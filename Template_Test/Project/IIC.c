#include "stm32f10x.h"
#include "IIC.h"
#include "sys.h"
#include "delay.h"



void IIC_IO_Init(void)
{					 
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//��1?��GPIOB����?��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_SCL|GPIO_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; //��?������?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(IIC_PERIPH, &GPIO_InitStructure);
  GPIO_SetBits(IIC_PERIPH,GPIO_Pin_8|GPIO_Pin_9); 	//PB6,PB7 ��?3???
}
 
void i2c_Start(void)  
{  
  /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */  
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
  /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */  
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
  /* �ȷ����ֽڵĸ�λbit7 */  
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
      IIC_SDA = 1; // �ͷ�����  
    }  
    _ucByte <<= 1;    /* ����һ��bit */  
    delay_us(10);  
  }  
}  
u8 i2c_ReadByte(void)  
{  
  u8 i;  
  u8 value;  
  IIC_SDA = 1;  
  SDA_IN();
  /* ������1��bitΪ���ݵ�bit7 */  
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
  IIC_SDA = 1;  /* CPU�ͷ�SDA���� */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */  
  delay_us(10);  
  if (READ_SDA)   /* CPU��ȡSDA����״̬ */  
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
  IIC_SDA = 0;  /* CPU����SDA = 0 */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU����1��ʱ�� */  
  delay_us(10);  
  IIC_SCL = 0;  
  delay_us(10);  
  IIC_SDA = 1;  /* CPU�ͷ�SDA���� */  
}  
void i2c_NAck(void)  
{  
  SDA_OUT();
  IIC_SDA = 1;  /* CPU����SDA = 1 */  
  delay_us(10);  
  IIC_SCL = 1;  /* CPU����1��ʱ�� */  
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
