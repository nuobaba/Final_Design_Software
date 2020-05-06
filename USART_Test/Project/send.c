#include "stm32f10x.h"






void usart_release_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /*����PA9Ϊ�����������*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*����PA10Ϊ��������*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStruct);
}



void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; //NVIC ��ʼ���ṹ������

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //���ô���1 �ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ��

    NVIC_Init(&NVIC_InitStructure);
}






//���ô���Э��
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

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ�ܽ����ж�
}


//void usart_config()
//{
    /*��USATT1��GPIOA��AFIO��ʱ��*/
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 \
    | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /*���ö�Ӧ�Ĵ�������*/
 //   usart_release_gpio_init();

    /*���ô����ж�*/
 //   usart_para_config();

 //   USART_ClearFlag(USART1,USART_FLAG_TC); //���������ɱ�־λ
 //   NVIC_Config();                         //��ʼ��NVIO
  //  USART_Cmd(USART1, ENABLE);             //ʹ�ܴ���1
//}
//������Ӧ��IO�ڣ�������Ϊ������������͸�������

