#include "stm32f10x.h"
//#include "vibration.h"
//#include "Lora.h"
#include "send.h"


void main()
{
    /*��USATT1��GPIOA��AFIO��ʱ��*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 \
    | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /*���ö�Ӧ�Ĵ�������*/
    usart_release_gpio_init();

    /*���ô����ж�*/
    usart_para_config();

    USART_ClearFlag(USART1,USART_FLAG_TC); //���������ɱ�־λ
    NVIC_Config();                         //��ʼ��NVIO
    USART_Cmd(USART1, ENABLE);             //ʹ�ܴ���1
}
//������Ӧ��IO�ڣ�������Ϊ������������͸�������







/*int main()
{
		VibrationInit();
		LoraInit();
	
}
*/


