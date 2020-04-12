#include "stm32f10x.h"


int LoraInit(void)
{

	GPIO_InitTypeDef LORA_Init;	
	USART_InitTypeDef USART1_Init;
	NVIC_InitTypeDef LORA_NVIC_Init;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	
	
	  //Initial the GPIO                 TX
		LORA_Init.GPIO_Pin = GPIO_Pin_9;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
	

		//Initial the GPIO                 RX
		LORA_Init.GPIO_Pin = GPIO_Pin_10;	
	  LORA_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&LORA_Init);	
	

	
	
	
		//Initial the USART     RX/TX
		USART1_Init.USART_BaudRate = 9600;
		USART1_Init.USART_WordLength = USART_WordLength_8b;         
		USART1_Init.USART_StopBits = USART_StopBits_1;            
		USART1_Init.USART_Parity = USART_Parity_No ;              
		USART1_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART1_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART1,&USART1_Init);
		
		USART_Cmd(USART1,ENABLE);
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART1_IRQn;               //stm32f10x,h���ң�ע�⿴�ṹ��Ķ���
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// ָ����ռʽ���ȼ���1����ȡ0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// ָ����Ӧ���ȼ���0����ȡ0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		
		
		


}



int LoraCtrl(void)           ///interrupt

{
	if ((USART_GetITStatus(USART1,USART_IT_RXNE)) == SET)   ///SET==0
	
	
		uint8_t data;             
		data = USART_ReceiveData(USART1);        //receive data from the lora from the sensor��
		USART_SetAddress(USART1,0x0);
	
	
	/*ÿ�յ�ʮ��λ���ݣ������ж�һ�Σ������ݷ���MCU�У��ֱ�ȷ��ÿһ����ĽǶȣ����ж����ƺͽǶȵ�ת������������ĽǶ�*/
	/*�յ��񶯴����������ݣ�һ�����������ж�*/
	//qmc5883l
	uint8_t X[8],Y[8],Z[8];
	uint8_t i;
	for(i=0;i<8;i++)
	USART1_BASE << i = X[i];
	USART1_BASE << (i+8) = Y[i];
	USART1_BASE << (i+16) = Z[i];

}