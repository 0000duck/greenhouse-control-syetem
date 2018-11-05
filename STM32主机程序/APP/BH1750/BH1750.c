#include "BH1750.h"
	
void bh_data_send(u8 command)  
{  
    do{  
    I2C_Start();                      //iic起始信号  
    I2C_Send_Byte(BHAddWrite);       //发送器件地址  
    }while(I2C_Wait_Ack());           //等待从机应答  
    I2C_Send_Byte(command);          //发送指令  
    I2C_Wait_Ack();                   //等待从机应答  
    I2C_Stop();                       //iic停止信号  
}

u16 bh_data_read(void)  
{  
    u16 buf;  
    I2C_Start();                       //iic起始信号  
    I2C_Send_Byte(BHAddRead);         //发送器件地址+读标志位  
    I2C_Wait_Ack();                     //等待从机应答  
    buf=I2C_Read_Byte(1);              //读取数据  
    buf=buf<<8;                        //读取并保存高八位数据  
    buf+=0x00ff&I2C_Read_Byte(0);      //读取并保存第八位数据  
    I2C_Stop();                        //发送停止信号   
    return buf;   
}

void BH1750_Sensitivity(u8 high_type,u8 low_type)
{
		I2C_Start();                          //起始信号
    I2C_Send_Byte(BHAddWrite);   //发送设备地址+写信号
		I2C_Wait_Ack();
		I2C_Send_Byte(high_type);   //发送设备地址+写信号
		I2C_Wait_Ack();
		I2C_Stop();
	
		I2C_Start();                          //起始信号
    I2C_Send_Byte(BHAddWrite);   //发送设备地址+写信号
		I2C_Wait_Ack();
		I2C_Send_Byte(low_type);   //发送设备地址+写信号
		I2C_Wait_Ack();
		I2C_Stop();
}

void BH1750_Sensitivity_Control(u8 mode)
{
		switch(mode)
		{
			case 1:
				BH1750_Sensitivity(0X40,0X7F);
				break;
			case 2:
				BH1750_Sensitivity(0X42,0X65);
				break;
			case 3:
				BH1750_Sensitivity(0X43,0X78);
				break;
			case 4:
				BH1750_Sensitivity(0X47,0X7E);
				break;
		}
}
void BH1750_Init(void)
{
	  I2C_INIT();
		bh_data_send(BHPowOn);    //发送启动命令  
    bh_data_send(BHReset);    //清除寄存器内容  
    bh_data_send(BHModeH2);   //设置高精度为模式2  
    delay_ms(180);            //设置完成后要有一段延迟，手册上说最大180ms就可以了
}

void display_Lx(unsigned int Lx,u8 *table3)				//电阻显示函数
{
	u8 count=0,num=0;
  unsigned int Lx0;
  Lx0=Lx;
  while(Lx)
  {
		 Lx=Lx/10;
		 count++;
  }
	
	for(num=5+count;num>5;num--)
  {
		table3[num]=0x30;
	}
	
  for(num=5+count;num>5;num--)
  {
		table3[num]=(u8)(Lx0%10+48);
		Lx0=Lx0/10;
  
	}
	table3[6+count]=' ';
	table3[7+count]='l';
	table3[8+count]='x';
	table3[9+count]='\0';
}	
