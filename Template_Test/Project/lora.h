#ifndef	__LORA_H
#define __LORA_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"



/**

		*@brief initia the lora chip
		*@para none
		*@retval none
*/


void LoraInit(void);




//#define SDA_IN()  {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=(u32)8<<4;}
//#define SDA_OUT() {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=(u32)3<<4;}
#define LORA_MD0    PBout(5) //MDO
#define LORA_MD1    PBout(6) //MD1	 
#define GPIO_MD0    GPIO_Pin_5
#define GPIO_MD1    GPIO_Pin_6
#define LORA_PERIPH GPIOB
///#define READ_SDA   PAin(9) 




#endif