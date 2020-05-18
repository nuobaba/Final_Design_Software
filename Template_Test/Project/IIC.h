#ifndef	__IIC_H
#define __IIC_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"



#define SDA_IN()  {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=(u32)8<<4;}
#define SDA_OUT() {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=(u32)3<<4;}
#define IIC_SCL    PAout(8) //SCL
#define IIC_SDA    PAout(9) //SDA	 
#define GPIO_SCL    GPIO_Pin_8
#define GPIO_SDA    GPIO_Pin_9
#define IIC_PERIPH GPIOA
#define READ_SDA   PAin(9) 

#define HMC5883L_Write_Address   0x1a
#define HMC5883L_Read_Address    0x1b




#endif
