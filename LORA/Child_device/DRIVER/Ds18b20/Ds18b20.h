#ifndef __DS18B20_H
#define __DS18B20_H 
#include "stm32f10x.h"  

#define DS18B20_IO_IN()   {	GPIO_InitTypeDef GPIO_InitStructure;GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;GPIO_Init(GPIOA, &GPIO_InitStructure);}	
						              //��ʼ��IO��Ϊ��������
#define DS18B20_IO_OUT()   { GPIO_InitTypeDef GPIO_InitStructure;GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;GPIO_Init(GPIOA, &GPIO_InitStructure);}
													//��ʼ��IO��Ϊ�������
////IO��������											   

#define DS18B20_DQ_OUT_PORT              GPIOA
#define DS18B20_DQ_OUT_CLK               RCC_APB2Periph_GPIOA 
#define DS18B20_DQ_OUT_PIN        			 GPIO_Pin_10		  //��DS18B20��IO��PA10

#define Set_DS18B20_DQ_OUT   {GPIO_SetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN );}
#define Clr_DS18B20_DQ_OUT   {GPIO_ResetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN );} 

#define DS18B20_DQ_IN_PORT              GPIOA
#define DS18B20_DQ_IN_CLK               RCC_APB2Periph_GPIOA  
#define DS18B20_DQ_IN_PIN        			  GPIO_Pin_10
 
#define DS18B20_DQ_IN   (GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT, DS18B20_DQ_IN_PIN ))
   	
u8 DS18B20_Init (void);//��ʼ��DS18B20
short DS18B20_Get_Temp (void);//��ȡ�¶�
void DS18B20_Start (void);//��ʼ�¶�ת��
void DS18B20_Write_Byte (u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte (void);//����һ���ֽ�
u8 DS18B20_Read_Bit (void);//����һ��λ
u8 DS18B20_Check (void);//����Ƿ����DS18B20
void DS18B20_Rst (void);//��λDS18B20  

extern void Delay_us(u32 nus);

#endif

















