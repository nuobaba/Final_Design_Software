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


///***************** ����һ���ַ� **********************/
// void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
// {
// /* ����һ���ֽ����ݵ� USART */
// USART_SendData(pUSARTx,ch);
// 
// /* �ȴ��������ݼĴ���Ϊ�� */
// while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
// }
// 
// 
// 
// /***************** �����ַ��� **********************/
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
// /* �ȴ�������� */
////(�ȴ��������ݼĴ���Ϊ��)
//	  }
// 
////		else 
//	//		break;
// }
///*Usart_SendString������������һ���ַ�����ʵ�ʵ���Usar_SendByte����
//����ÿ���ַ���ֱ���������ַ���ֹͣ���͡����ʹ��ѭ����ⷢ����ɵ�
//�¼���־TC����֤������ɺ���˳�������*/





 #endif