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
		
		USART_Cmd(USART2,ENABLE);				//启动设备USART3
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART2_IRQn;               //stm32f10x,h中找，注意看结构体的定义
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占式优先级别1，可取0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// 指定响应优先级别0，可取0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		

//  设置中断进入的条件：发送数据缓冲区有数据的时候就会进入中断
 
        USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
				

	
}



//void USART2_IRQHandler(void)
//{




//	
//		
//}







/*进行数据库比较
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












