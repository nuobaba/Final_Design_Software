#include "stm32f10x.h"
#include "IIC.h"
#include "sys.h"
#include "delay.h"



void IIC_IO_Init(void)
{					 
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ê1?üGPIOBê±?ó
  
  GPIO_InitStructure.GPIO_Pin = GPIO_SCL|GPIO_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; //í?íìê?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(IIC_PERIPH, &GPIO_InitStructure);
  GPIO_SetBits(IIC_PERIPH,GPIO_Pin_8|GPIO_Pin_9); 	//PB6,PB7 ê?3???
}
 
void i2c_Start(void)  
{  
  /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */  
  SDA_OUT();
  IIC_SDA = 1;  
  delay_us(10);  
  IIC_SCL = 1;  
  delay_us(10);  
  IIC_SDA = 0;  
  delay_us(10);  
  IIC_SCL = 0;  
  delay_us(10);  
}  
void i2c_Stop(void)  
{  
  /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */  
  SDA_OUT();
  IIC_SDA = 0;  
  delay_us(10);  
  IIC_SCL = 1;  
  delay_us(10);  
  IIC_SDA = 1;  
}  
void i2c_SendByte(u8 _ucByte)  
{  
  u8 i;  
  SDA_OUT();
  /* 先发送字节的高位bit7 */  
  for (i = 0; i < 8; i++)  
  {       
    if (_ucByte & 0x80)  
    {  
      IIC_SDA = 1;  
    }  
    else  
    {  
      IIC_SDA = 0;  
    }  
    delay_us(10);  
    IIC_SCL = 1;  
    delay_us(10);      
    IIC_SCL = 0;  
    if (i == 7)  
    {  
      IIC_SDA = 1; // 释放总线  
    }  
    _ucByte <<= 1;    /* 左移一个bit */  
    delay_us(10);  
  }  
}  
u8 i2c_ReadByte(void)  
{  
  u8 i;  
  u8 value;  
  IIC_SDA = 1;  
  SDA_IN();
  /* 读到第1个bit为数据的bit7 */  
  value = 0;  
  for (i = 0; i < 8; i++)  
  {  
    value <<= 1;  
    IIC_SCL = 1;  
    delay_us(10);  
    if (READ_SDA)  
    {  
      value++;  
    }  
    IIC_SCL = 0;  
    delay_us(10);  
  }  
  return value;  
}  
u8 i2c_WaitAck(void)  
{  
  u8 re;  
    SDA_IN();
  IIC_SDA = 1;  /* CPU释放SDA总线 */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */  
  delay_us(10);  
  if (READ_SDA)   /* CPU读取SDA口线状态 */  
  {  
    re = 1;  
  }  
  else  
  {  
    re = 0;  
  }  
  IIC_SCL = 0;  
  delay_us(10);  
  return re;  
}  
void i2c_Ack(void)  
{  
  SDA_OUT();
  IIC_SDA = 0;  /* CPU驱动SDA = 0 */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU产生1个时钟 */  
  delay_us(10);  
  IIC_SCL = 0;  
  delay_us(10);  
  IIC_SDA = 1;  /* CPU释放SDA总线 */  
}  
void i2c_NAck(void)  
{  
  SDA_OUT();
  IIC_SDA = 1;  /* CPU驱动SDA = 1 */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU产生1个时钟 */  
  delay_us(10);  
  IIC_SCL = 0;  
  delay_us(10);    
}  
void HMC5883L_Init()  
{  
  IIC_IO_Init();
  //i2c_CheckDevice(HMC5883L_Write_Address);  
  i2c_Start();  
  i2c_SendByte(HMC5883L_Write_Address);  
  i2c_WaitAck();  
  i2c_SendByte(0x00);  
  i2c_WaitAck();  
  i2c_SendByte(0x70);  
  i2c_WaitAck();  
  i2c_SendByte(0x01);  
  i2c_WaitAck();  
  i2c_SendByte(0xe0);  
  i2c_WaitAck();  
  i2c_SendByte(0x02);  
  i2c_WaitAck();  
  i2c_SendByte(0x01);  
  i2c_Stop();  
}
