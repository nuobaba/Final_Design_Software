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
		
		USART_Cmd(USART3,ENABLE);				//�����豸USART1
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART3_IRQn;               //stm32f10x,h���ң�ע�⿴�ṹ��Ķ���
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// ָ����ռʽ���ȼ���1����ȡ0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// ָ����Ӧ���ȼ���0����ȡ0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		
	
}


void Vibration_Rec(void)
{
	
//GPIOB_0��GPIOB_1�øߵ�ƽ�������ռ��ź�
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

//���񶯴���������
uint16_t RxData; 
USART_ReceiveData(USART2);

//���ݷ������ݼĴ�����
//RxData = USART_DR_DR;


}



/*�����ж�
�����ж�
//���øò������ݶ���MCU

�������ݸ���������
//RxData = USART_DR_DR;*/

/***************** ����һ���ַ� **********************/
 void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
 {
 /* ����һ���ֽ����ݵ� USART */
 USART_SendData(pUSARTx,ch);
 
 /* �ȴ��������ݼĴ���Ϊ�� */
 while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
 }





 /***************** �����ַ��� **********************/
 void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
 {
 unsigned int k=0;
 do 
{
 Usart_SendByte( pUSARTx, *(str + k) );
 k++;
 } 
while (*(str + k)!='\0'); 
 /* �ȴ�������� */
//(�ȴ��������ݼĴ���Ϊ��)
 while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
 {
 }
 }
/*Usart_SendString������������һ���ַ�����ʵ�ʵ���Usar_SendByte����
����ÿ���ַ���ֱ���������ַ���ֹͣ���͡����ʹ��ѭ����ⷢ����ɵ�
�¼���־TC����֤������ɺ���˳�������




�������ݿ�Ƚ�
//how to compare????
�ȽϺ���������


if����꣩
{
���������Ŵ�����  ���øߵ�ƽ��
������������ͷ     ���øߵ�ƽ��
}
�����
break;
}*/












