#ifndef __VIBRATION_H
#define __VIBRATION_H
#include "stm32f10x.h"




/**

		*@brief initia the virbation sensor
		*@para none
		*@retval none
*/
void VibrationInit(void);

/**

		*@brief 


*/

void LoraCtrl(void); 
void Vibration_Rec(void);



/********************接收单个字符********************/
void USART_RecByte( USART_TypeDef * pUSARTx, uint16_t RecData)
{

	USART_ReceiveData(pUSARTx);
	RecData = USART_ReceiveData(pUSARTx);

//判断接收寄存器满标志位;
while(USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE ) == !RESET);
	
}




/***************** 接收字符串 **********************/

void Usart_ReceiveString( USART_TypeDef * pUSARTx, char *str)
 {
 unsigned int k=0;
 do 
{
 Usart_RecByte( pUSARTx, *(str + k) );
 k++;
 } 
while (*(str + k)!='\0'); 
 /* 等待接收完成 */
//(等待接收数据寄存器为满)
 while (USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE == !RESET))
 {
}

 }
 
 #endif