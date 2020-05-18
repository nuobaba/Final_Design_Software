#include "stm32f10x.h"
#include "vibration.h"


void VibrationInit(void)
{
		GPIO_InitTypeDef GPIO_InitSensor;	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		GPIO_InitSensor.GPIO_Pin = GPIO_Pin_2;	
	  GPIO_InitSensor.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		GPIO_InitSensor.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
			
			
		GPIO_Init(GPIOA,&GPIO_InitSensor);																		//programm into the register, vibration are all select the GPIOB 

	
//		NVIC_DisableIRQ(IRQn);
	
		USART_InitTypeDef USART2_Init;
		NVIC_InitTypeDef LORA_NVIC_Init;
	  RCC_AHB1PeriphCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	

	
		//Initial the USART     TX
		USART2_Init.USART_BaudRate = 9600;
		USART2_Init.USART_WordLength = USART_WordLength_8b;         
		USART2_Init.USART_StopBits = USART_StopBits_1;            
		USART2_Init.USART_Parity = USART_Parity_No ;              
		USART2_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART2_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART2,&USART2_Init);
		
		USART_Cmd(USART2,ENABLE);				//�����豸USART3
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART2_IRQn;               //stm32f10x,h���ң�ע�⿴�ṹ��Ķ���
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// ָ����ռʽ���ȼ���1����ȡ0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// ָ����Ӧ���ȼ���0����ȡ0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		

//  �����жϽ�����������������ݻ����������ݵ�ʱ��ͻ�����ж�
 
        USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
				

	
}



//void USART2_IRQHandler(void)
//{




//	
//		
//}







/*�������ݿ�Ƚ�
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












