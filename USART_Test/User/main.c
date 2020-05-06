#include "stm32f10x.h"
//#include "vibration.h"
//#include "Lora.h"
#include "send.h"


void main()
{
    /*打开USATT1、GPIOA、AFIO的时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 \
    | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /*配置对应的串口引脚*/
    usart_release_gpio_init();

    /*配置串口中断*/
    usart_para_config();

    USART_ClearFlag(USART1,USART_FLAG_TC); //清除发送完成标志位
    NVIC_Config();                         //初始化NVIO
    USART_Cmd(USART1, ENABLE);             //使能串口1
}
//配置相应的IO口，将其设为复用推挽输出和浮空输入







/*int main()
{
		VibrationInit();
		LoraInit();
	
}
*/


