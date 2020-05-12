 #include "stm32f10x.h"   

int 	QMCInit(void)
{

	GPIO_InitTypeDef QMC_Init;	
	USART_InitTypeDef USART1_Init;
	NVIC_InitTypeDef QMC_NVIC_Init;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//PA9
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	
//	
//	  //Initial the GPIO                 
//		LORA_Init.GPIO_Pin = GPIO_Pin_10;	
//	  LORA_Init.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
//		LORA_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
//		GPIO_Init(GPIOA,&LORA_Init);	
//	

		//Initial the GPIO                 TX
		QMC_Init.GPIO_Pin = GPIO_Pin_9;	
	  QMC_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		QMC_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&QMC_Init);	
	

	
	
	
		//Initial the USART     RX/TX
		USART1_Init.USART_BaudRate = 9600;
		USART1_Init.USART_WordLength = USART_WordLength_8b;         
		USART1_Init.USART_StopBits = USART_StopBits_1;            
		USART1_Init.USART_Parity = USART_Parity_No ;              
		USART1_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART1_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART1,&USART1_Init);
		
		USART_Cmd(USART1,ENABLE);				//启动设备USART1
		
		
		//interrupt intial
		
		
		QMC_NVIC_Init.NVIC_IRQChannel = USART1_IRQn;               //stm32f10x,h中找，注意看结构体的定义
		QMC_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占式优先级别1，可取0-7
		QMC_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// 指定响应优先级别0，可取0-1
		QMC_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&QMC_NVIC_Init);
		
		
		
		


}
