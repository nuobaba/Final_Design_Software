#include "stm32f10x.h"
#include "Lora.h"

#include "vibration_receive.h"
int main()
{
		VibrationInit_TX();
		LoraInit();
	Usart_ReceiveString( USART3, char *vib);
		for(int i=0;i<8;i++)
	{
		USART_SendData(USART3,RecMid[i]);
	
	}
	
	
}



