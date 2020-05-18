#include "stm32f10x.h"
#include "IIC.h"


int x,y,z,X,Y,Z;
float Get_Current_Angle()  
{  
  u8 i;  
  u8 a[6];  
  float Curent_Angle;  
  HMC5883L_Init();  
  i2c_Start();  
  i2c_SendByte(HMC5883L_Write_Address);  
  i2c_WaitAck();  
  i2c_SendByte(0x03);  
  i2c_WaitAck();  
    
  i2c_Start();  
  i2c_SendByte(HMC5883L_Read_Address);  
  i2c_WaitAck();  
  for(i=0;i<6;i++)  
  {  
    a[i] = i2c_ReadByte();  
    if(i==5)  
    {  
      i2c_NAck();  
    }  
    else  
    {  
      i2c_Ack();  
    }  
  }  
  i2c_Stop();  
  x=a[0];  
  x=x<<8;  
  x=x|a[1];  
  y=a[2];  
  y=y<<8;  
  y=y|a[3];  
  z=a[4];  
  z=z<<8;  
  z=z|a[5];  
  if(x>32768)  
  {  
    x = -(0xFFFF - x + 1);  
  }  
    
  if(y>32768)  
  {  
    y = -(0xFFFF - y + 1);  
  }  
  if(z>32768)  
  {  
    z = -(0xFFFF - z + 1);  
  }  
  X = (s16)x;    //x分量  
  Y = (s16)y;    //y分量  
  Z = (s16)z;    //z分量  
  Curent_Angle = (atan2(Y,X) * (180 / 3.14159265) + 180);  //实际水平角度  
  return Curent_Angle;  
} 
