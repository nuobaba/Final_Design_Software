#ifndef __DS18B20_H
#define __DS18B20_H 
#include "stm32f10x.h"  

#define DS18B20_IO_IN()   {	GPIO_InitTypeDef GPIO_InitStructure;GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;GPIO_Init(GPIOA, &GPIO_InitStructure);}	
						              //初始化IO口为上拉输入
#define DS18B20_IO_OUT()   { GPIO_InitTypeDef GPIO_InitStructure;GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;GPIO_Init(GPIOA, &GPIO_InitStructure);}
													//初始化IO口为推挽输出
////IO操作函数											   

#define DS18B20_DQ_OUT_PORT              GPIOA
#define DS18B20_DQ_OUT_CLK               RCC_APB2Periph_GPIOA 
#define DS18B20_DQ_OUT_PIN        			 GPIO_Pin_10		  //接DS18B20的IO口PA10

#define Set_DS18B20_DQ_OUT   {GPIO_SetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN );}
#define Clr_DS18B20_DQ_OUT   {GPIO_ResetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN );} 

#define DS18B20_DQ_IN_PORT              GPIOA
#define DS18B20_DQ_IN_CLK               RCC_APB2Periph_GPIOA  
#define DS18B20_DQ_IN_PIN        			  GPIO_Pin_10
 
#define DS18B20_DQ_IN   (GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT, DS18B20_DQ_IN_PIN ))
   	
u8 DS18B20_Init (void);//初始化DS18B20
short DS18B20_Get_Temp (void);//获取温度
void DS18B20_Start (void);//开始温度转换
void DS18B20_Write_Byte (u8 dat);//写入一个字节
u8 DS18B20_Read_Byte (void);//读出一个字节
u8 DS18B20_Read_Bit (void);//读出一个位
u8 DS18B20_Check (void);//检测是否存在DS18B20
void DS18B20_Rst (void);//复位DS18B20  

extern void Delay_us(u32 nus);

#endif

















