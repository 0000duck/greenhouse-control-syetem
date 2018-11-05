/************************************************************************************
Copyright,  LCES (WIND TALKER)  
程序名称：DHT11温湿度测量（晶振频率12MHz） 
功能说明: 间隔2秒，串口传送温湿度数据，单片机IO口为P5.4；
          波特率9600，数据位8，奇偶效验无，停止位1，数据流控制无
程序版本：1.0 （2014/06）
阿里旺旺：rob1983
淘宝店铺：http://shop67639654.taobao.c
************************************************************************************/

#include "stc15f2k60s2.h"	    // 单片机STC15F2K60S2头文件,可以不再加入reg51.h
#include <intrins.h>			    // 加入此头文件后,可使用_nop_库函数
#include "uart.h"				      // 串口1初始化、字符与字符串发送程序
#include <stdio.h>
#include "delay.h"				    // 延时程序头文件 
#include "oled12864.h"				// 128*64 OLED驱动程序


sbit  Sensor_SDA   = P1^7 ;

unsigned char  FLAG=0,temp=0;
unsigned char str[5]={0x00,0x00,0x00,0x00,0x00};
void Clear_Data (void);

unsigned char COM(void)
{
     unsigned char i,U8comdata ;      
     for(i=0;i<8;i++)	   
	 {		
	   	FLAG=2;	
	   	while((!Sensor_SDA )&&FLAG++);
		DelayUS(30);
	  	temp=0;
	    if(Sensor_SDA )temp=1;
		FLAG=2;
		while((Sensor_SDA )&&FLAG++);
	   	//超时则跳出for循环		  
	   	if(FLAG==1)break;
	   	//判断数据位是0还是1	 	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 	   	 
		U8comdata<<=1;
	   	U8comdata|=temp;        //0
	  }//rof
	  return  U8comdata	;
}



void RH(void)
{
     unsigned char  checkdata_temp;
	  //主机拉低18ms 
     Sensor_SDA =0;
	   DelayMS(18);
	   Sensor_SDA =1;
	 //总线由上拉电阻拉高 主机延时20us
	   DelayUS(40);
	 //主机设为输入 判断从机响应信号 
	   Sensor_SDA =1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	   if(!Sensor_SDA )		 //T !	  
	   {
		   FLAG=2;
		 //判断从机是否发出 80us 的低电平响应信号是否结束	 
		   while((!Sensor_SDA )&&FLAG++);
		   FLAG=2;
		 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		   while((Sensor_SDA )&&FLAG++);
		 //数据接收状态		 
	
		  str[0]= COM();
		  str[1]= COM();
		  str[2]= COM();
		  str[3]= COM();
		  str[4]= COM();			 
				 
		  Sensor_SDA =1;
		 //数据校验 
	      checkdata_temp= str[4];
		   temp=(str[0]+str[1]+str[2]+str[3]);
		   if(temp==checkdata_temp)
			   {	 
			   }
	   }
}
	
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
void DHT11_Read_Data(byte *temp,byte *humi)    
{   	 
	RH();	 //调用温湿度读取子程序                                                                                    
	 
	*humi=str[0];
	*temp=str[2];		
	 
}

void data_pros(byte *temp_buf,byte *humi_buf)	//数据处理函数
{
	byte temp;  	    
	byte humi;
	DHT11_Read_Data(&temp,&humi);
	temp_buf[0]=temp/10+0x30;	
	temp_buf[1]=temp%10+0x30;
	temp_buf[2]='\0';
	 
		
	humi_buf[0]=humi/10+0x30;	
	humi_buf[1]=humi%10+0x30;
	humi_buf[2]='\0';
 		
}

void Clear_Data (void)
  {
	int i;
	for(i=0;i<5;i++)
	{
	   str[i] = 0x00;
	 }
  }
