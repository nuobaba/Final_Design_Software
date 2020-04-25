#include "stm32f10x.h"

uint8_t usart_rx_buf[5][40];    //接收缓冲,最大40个字节
uint8_t usart_rx_temporary[40]; //数据保存暂存器,最多能够缓存40个字节
uint8_t usartrxbuf_pagebuf=0; //最上面接受缓存的页码（5）缓存
uint8_t usart_rd_len=0;         //有用信息的数据长度
uint8_t usart_rd_lentemp=0;   //用来记录已读取的数据长度
uint8_t usart_rx_enableflag=0;  //接收状态标记  
uint8_t usart_rx_lenrightflag=0;//数据长度校验位正确标志
uint8_t usart_rx_successflag=0; //成功接收到数据信息


/******************************************************************************************/
//USART2         自定义串口数据收发数据校验
//串口每次发送一个字节（一个八位二进制数），没接受一个字节，

//串口中断一次，就执行一次串口中断函数。
//串口数据校验  (包头0xee)(数据长度)(...数据...)(数据长度反码)(包尾0xef)
// 每一个括号代表一个字节，而数据括号待变N个字?      
/******************************************************************************************/
void USART2_IRQHandler(void)                 //串口2中断服务程序
{
uint8_t i,res,check_temp;
if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)   //接收中断，每接收一个字节（8位二进制数据），中断一次,每次中断（即每接收一个数据）都执行一次下列程序
{
    res=USART_ReceiveData(USART2); //读取接收到的数据
    if(usart_rx_enableflag==1) //到接受数据标志置位时，接受数据
{
res=USART_ReceiveData(USART2); //读取串口标志
if(usart_rd_lentemp==0) //包头后第一个数据为需要传输的数据的长度
{
usart_rd_len=res; //读取数据的长度  !!
if(usart_rd_len>=40)
{
usart_rx_lenrightflag=0; //数据长度校验清零
usart_rx_successflag=0; //数据接收成功标志清零
usart_rx_enableflag=0; //数据接收完成，数据接收启动标志清零
usart_rd_len=0;                  //数据长度清零
usart_rd_lentemp=0; //数据长度暂存器清零
}
}

else if(usart_rd_lentemp==usart_rd_len+1) //当读取到第usart_rd_lentemp+1个数据时，校验是否是长度信息的反码
{
check_temp=~usart_rd_len; //取数据长度校验位的反码
if(res==check_temp) //当数据长度校验正确时
usart_rx_lenrightflag=1; //数据长度校验标志置一
else
{ //当数据长度校验错误时
usart_rx_lenrightflag=0; //数据长度校验清零
usart_rx_successflag=0; //数据接收成功标志清零
usart_rx_enableflag=0; //当数据长度校验错误时，数据接收启动标志清零
usart_rd_len=0; //数据长度清零
usart_rd_lentemp=0;   //数据长度暂存器清零
}
}
else if(usart_rd_lentemp==usart_rd_len+2) //当读取到第usart_rd_lentemp+2个数据时，校验包尾是否正确
{
if((res==0xef)&&(usart_rx_lenrightflag==1)) //如果包尾数据与长度校验都正确
{
usart_rx_lenrightflag=0; //数据长度校验清零
usart_rx_successflag=1;          //数据接收成功标志置一
usart_rx_enableflag=0; //数据接收完成，数据接收启动标志清零
// usart_rd_len=0; //数据长度清零
usart_rd_lentemp=0; //数据长度暂存器清零
}
else 
{ //当包尾数据校验错误时
usart_rx_lenrightflag=0; //数据长度校验清零
usart_rx_successflag=0; //数据接收成功标志清零
usart_rx_enableflag=0; //数据接收完成，数据接收启动标志清零
usart_rd_len=0; //数据长度清零
usart_rd_lentemp=0; //数据长度暂存器清零
}
}
else usart_rx_temporary[usart_rd_lentemp-1]=res; //当usart_rd_lentemp为数据段时，将数据存到串口数据接收寄存器中

        usart_rd_lentemp++; //每次记录数据，数据长度暂存器自加
if(usart_rx_successflag==1) //如果成功接收到信息数据，将缓存usart_rx_temporary[]内的数据传递给usart_rx_buf[][]
{
for(i=0;i<usart_rd_len;i++)
usart_rx_buf[usartrxbuf_pagebuf][i]=usart_rx_temporary[i];
usartrxbuf_pagebuf++; //接受缓存的页码缓存自加
if(usartrxbuf_pagebuf==5) usartrxbuf_pagebuf=0; //接受缓存的页码缓存最大数为5


usart_rx_lenrightflag=0; //数据长度校验清零
usart_rx_successflag=0; //数据接收成功标志清零
usart_rx_enableflag=0; //数据接收完成，数据接收启动标志清零
usart_rd_len=0;                  //数据长度清零
usart_rd_lentemp=0; //数据长度暂存器清零
// USART2_SendData("successed rx!\r\n");
}
}
if((res==0xee)&&(usart_rx_enableflag==0)) //(红)当接受到包头(0xee)数据并且还没有成功接收完数据信息
usart_rx_enableflag=1; //（红）说明这是包头，启动接收数据标志，进入数据接收阶段
}
USART_ClearITPendingBit(USART2, USART_IT_RXNE);//中断清除
} 



//标红的地方，是和原文中不同的地方。

//首先usart_rd_len=0;这句如果存在，则在成功标志为1条件中无法给rx_buf赋值，因为i<0一直循环直接跳出；

//后面那两句如果在头则会直接进入下一个if，使数据长度也为0xEE，就错啦。

