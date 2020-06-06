#ifndef __VIBRATION_H
#define __VIBRATION_H
#include "stm32f10x.h"
#include "stm32f10x_usart.h"




/**

		*@brief initia the virbation sensor
		*@para none
		*@retval none
*/
void VibrationInit(void);

/**

		*@brief 


*/



	
/********************接收单个字符********************/
void USART_RecByte( USART_TypeDef * pUSARTx, uint16_t RecData)
{


while(USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE ) == !RESET);

	{
	USART_ReceiveData(pUSARTx);
	RecData = USART_ReceiveData(pUSARTx);
	}
//判断接收寄存器满标志位;

	
}




/***************** 接收字符串 **********************/

void Usart_ReceiveString( USART_TypeDef * pUSARTx, char *str)
 {
 
 while (USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE) == RESET)
 {
	 unsigned int k=0;
 do 
{
 USART_RecByte( pUSARTx, *(str + k) );
 k++;
 } 
while (*(str + k)!='\0'); 
 /* 等待接收完成 */
//(等待接收数据寄存器为满)
	 
printf("%s\n",str);
	 
}

}



void USART2_IRQHandler(void);


/*Usart_SendString函数用来发送一个字符串，实际调用Usar_SendByte函数
发送每个字符，直到遇到空字符才停止发送。最后使用循环检测发送完成的
事件标志TC，保证数据完成后才退出函数。*/



void USART2_IRQHandler(void);

 
 #endif