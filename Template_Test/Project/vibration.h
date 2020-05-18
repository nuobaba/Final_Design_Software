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


///***************** 发送一个字符 **********************/
// void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
// {
// /* 发送一个字节数据到 USART */
// USART_SendData(pUSARTx,ch);
// 
// /* 等待发送数据寄存器为空 */
// while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
// }
// 
// 
// 
// /***************** 发送字符串 **********************/
// void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
// {

// while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
// {
// unsigned int k=0;
// do 
//{
// Usart_SendByte( pUSARTx, *(str + k) );
// k++;
// } 
//while (*(str + k)!='\0'); 
// /* 等待发送完成 */
////(等待发送数据寄存器为空)
//	  }
// 
////		else 
//	//		break;
// }
///*Usart_SendString函数用来发送一个字符串，实际调用Usar_SendByte函数
//发送每个字符，直到遇到空字符才停止发送。最后使用循环检测发送完成的
//事件标志TC，保证数据完成后才退出函数。*/





 #endif