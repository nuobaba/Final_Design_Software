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

#define ALARM 22

int main(void)
{
	u8 i = 0;
	int temper = 0;
	unsigned char rx[20];
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
		showImage(0,0,i,8,LORA_LOGO);
    }
	formatScreen(0x00);

    while (1)
    {
        receivePackets(&rx[0]);
		temper = (int)(rx[11]-'0')*10 + (int)(rx[12]-'0');
		printf("%s\n",rx);
			printf("%d\n", temper);
		//showNumber(0,2,rx,DEC,3,FONT_16_EN);
			showString(0,1,rx,FONT_16_EN);
			if(temper < ALARM)
			{
				showString(35,4,"NORMAL",FONT_16_EN);
			}else{
				showString(35,4,"ALARM!",FONT_16_EN);
			}
		toggleLED();
        Delay_ms(500);
    }
}

