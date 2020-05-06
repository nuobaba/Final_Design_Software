 #include "stm32f10x.h"   

int 	QMCInit(void)
{

	GPIO_InitTypeDef LORA_Init;	
	USART_InitTypeDef USART3_Init;
	NVIC_InitTypeDef LORA_NVIC_Init;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//PA8
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
		USART3_Init.USART_BaudRate = 9600;
		USART3_Init.USART_WordLength = USART_WordLength_9b;         
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
