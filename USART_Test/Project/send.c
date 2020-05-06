#include "stm32f10x.h"






void usart_release_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /*配置PA9为复用推外输出*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*配置PA10为浮空输入*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStruct);
}



void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; //NVIC 初始化结构体声明

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //设置串口1 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //子优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能

    NVIC_Init(&NVIC_InitStructure);
}






//配置串口协议
void usart_para_config(void)
{
    USART_InitTypeDef USART_InitStruct;

    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8
    USART_InitStruct.USART_Parity = USART_Parity_No;        //N
    USART_InitStruct.USART_StopBits = USART_StopBits_1;     //1

    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能接收中断
}


//void usart_config()
//{
    /*打开USATT1、GPIOA、AFIO的时钟*/
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 \
    | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /*配置对应的串口引脚*/
 //   usart_release_gpio_init();

    /*配置串口中断*/
 //   usart_para_config();

 //   USART_ClearFlag(USART1,USART_FLAG_TC); //清除发送完成标志位
 //   NVIC_Config();                         //初始化NVIO
  //  USART_Cmd(USART1, ENABLE);             //使能串口1
//}
//配置相应的IO口，将其设为复用推挽输出和浮空输入

