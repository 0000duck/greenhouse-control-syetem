/************************************************************************************
Copyright,  LCE STUDIO   
�������ƣ�ESP8266 WiFi����ģ��ͨ�ţ�18.432MHz�� 
����˵��:  1. �ó���ESP8266����ΪAP+STATION����ģʽ��������TCP ��������Ĭ��IPΪ192.168.4.1�� ���Ŷ˿�5000
					 2. �����ֻ���WIFI��������ESP_***�ȵ�󣬽������ӡ�
					 3. �򿪰�װ���ֻ��������������֣�ͨ��TCP CLIENT�ķ�ʽ����TCP������192.168.4.1���˿�5000���������ӡ�
					 4. �ֻ���TCP���������Ϳ���ָ����緢�͡�ESPKLED1���󣬽�����LED1��ͬʱģ�鷵�ء�Command Executed�� 

						ע�⣺����1�ʹ���2����һ��buffer,���յ�����1�ġ�ESPKLED1����Ҳ��ִ������ָ��
					        �򱾳�����Ϊ�����ã���ESP8266����Ϊ�ȵ�� ���ȵ��ǲ���Ҫ����ġ����ܹ�"AT+CWSAP"��������
 						      ����1�ʹ���2�����ʾ�Ϊ9600
����汾��1.0 ��2015/6/20��
����������rob1983
�Ա����̣�http://shop67639654.taobao.com 
************************************************************************************/


#include "stc15f2k60s2.h"	    // ��Ƭ��STC15F2K60S2ͷ�ļ�,���Բ��ټ���reg51.h
#include <intrins.h>					// �����ͷ�ļ���,��ʹ��_nop_�⺯��
#include "delay.h"		        // ��ʱ����ͷ�ļ�
#include "uart.h"		        	// ����ͨ�ź���ͷ�ļ�
#include <string.h>           // �����ͷ�ļ���,��ʹ��strstr�⺯��
#include "dht11.h"						// DHT11���ݴ������ͷ�ļ�
#include "oled12864.h"				// 128*64 OLED��������
#include "string.h"
#include "stdio.h"
sbit LCD_CS =P4^3; 

#define Buf_Max 50

unsigned char xdata Rec_Buf[Buf_Max];
unsigned char i = 0; 
byte temperatureStr[8]="2T";
byte humidityStr[8]="2H";
byte  temp_buf[3],humi_buf[3];
void CLR_Buf(void);				   
bit  Hand(unsigned char *a); 	
void ESP8266_SendString(  char * pStr, unsigned int ulStrLength  );
	 
sbit LED1 = P5^0;		    // ����LED1ΪP5.0 
sbit LED2 = P5^1;				// ����LED2ΪP5.1
sbit LED3 = P5^2;				// ����LED3ΪP5.2
sbit OP_relay = P3^5;		// �������̵�������I/OΪP3.5

char code str1[]="AT\r\n";                                    		    //  ����ָ�����"OK"
char code str2[]="AT+CWMODE=1\r\n";                         		      //  ����ESP8266�Ĺ���ģʽ������"OK"����"no change"
char code str3[]="AT+CWJAP=\"PUZHONG\",\"puzhong168\"\r\n";     			//  ���ӵ�WiFi�ȵ㣬lcesΪ�ȵ����ƣ�88518851Ϊ���룻���ӳɹ����ء�OK��     
char code str4[]="AT+CIFSR\r\n";                                   	  // 	����IP��ַ��ѯָ��
char code str5[]="AT+CIPSTART=\"TCP\",\"192.168.191.4\",8080\r\n";    //  ���ӵ�TCP�����������ء�Linked��
char code str6[]="AT+CIPSEND=6\r\n";   															  //  ��������ָ��
char code str7[]="hello!\r\n";   																			//  ��������
char code str8[]="AT+CIPSERVER=1,5000\r\n";   												//  ����TCP�����������Ŷ˿�8888							
char code str9[]="AT+CIPMUX=1\r\n";   																//	�򿪶�����	
char code str10[]="AT+RST\r\n"; 																			//  �����λ
char code str11[]="AT+CIPSEND=4\r\n";   														//  ��������ָ��,���ڶ�·����ģʽ
//char code str11[]="AT+CIPSEND=0,2\r\n";   														//  ��������ָ��,���ڶ�·����ģʽ
char code str12[]="Command Executed!\r\n";   													//  ��������

char code str13[]="hello!led1,good\r\n";
char code str14[]="hello!led2,good\r\n";
char code str15[]="hello!led3,good\r\n";
char code str16[]="hello!rel1,good\r\n";
char code str17[]="hello!rel2,good\r\n";
char code str18[]="hello!rel3,good\r\n";


void main()		                                  // ������     
{	
 
	P1M1 = 0x03;
	P1M0 = 0x03;
  P3M0 = 0x00;
  P3M1 = 0x00;
	P4M0 = 0X00;
	P4M1 = 0X00;	
  P5M0 = 0x00;
  P5M1 = 0x00;	
	LCD_CS= 0;
	LCD_Init();   

	LCD_Fill(0xff); 
	DelayMS(100); 
	LCD_Fill(0x00);
	DelayMS(100);     
	LCD_CLS();
	
	LCD_P8x16Str(25,0,"LCE STUDIO");

	LCD_P6x8Str(8,3,"DHT11 Test Program");
	LCD_P6x8Str(34,7,"2018-03-20");    
	DelayMS(100);  
	DelayUS(100);	
	UartInit();								                		// ��ʼ������
	ES = 1;                                       // ����1�жϴ�
	IE2 = 0x01;                                   // ����2�жϴ�
	EA = 1;                                       // ���жϴ�
	DelayMS(1000);							                  // ��ʱһ��ʱ�䣬��ESP8266����
	DelayUS(100);
  U1SendString(Rec_Buf);                        // ��ESP8266������Ϣͨ������1��ӡ��  
  U1SendString("\r\n");	
  U1SendString("Welcome to LCE STUDIO, Please wait while we are getting the device ready\r\n");	
	CLR_Buf();                                 		//�����������	

	while(!Hand("OK"))                            //�ж��Ƿ����ֳɹ�,������ɹ���ʱһ��,�ٷ���AT����ָ��
	{
		U2SendString(str1);                         //��������ָ�� 
		DelayMS(500);
	}
	CLR_Buf();                                    //�����������
  U1SendString("OK,Succeed Establish connection with ESP8266\r\n");		


	
	while(!(Hand("OK")|Hand("no change")))        //�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٴη���
	{		
		U2SendString(str2);                         //��������ESP8266����ģʽָ��	
		DelayMS(500);		
	}
	if(Hand("OK"))                                 
	{
			CLR_Buf();
			U2SendString(str10);                 
			DelayMS(500);			
	}
	CLR_Buf();                 
  U1SendString("OK,ESP8266 has been set as AP+Station Mode\r\n");	

	/*while(!Hand("OK"))                             
	{
		U2SendString(str9);                                //����Ϊ��·����       
		DelayMS(500);
	}
	 U1SendString("OK,ESP8266����Ϊ��·����\r\n");	
	CLR_Buf();

	*/
	while(!Hand("OK"))    										 		//�ж��Ƿ�����WiFi·�������粻�ɹ�����ʱ���ٴη���
	{		
		U2SendString(str3); 	
		DelayMS(2000);		
	}
	LED2 = 0;
	CLR_Buf();              
  U1SendString("OK,Succeed establish connection with WiFi AP\r\n");	
	
/*	while(!Hand("OK"))                                   // ����TCP �������������Ŷ˿�8888
	{
		U2SendString(str8);                          
		DelayMS(500);
	}
	U1SendString("OK,ESP8266����Tcp������\r\n");	
	
	CLR_Buf();	

	while(!Hand("OK"))                                    //  ��ѯģ�鵱ǰIP��ַ
	{
		U2SendString(str4);                          
		DelayMS(500);
	}
	
	U1SendString("OK,ESP8266��ѯ��ǰ��ַ�ɹ�\r\n");
	U1SendString(Rec_Buf);*/
	
		while(!Hand("CONNECTED"))                                    
	{
		U2SendString(str5);                          
		DelayMS(4000);
	}
	U1SendString("OK,ESP8266�ɹ�����Tcp������\r\n");
	
	U1SendString("Congratulations, Everything is set up! TCP sever:192.168.4.1, Port: 5000");
	CLR_Buf();	
	

  while (1)		                                        // ��ѭ��  
  {
 
		
			DelayMS(2200);		 
			data_pros(temp_buf,humi_buf);
			U1SendString("ʪ�Ⱥ��¶�����\r\n");
			U1SendString(temp_buf);
			U1SendString("\r\n");
			U1SendString(humi_buf);
			LCD_P6x8Str(8,5,"TEMP:");  
      LCD_P6x8Str(40,5,temp_buf);  
			LCD_P6x8Str(52,5,"C");  
			LCD_P6x8Str(80,5,"HUM:");  
			LCD_P6x8Str(110,5,humi_buf);  
			LCD_P6x8Str(122,5,"% ");  
			
			strcpy(temperatureStr,"2T");
		  strcpy(humidityStr,"2H");	
		  strcat(temperatureStr,(const char *)temp_buf );	
		  strcat(humidityStr,(const char *)humi_buf );
			U1SendString("���ӳɹ�\r\n");
		  U1SendString(temperatureStr);
		  U1SendString("\r\n");
			U1SendString(humidityStr);
			Clear_Data();
			U1SendString("\r\n");
			
			 while(!Hand("SEND OK"))     									//�ж��Ƿ������ݳɹ����粻�ɹ�����ʱ���ٴη���
			{

				U2SendString(str11); //���ݷ���ָ�� 
				DelayMS(100);		
				U2SendString(temperatureStr); //��������	
				DelayMS(500);
				
				U2SendString(str11); //���ݷ���ָ�� 
				DelayMS(100);		
				U2SendString(humidityStr); //��������	
				DelayMS(500);
			}
			CLR_Buf();  
			DelayMS(6000);
	/*		if(Hand("ESPGLED1"))                            //  �յ��ر�LED1��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED1 = 1;				
					CLR_Buf();
					U1SendString("Command: Turn off LED1, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str13);
					ES = 1;		
					IE2 = 0x01;						
				}  

				else if(Hand("ESPKLED1"))                     //  �յ�����LED1��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED1 = 0;				
					CLR_Buf();
					U1SendString("Command: Turn on LED1, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str13);					
					ES = 1;		
					IE2 = 0x01;				
				} 	
				
			else if(Hand("ESPGLED2"))                            //  �յ��ر�LED2��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED2 = 1;				
					CLR_Buf();
					U1SendString("Command: Turn off LED1, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str14);					
					ES = 1;		
					IE2 = 0x01;						
				}  
				
			else if(Hand("ESPKLED2"))                            //  �յ�����LED2��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED2 = 0;				
					CLR_Buf();
					U1SendString("Command: Turn on LED1, Executed!\r\n");	
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str14);					
					ES = 1;		
					IE2 = 0x01;				
				}

			else if(Hand("ESPGLED3"))                            //  �յ��ر�LED3��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED3 = 1;				
					CLR_Buf();
					U1SendString("Command: Turn off LED1, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str15);
					ES = 1;		
					IE2 = 0x01;						
				}  
				
			else if(Hand("ESPKLED3"))                            //  �յ�����LED3��ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					LED3 = 0;				
					CLR_Buf();
					U1SendString("Command: Turn on LED3, Executed!\r\n");
					U1SendString(temp_buf);
					U1SendString("\r\n");
					U1SendString(humi_buf);
					U1SendString("\r\n");
					U2SendString(str11);
					DelayMS(1);	
					
					//U2SendString(str15);	
					U2SendString( temp_buf);
					U2SendString( humi_buf);
					U2SendString("\r\n");
					ES = 1;		
					IE2 = 0x01;				
				} 	 	
				
			else if(Hand("ESPKJDQ1"))                            //  �յ����ϼ̵�����ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					OP_relay = 0;				
					CLR_Buf();
					U1SendString("Command: OP relay Enable, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str16);					
					ES = 1;		
					IE2 = 0x01;						
				}  
				
			else if(Hand("ESPGJDQ1"))                            //  �յ��Ͽ��̵�����ָ��
				{
					ES = 0; 
					IE2 = 0x00;					
					OP_relay = 1;				
					CLR_Buf();
					U1SendString("Command: OP relay Disable, Executed!\r\n");
					U2SendString(str11);
					DelayMS(1);		
					U2SendString(str16);					
					ES = 1;		
					IE2 = 0x01;				
				} 	 */					

   }
		
}

//ESP8266ģ�鷢���ַ���
//pStr��Ҫ���͵��ַ���
//ulStrLength��Ҫ���͵��ַ������ֽ���
void ESP8266_SendString(  char * pStr, unsigned int ulStrLength  )
{
	  char cStr [20];		
	  sprintf ( cStr, "AT+CIPSEND=%d", ulStrLength + 2 );	
		while(!Hand(">"))                                   
		{
			U2SendString(cStr);                          
			DelayMS(1000);
		}
		while(!Hand("SEND OK"))                              
		{
			U2SendString(pStr);                          
			DelayMS(1000);
		}
 
}
	
bit Hand(unsigned char *a)
{ 
    if(strstr(Rec_Buf,a)!=NULL)
	    return 1;
	else
		return 0;
}

void CLR_Buf(void)
{
	unsigned char k;
    for(k=0;k<Buf_Max;k++)    
	    {
			Rec_Buf[k] = 0;
		}
    i = 0;                    
}

void Uart1() interrupt 4 using 1
{
	ES = 0;
	if (RI)
    {
      RI = 0;                 //���RIλ
			Rec_Buf[i] = SBUF; 
			i++;               
			if(i>Buf_Max)          
				{
					i = 0;
				}           

    }
    if (TI)
    {
        TI = 0;                 //���TIλ

    }
		ES =  1;
}



void Uart2() interrupt 8 using 1
{
		IE2 = 0x00;	
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         
				Rec_Buf[i] = S2BUF; 
				i++;               
				if(i>Buf_Max)          
				{
					i = 0;
				}     
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;            
    }
		IE2 = 0x01;		
}