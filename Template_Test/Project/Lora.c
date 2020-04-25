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
		USART1_Init.USART_WordLength = USART_WordLength_9b;         
		USART1_Init.USART_StopBits = USART_StopBits_1;            
		USART1_Init.USART_Parity = USART_Parity_No ;              
		USART1_Init.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                
		USART1_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	
		
		USART_Init(USART1,&USART1_Init);
		
		USART_Cmd(USART1,ENABLE);				//启动设备USART1
		
		
		//interrupt intial
		
		
		LORA_NVIC_Init.NVIC_IRQChannel = USART1_IRQn;               //stm32f10x,h中找，注意看结构体的定义
		LORA_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占式优先级别1，可取0-7
		LORA_NVIC_Init.NVIC_IRQChannelSubPriority = 0;						// 指定响应优先级别0，可取0-1
		LORA_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
		
		
		
		NVIC_Init(&LORA_NVIC_Init);
		
		
		
		


}



int LoraCtrl(void)           ///interrupt

{
	if ((USART_GetITStatus(USART1,USART_IT_RXNE)) == SET)   ///SET==0
	
	
		uint8_t data;             
		data = USART_ReceiveData(USART1);        //receive data from the lora from the sensor、
		USART_SetAddress(USART1,0x0);
	
	
	/*每收到十六位数据，进入中断一次，将数据放入MCU中，分别确定每一方向的角度，进行二进制和角度的转换，调整舵机的角度*/
	/*收到振动传感器的数据，一定量，进入中断*/
	//qmc5883l
	uint16_t X,Y,Z;
	uint8_t i;
	X = GPIO_ReadInputData(GPIOB,GPIO_Pin_5);
	
	for(i=0;i<8;i++)
	USART1_BASE << i = X[i];
	USART1_BASE << (i+8) = Y[i];
	USART1_BASE << (i+16) = Z[i];
	
	//数据从传感器收到传到LORA连接口，这个不对，需要的是USART的写入形式
	GPIO_Write(GPIOA,X);

}





/* 发送单个字符 */
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
    // 操作USART_DR寄存器发送单个数据
    USART_SendData(pUSARTx, data);
    // 等待发送寄存器TDR为空，为空时则置1
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/* 发送字符串 */
void Usart_SendStr(USART_TypeDef* pUSARTx, char *str)
{
    uint8_t i = 0;
    do
    {
	Usart_SendByte(pUSARTx, *(str+i));
	i++;
    }
		//while(*(str+i) != '\0');
    // 等待发送完成
  //  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
		
//{	}	
		
	}		
		
		
	
		
			USART_DR_DR;
