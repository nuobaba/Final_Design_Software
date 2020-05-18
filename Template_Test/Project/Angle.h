#ifndef __ANGLE_H
#define __ANGLE_H



void HMC5883L_Init(void)
	
{
	GPIO_InitTypeDef QMC_Init;	
	USART_InitTypeDef USART1_Init;
	NVIC_InitTypeDef QMC_NVIC_Init;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//PA9
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	


	//Initial the GPIO                 TX
		QMC_Init.GPIO_Pin = GPIO_Pin_9;	
	  QMC_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;      										 //select the I/O mode 
		QMC_Init.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
		GPIO_Init(GPIOA,&QMC_Init);	

		//interrupt intial
		


}


#endif