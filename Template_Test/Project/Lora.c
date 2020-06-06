#include "stm32f10x.h"
//#include "vibration_receive.h"
#include "lora.h"



void LoraInit(void)
{

		GPIO_InitTypeDef LORA_Init;	
		USART_InitTypeDef USART3_Init;
		NVIC_InitTypeDef LORA_NVIC_Init;
		USART_InitTypeDef USART2_Init;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	
	
	
	  //Initial the GPIO                 TX
		LORA_Init.GPIO_Pin = GPIO_Pin_10;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
	

		//Initial the GPIO                 RX
		LORA_Init.GPIO_Pin = GPIO_Pin_11;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
	

	  //Initial the GPIO                MD0
		LORA_Init.GPIO_Pin = GPIO_Pin_5;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
	

		//Initial the GPIO                 MD1
		LORA_Init.GPIO_Pin = GPIO_Pin_6;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
		
			//Initial the GPIO                 AUX
		LORA_Init.GPIO_Pin = GPIO_Pin_4;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);
	
	
	
		//Initial the USART     RX/TX
		USART3_Init.USART_BaudRate = 9600;
		USART3_Init.USART_WordLength = USART_WordLength_8b;         
		USART3_Init.USART_StopBits = USART_StopBits_1;            
		USART3_Init.USART_Parity = USART_Parity_No ;              
		USART3_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART3_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART3,&USART3_Init);
		
		USART_Cmd(USART3,ENABLE);				//�����豸USART3
		
		//Initial the USART     RX/TX
		USART2_Init.USART_BaudRate = 12800;
		USART2_Init.USART_WordLength = USART_WordLength_8b;         
		USART2_Init.USART_StopBits = USART_StopBits_1;            
		USART2_Init.USART_Parity = USART_Parity_No ;              
		USART2_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART2_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART2,&USART2_Init);
		
		USART_Cmd(USART2,ENABLE);				//�����豸USART3
		
		
		//interrupt intial
		
		//SysTick��ʱ����ϵͳ�δ�ʱ������һ������ʱ��ʱ������������NVIC�У����ڲ���SYSTICK�쳣���쳣�ţ�15����
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART3_IRQn;               //stm32f10x,h���ң�ע�⿴�ṹ��Ķ���
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// ָ����ռʽ���ȼ���1����ȡ0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// ָ����Ӧ���ȼ���0����ȡ0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		LORA_MD0 = 0;
		LORA_MD1 = 0;
		

}



uint16_t RecTransform; 


void LoraCtrl(void)           ///interrupt

{
	

//���������񶯴�����USART�ڵ����ݷ�������LORA�Ĵ������� 

	
if (USART3, GetFlagStatus (USART3,USART_FLAG_RXNE) != SET) //���յ���λ�����ַ�����������
	
	{
		
		
	
	}
//{
//MDO=0;
//MD1=1;
//����1
//�Է����գ�2
//����������2
//�����Recdata   2
//	�����2
//	�����1
//	
//	
//	if�����������и�������
//	�����ӴŴ�������GPIO ��ֵ
//	��ʼ�ռ�
//	����ĳ����
//	
//	������lora�����ߣ�
//	���������
//	����һ�±�ɽǶ�
//	
//	
//	����ͷ�źŷ������
//	��lora�����ߣ�
	
	
	
	
	
	


//}
	
	
	
}