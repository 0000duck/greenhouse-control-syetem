/************************************************************************************
Copyright,  LCES (WIND TALKER)  
�������ƣ�DHT11��ʪ�Ȳ���������Ƶ��12MHz�� 
����˵��: ���2�룬���ڴ�����ʪ�����ݣ���Ƭ��IO��ΪP5.4��
          ������9600������λ8����żЧ���ޣ�ֹͣλ1��������������
����汾��1.0 ��2014/06��
����������rob1983
�Ա����̣�http://shop67639654.taobao.c
************************************************************************************/

#include "stc15f2k60s2.h"	    // ��Ƭ��STC15F2K60S2ͷ�ļ�,���Բ��ټ���reg51.h
#include <intrins.h>			    // �����ͷ�ļ���,��ʹ��_nop_�⺯��
#include "uart.h"				      // ����1��ʼ�����ַ����ַ������ͳ���
#include <stdio.h>
#include "delay.h"				    // ��ʱ����ͷ�ļ� 
#include "oled12864.h"				// 128*64 OLED��������


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
	   	//��ʱ������forѭ��		  
	   	if(FLAG==1)break;
	   	//�ж�����λ��0����1	 	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 	   	 
		U8comdata<<=1;
	   	U8comdata|=temp;        //0
	  }//rof
	  return  U8comdata	;
}



void RH(void)
{
     unsigned char  checkdata_temp;
	  //��������18ms 
     Sensor_SDA =0;
	   DelayMS(18);
	   Sensor_SDA =1;
	 //������������������ ������ʱ20us
	   DelayUS(40);
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	   Sensor_SDA =1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	   if(!Sensor_SDA )		 //T !	  
	   {
		   FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
		   while((!Sensor_SDA )&&FLAG++);
		   FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		   while((Sensor_SDA )&&FLAG++);
		 //���ݽ���״̬		 
	
		  str[0]= COM();
		  str[1]= COM();
		  str[2]= COM();
		  str[3]= COM();
		  str[4]= COM();			 
				 
		  Sensor_SDA =1;
		 //����У�� 
	      checkdata_temp= str[4];
		   temp=(str[0]+str[1]+str[2]+str[3]);
		   if(temp==checkdata_temp)
			   {	 
			   }
	   }
}
	
//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
void DHT11_Read_Data(byte *temp,byte *humi)    
{   	 
	RH();	 //������ʪ�ȶ�ȡ�ӳ���                                                                                    
	 
	*humi=str[0];
	*temp=str[2];		
	 
}

void data_pros(byte *temp_buf,byte *humi_buf)	//���ݴ�����
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
