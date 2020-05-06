



#ifndef	__SEND_H
#define __SEND_H
#include "stm32f10x.h"




/**

		*@brief initia the usart pin
		*@para none
		*@retval none
*/


void usart_config(void);
void usart_release_gpio_init(void);
void NVIC_Config(void);
void usart_para_config(void);





#endif