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



/********************���յ����ַ�********************/
void USART_RecByte( USART_TypeDef * pUSARTx, uint16_t RecData)
{

	USART_ReceiveData(pUSARTx);
	RecData = USART_ReceiveData(pUSARTx);

//�жϽ��ռĴ�������־λ;
while(USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE ) == !RESET);
	
}




/***************** �����ַ��� **********************/

void Usart_ReceiveString( USART_TypeDef * pUSARTx, char *str)
 {
 unsigned int k=0;
 do 
{
 Usart_RecByte( pUSARTx, *(str + k) );
 k++;
 } 
while (*(str + k)!='\0'); 
 /* �ȴ�������� */
//(�ȴ��������ݼĴ���Ϊ��)
 while (USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE == !RESET))
 {
}

 }
 
 #endif