#include "stm32f10x.h"
#include "vibration.h"


void VibrationInit(void)
{
		GPIO_InitTypeDef GPIO_InitSensor;	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		GPIO_InitSensor.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;	
	  GPIO_InitSensor.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		GPIO_InitSensor.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
			
			
		GPIO_Init(GPIOB,&GPIO_InitSensor);																		//programm into the register, vibration are all select the GPIOB 

	
//		NVIC_DisableIRQ(IRQn);
	
	
	
	
	
	
	/*----------------------------------------------------------*/
	
	
	USART_InitTypeDef USART3_Init;
	NVIC_InitTypeDef LORA_NVIC_Init;
	
	   RCC_AHB1PeriphCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	

	
		//Initial the USART     RX/TX
		USART3_Init.USART_BaudRate = 9600;
		USART3_Init.USART_WordLength = USART_WordLength_8b;         
		USART3_Init.USART_StopBits = USART_StopBits_1;            
		USART3_Init.USART_Parity = USART_Parity_No ;              
		USART3_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART3_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART3,&USART3_Init);
		
		USART_Cmd(USART3,ENABLE);				//启动设备USART1
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART3_IRQn;               //stm32f10x,h中找，注意看结构体的定义
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占式优先级别1，可取0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// 指定响应优先级别0，可取0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		
	
}


void Vibration_Rec(void)
{
	
//GPIOB_0、GPIOB_1置高电平，方便收集信号
GPIO_SetBits(GPIOB,GPIO_Pin_0);
GPIO_SetBits(GPIOB,GPIO_Pin_1);
	
uint16_t data0;	
uint16_t data1;
data0 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);	
data1 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);	
	
	
	
	
}










void USART3_IRQHandler(void)
{
//{
//u16 RxData; 
//RxData = USART_ReceiveData(USART2);
//}

//收振动传感器数据
uint16_t RxData; 
USART_ReceiveData(USART2);

//数据放入数据寄存器。
//RxData = USART_DR_DR;


}



/*触发中断
进入中断
//将该该部分数据读入MCU

发送数据给变量？？
//RxData = USART_DR_DR;*/

/***************** 发送一个字符 **********************/
 void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
 {
 /* 发送一个字节数据到 USART */
 USART_SendData(pUSARTx,ch);
 
 /* 等待发送数据寄存器为空 */
 while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
 }





 /***************** 发送字符串 **********************/
 void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
 {
 unsigned int k=0;
 do 
{
 Usart_SendByte( pUSARTx, *(str + k) );
 k++;
 } 
while (*(str + k)!='\0'); 
 /* 等待发送完成 */
//(等待发送数据寄存器为空)
 while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
 {
 }
 }
/*Usart_SendString函数用来发送一个字符串，实际调用Usar_SendByte函数
发送每个字符，直到遇到空字符才停止发送。最后使用循环检测发送完成的
事件标志TC，保证数据完成后才退出函数。




进行数据库比较
//how to compare????
比较函数（）；


if（达标）
{
触发启动磁传感器  （置高电平）
触发启动摄像头     （置高电平）
}
不达标
break;
}*/












