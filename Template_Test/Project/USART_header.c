#include "stm32f10x.h"

uint8_t usart_rx_buf[5][40];    //���ջ���,���40���ֽ�
uint8_t usart_rx_temporary[40]; //���ݱ����ݴ���,����ܹ�����40���ֽ�
uint8_t usartrxbuf_pagebuf=0; //��������ܻ����ҳ�루5������
uint8_t usart_rd_len=0;         //������Ϣ�����ݳ���
uint8_t usart_rd_lentemp=0;   //������¼�Ѷ�ȡ�����ݳ���
uint8_t usart_rx_enableflag=0;  //����״̬���  
uint8_t usart_rx_lenrightflag=0;//���ݳ���У��λ��ȷ��־
uint8_t usart_rx_successflag=0; //�ɹ����յ�������Ϣ


/******************************************************************************************/
//USART2         �Զ��崮�������շ�����У��
//����ÿ�η���һ���ֽڣ�һ����λ������������û����һ���ֽڣ�

//�����ж�һ�Σ���ִ��һ�δ����жϺ�����
//��������У��  (��ͷ0xee)(���ݳ���)(...����...)(���ݳ��ȷ���)(��β0xef)
// ÿһ�����Ŵ���һ���ֽڣ����������Ŵ���N����?      
/******************************************************************************************/
void USART2_IRQHandler(void)                 //����2�жϷ������
{
uint8_t i,res,check_temp;
if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)   //�����жϣ�ÿ����һ���ֽڣ�8λ���������ݣ����ж�һ��,ÿ���жϣ���ÿ����һ�����ݣ���ִ��һ�����г���
{
    res=USART_ReceiveData(USART2); //��ȡ���յ�������
    if(usart_rx_enableflag==1) //���������ݱ�־��λʱ����������
{
res=USART_ReceiveData(USART2); //��ȡ���ڱ�־
if(usart_rd_lentemp==0) //��ͷ���һ������Ϊ��Ҫ��������ݵĳ���
{
usart_rd_len=res; //��ȡ���ݵĳ���  !!
if(usart_rd_len>=40)
{
usart_rx_lenrightflag=0; //���ݳ���У������
usart_rx_successflag=0; //���ݽ��ճɹ���־����
usart_rx_enableflag=0; //���ݽ�����ɣ����ݽ���������־����
usart_rd_len=0;                  //���ݳ�������
usart_rd_lentemp=0; //���ݳ����ݴ�������
}
}

else if(usart_rd_lentemp==usart_rd_len+1) //����ȡ����usart_rd_lentemp+1������ʱ��У���Ƿ��ǳ�����Ϣ�ķ���
{
check_temp=~usart_rd_len; //ȡ���ݳ���У��λ�ķ���
if(res==check_temp) //�����ݳ���У����ȷʱ
usart_rx_lenrightflag=1; //���ݳ���У���־��һ
else
{ //�����ݳ���У�����ʱ
usart_rx_lenrightflag=0; //���ݳ���У������
usart_rx_successflag=0; //���ݽ��ճɹ���־����
usart_rx_enableflag=0; //�����ݳ���У�����ʱ�����ݽ���������־����
usart_rd_len=0; //���ݳ�������
usart_rd_lentemp=0;   //���ݳ����ݴ�������
}
}
else if(usart_rd_lentemp==usart_rd_len+2) //����ȡ����usart_rd_lentemp+2������ʱ��У���β�Ƿ���ȷ
{
if((res==0xef)&&(usart_rx_lenrightflag==1)) //�����β�����볤��У�鶼��ȷ
{
usart_rx_lenrightflag=0; //���ݳ���У������
usart_rx_successflag=1;          //���ݽ��ճɹ���־��һ
usart_rx_enableflag=0; //���ݽ�����ɣ����ݽ���������־����
// usart_rd_len=0; //���ݳ�������
usart_rd_lentemp=0; //���ݳ����ݴ�������
}
else 
{ //����β����У�����ʱ
usart_rx_lenrightflag=0; //���ݳ���У������
usart_rx_successflag=0; //���ݽ��ճɹ���־����
usart_rx_enableflag=0; //���ݽ�����ɣ����ݽ���������־����
usart_rd_len=0; //���ݳ�������
usart_rd_lentemp=0; //���ݳ����ݴ�������
}
}
else usart_rx_temporary[usart_rd_lentemp-1]=res; //��usart_rd_lentempΪ���ݶ�ʱ�������ݴ浽�������ݽ��ռĴ�����

        usart_rd_lentemp++; //ÿ�μ�¼���ݣ����ݳ����ݴ����Լ�
if(usart_rx_successflag==1) //����ɹ����յ���Ϣ���ݣ�������usart_rx_temporary[]�ڵ����ݴ��ݸ�usart_rx_buf[][]
{
for(i=0;i<usart_rd_len;i++)
usart_rx_buf[usartrxbuf_pagebuf][i]=usart_rx_temporary[i];
usartrxbuf_pagebuf++; //���ܻ����ҳ�뻺���Լ�
if(usartrxbuf_pagebuf==5) usartrxbuf_pagebuf=0; //���ܻ����ҳ�뻺�������Ϊ5


usart_rx_lenrightflag=0; //���ݳ���У������
usart_rx_successflag=0; //���ݽ��ճɹ���־����
usart_rx_enableflag=0; //���ݽ�����ɣ����ݽ���������־����
usart_rd_len=0;                  //���ݳ�������
usart_rd_lentemp=0; //���ݳ����ݴ�������
// USART2_SendData("successed rx!\r\n");
}
}
if((res==0xee)&&(usart_rx_enableflag==0)) //(��)�����ܵ���ͷ(0xee)���ݲ��һ�û�гɹ�������������Ϣ
usart_rx_enableflag=1; //���죩˵�����ǰ�ͷ�������������ݱ�־���������ݽ��ս׶�
}
USART_ClearITPendingBit(USART2, USART_IT_RXNE);//�ж����
} 



//���ĵط����Ǻ�ԭ���в�ͬ�ĵط���

//����usart_rd_len=0;���������ڣ����ڳɹ���־Ϊ1�������޷���rx_buf��ֵ����Ϊi<0һֱѭ��ֱ��������

//���������������ͷ���ֱ�ӽ�����һ��if��ʹ���ݳ���ҲΪ0xEE���ʹ�����

