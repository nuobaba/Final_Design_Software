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



	
/********************���յ����ַ�********************/
void USART_RecByte( USART_TypeDef * pUSARTx, uint16_t RecData)
{


while(USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE ) == !RESET);

	{
	USART_ReceiveData(pUSARTx);
	RecData = USART_ReceiveData(pUSARTx);
	}
//�жϽ��ռĴ�������־λ;

	
}




/***************** �����ַ��� **********************/

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
 /* �ȴ�������� */
//(�ȴ��������ݼĴ���Ϊ��)
	 
printf("%s\n",str);
	 
}

}



void USART2_IRQHandler(void);


/*Usart_SendString������������һ���ַ�����ʵ�ʵ���Usar_SendByte����
����ÿ���ַ���ֱ���������ַ���ֹͣ���͡����ʹ��ѭ����ⷢ����ɵ�
�¼���־TC����֤������ɺ���˳�������*/



void USART2_IRQHandler(void);

 
 #endif