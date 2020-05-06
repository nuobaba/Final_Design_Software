/******************************************************************
 * 文件：main.c
 * 功能：主函数入口
 * 日期：2018-02-16
 * 作者：zx
 * 版本：Ver.1.0 | 最初版本
 * 官博：http://fengmeitech.club
 * Copyright (C) 2017 zx. All rights reserved.
*******************************************************************/
#include "stdio.h"
#include "DELAY/Delay.h"
#include "UART/uart.h"
#include "ADC/ADC.h"
#include "LED/LED.h"
#include "IIC/IIC.h"
#include "OLED/OLED.h"
#include "SPIx/SPIx.h"
#include "SX1278/SX1278.h"
#include "Ds18b20.h"


int main(void)
{
	
	u8 i = 0;
	unsigned char tx[] = "ID: 00  T: 00.0"; //编码规则：ID+两位ID号+T+三位温度值
	u16 temper;    //用于获取温度值
	unsigned char T1,T2,T3;    //用于显示温度值
	unsigned char showTemp[] = "00.0";
	//u8 tx = 0;
	/*初始化各外设*/ 
    initSysTick();  
	initADC();
    initUART();           //波特率9600
	initLED();
	
	initIIC();
    initOLED();

    initSPIx(SPI2);
    initSX1278();

	formatScreen(0x00);
    for(i=0;i<=128;i+=2)  //风媒电子LOGO从左向右动态显示
    {
		showImage(0,0,i,8,LORA_LOGO_ENUM);
    }
		formatScreen(0x00);
		showString(15,0,"Device ID: 00",FONT_16_EN);

    while (1)
    {


				if( DS18B20_Init()==0 ) 
			{
				temper = DS18B20_Get_Temp();	
				printf("Temper:%d\r\n",temper);
				// T3 = temper%10; //小数位
				T3 = (char)(temper%10 +'0');
				//T2 = (temper/10)%10;// 个位
				T2 = (char)((temper/10)%10 +'0');
				//T1 = temper/100;// 十位
				T1 = (char)(temper/100 +'0');
				Delay_ms(500);
			}
			tx[11] = T1;
			tx[12] = T2;
			tx[14] = T3;
			showTemp[0] = T1;
			showTemp[1] = T2;
			showTemp[3] = T3;
		transmitPackets(&tx[0],sizeof(tx));
		showString(0,3,"Temper:",FONT_16_EN);
		showString(80,3,showTemp,FONT_16_EN);
		printf("DataSended is %s\n",tx);
        toggleLED();
        Delay_ms(1000);
			

		
    }
}

