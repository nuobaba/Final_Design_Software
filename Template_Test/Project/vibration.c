#include "stm32f10x.h"



int VibrationInit(void)
{
		GPIO_InitTypeDef GPIO_InitSensor;	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		GPIO_InitSensor.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;	
	  GPIO_InitSensor.GPIO_Mode = GPIO_Mode_AF_PP;      										 //select the I/O mode 
		GPIO_InitSensor.GPIO_Speed = GPIO_Speed_50MHz;            						 //selet the speed
			
			
		GPIO_Init(GPIOB,&GPIO_InitSensor);																		//programm into the register, vibration are all select the GPIOB 

}