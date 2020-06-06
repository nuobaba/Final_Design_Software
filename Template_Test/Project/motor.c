
#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"


void motor_intial (void)
{
GPIO_InitTypeDef GPIO_InitStructure;
 
  // 输出比较通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 /* // 输出比较通道互补通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
*/	
	// BKIN引脚默认先输出低电平
	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);


}




static void Advance_TIM_Config(void)
{
	  // 开启定时器时钟,即内部时钟CK_INT=72M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
 
/*--------------------时基结构体初始化-------------------------*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period= (200-1);	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= (7200-1);	
	// 时钟分频因子 ，用于配置死区时间，没用到，随意
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到，可以随意设置
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
 
	/*--------------------输出比较结构体初始化-------------------*/		
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 互补输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	// 设置占空比大小
	TIM_OCInitStructure.TIM_Pulse = 0;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// 互补输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// 互补输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(TIM1, ENABLE);	
	// 主输出使能，当使用的是通用定时器时，这句不需要
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
 
void TIM_Init(void)
{
	motor_intial();
	Advance_TIM_Config();
}





//void motor_control (void)
//	{


//TIM_SetCompare1(ADVANCE_TIM, 175);
//		
//	
//		
//		

//}
	void motor_transform()

{
	int delay_time;
	delay_init(); //延时函数初始化
	TIM_Init(); //定时器初始化
	
	delay_time = 500;
	while(1)
	{
		delay_ms(delay_time);
		TIM_SetCompare1(ADVANCE_TIM, 175); //对应180度
        delay_ms(delay_time);
		TIM_SetCompare1(ADVANCE_TIM, 180); //对应135度
        delay_ms(delay_time);
		TIM_SetCompare1(ADVANCE_TIM, 185); //对应90度
        delay_ms(delay_time);
		TIM_SetCompare1(ADVANCE_TIM, 190); //对应45度
        delay_ms(delay_time);
		TIM_SetCompare1(ADVANCE_TIM, 195); //对应0度
	}
}

