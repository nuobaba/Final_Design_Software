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
		
		USART_Cmd(USART3,ENABLE);				//启动设备USART3
		
		//Initial the USART     RX/TX
		USART2_Init.USART_BaudRate = 12800;
		USART2_Init.USART_WordLength = USART_WordLength_8b;         
		USART2_Init.USART_StopBits = USART_StopBits_1;            
		USART2_Init.USART_Parity = USART_Parity_No ;              
		USART2_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART2_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART2,&USART2_Init);
		
		USART_Cmd(USART2,ENABLE);				//启动设备USART3
		
		
		//interrupt intial
		
		//SysTick定时器（系统滴答定时器）是一个倒计时定时器，被捆绑在NVIC中，用于产生SYSTICK异常（异常号：15）。
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART3_IRQn;               //stm32f10x,h中找，注意看结构体的定义
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占式优先级别1，可取0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// 指定响应优先级别0，可取0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		LORA_MD0 = 0;
		LORA_MD1 = 0;
		

}



uint16_t RecTransform; 


void LoraCtrl(void)           ///interrupt

{
	

//来自连接振动传感器USART口的数据放至连接LORA的传感器上 

	
if (USART3, GetFlagStatus (USART3,USART_FLAG_RXNE) != SET) //接收到八位长的字符串，接收满
	
	{
		
		
	
	}
//{
//MDO=0;
//MD1=1;
//发送1
//对方接收；2
//放入计算机；2
//收命令；Recdata   2
//	发命令；2
//	收命令；1
//	
//	
//	if（开启）（有个变量）
//	则连接磁传感器的GPIO 赋值
//	开始收集
//	防入某变量
//	
//	变量给lora，发走；
//	变量给舵机
//	处理一下变成角度
//	
//	
//	摄像头信号防入变量
//	给lora，发走；
	
	
	
	
	
	


//}
	
	
	
}