#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "oled.h"
#include "printf.h"
#include "dht11.h"
#include "BH1750.h"
#include "CO2.h"
#include "esp8266_drive.h"
#include "sta_tcpclent_test.h"
#include "string.h"

u8  table[16]="Cppm=";
u8  temp_buf[3],humi_buf[3];
u8 table3[16]="light=";
float datalx=0.0;
int CO2Data; 
int lightData;
u8 res;	
char * pCh,*cCh;
u8 temp;  	    
u8 humi;
char str[100]={0};
char   str1[3] ={0};
char carbonStr[7]="C";
char temperatureStr[5]="T";
char humidityStr[5]="H";
char illumilationStr[7]="I";
char commandOpenStr1[9]="ESPKJDQ1";
char commandOpenStr2[9]="ESPKJDQ2";
char commandOpenStr3[9]="ESPKJDQ3";

char commandCloseStr1[9]="ESPGJDQ1";
char commandCloseStr2[9]="ESPGJDQ2";
char commandCloseStr3[9]="ESPGJDQ3";
void display_Cppm(u32 K,u8 *table);
char* intTostring(int value, char *string, int radix);

int main()
{
	int i =0 ;
  char str[10]={0};																	//intת�ַ�����ʱ�洢����	
	SystemInit();
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		//NVIC�жϷ���Ϊ1�飺һλ��ռ���ȼ���3λ�����ȼ�	
	RCC_Configuration();  														//����4(CO2ģ�鴮��)����     
  NVIC_Configuration();
  GPIO_Configuration();
	USART4_Init();
	printf_init(); 																		//printf����1����������Ϊ9600
	BH1750_Init();																		//����ǿ��ģ���ʼ��
	LED_Init();																			  //LED��ʼ��
	BEEP_Init();																			//��������ʼ��
	OLED_Init();																			//OLED��ʼ��  
	while(DHT11_Init()){															//DHT11��ʼ��,���DHT11�Ƿ���
		OLED_ShowString(0,0,"DHT11 ERROR!",16);
		OLED_Refresh_Gram();  //ˢ��GRAM����	
		delay_ms(500);		
	}
	
	OLED_ShowString(0,0,"DHT11 SUCCESS!",16);
	OLED_Clear();	
	OLED_ShowString(0,0,"Temp:    C",16);
	OLED_ShowString(0,16,"Humi:   %RH",16);
	OLED_Refresh_Gram();  //ˢ��GRAM����
	
	ESP8266_Init(9600);	
	printf ( "\r\n��������ESP8266�����ĵȴ�...\r\n" );
	ESP8266_CH_PD_Pin_SetH;
	ESP8266_AT_Test();
	//ESP8266_Net_Mode_Choose(STA);
	ESP8266_Net_Mode_Choose(STA_AP);
	printf("�ɹ�����ΪSTAģʽ\r\n");
	while(!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD));
	printf("�ɹ�����wifi�ȵ�\r\n");
	ESP8266_Enable_MultipleId ( ENABLE );
	
	//while (!ESP8266_CIPAP( ESP8266_TCPServer_IP ));
	while(!ESP8266_StartOrShutServer(ENABLE, ESP8266_TCPServer_PORT,User_ESP8266_TCPServer_OverTime ));
	ESP8266_Inquire_ApIp ( str, 20 );
	printf("�ɹ���������\r\n,����IP��ַΪ%s",str);
	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Multiple_ID_0));
	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer1_IP, User_ESP8266_TCPServer1_PORT, Multiple_ID_1));
//  while(!ESP8266_Link_Server(enumTCP, phone_ESP8266_TCPServer_IP, phone_ESP8266_TCPServer_PORT, Multiple_ID_1));
//	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer1_IP, User_ESP8266_TCPServer1_PORT, Multiple_ID_1));
//	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer2_IP, User_ESP8266_TCPServer2_PORT, Multiple_ID_2));
//	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer3_IP, User_ESP8266_TCPServer3_PORT, Multiple_ID_3));
	printf ( "\r\n����ESP8266 OK��\r\n" );	
	ESP8266_Fram_Record_Struct .InfBit .FramLength = 0;
	ESP8266_Fram_Record_Struct .InfBit .FramFinishFlag = 0;
	
	while(1){
		OLED_Clear();
		OLED_ShowString(0,0,"Temp:    C",16);
		OLED_ShowString(0,16,"Humi:   %RH",16);
		OLED_Refresh_Gram();  //ˢ��GRAM����
		USART_SendData_Length(UART4,readGasDensityCmd,9);	
		if(receiveFlag){
				CO2Data = chartoint(RxBuffer2[2])* 256 +chartoint(RxBuffer2[3]);
				printf("CO2Ũ��Ϊ��%d ppm\r\n",CO2Data);		  
				receiveFlag=0;
		}
		display_Cppm(CO2Data,table);
		OLED_ShowString(0,32,table,16);
		OLED_Refresh_Gram();  //ˢ��GRAM����				
		delay_ms(200); 
		
		data_pros(temp_buf,humi_buf);
		OLED_ShowString(8*5,0,temp_buf,16);		
	  OLED_Refresh_Gram();  //ˢ��GRAM����
			
	  OLED_ShowString(8*5,16,humi_buf,16);
	  OLED_Refresh_Gram();  //ˢ��GRAM����
			
		datalx =bh_data_read()/1.2; //�����ֲ��ȡ�����ݳ���1.2�͵õ���λλlx�Ĺ�ǿ�ȼ��ֵ��  
		display_Lx((unsigned int)datalx,table3);
		OLED_ShowString(0,48,table3,16);
		OLED_Refresh_Gram();  //ˢ��GRAM����
		delay_ms(300);
		
		strcpy(carbonStr,"C");
		strcpy(illumilationStr,"I");
		strcpy(temperatureStr,"T");
		strcpy(humidityStr,"H");		 		
		strcpy(str,"       ");		
		intTostring(CO2Data,str,10);
	  strcat(carbonStr,str);		
		strcpy(str,"      ");
		lightData=(int)datalx;
		intTostring(lightData,str,10);
		strcat(illumilationStr,str);	
		strcat(temperatureStr,(const char *)temp_buf );	
		strcat(humidityStr,(const char *)humi_buf );
	
		ESP8266_SendString ( DISABLE,carbonStr,strlen(carbonStr),Multiple_ID_0 );
		ESP8266_SendString ( DISABLE,illumilationStr,strlen(illumilationStr),Multiple_ID_0 );
		ESP8266_SendString ( DISABLE,temperatureStr,strlen(temperatureStr),Multiple_ID_0 );
		ESP8266_SendString ( DISABLE,humidityStr,strlen(humidityStr),Multiple_ID_0 );	
		
		if(lightData>800){
		//ESPKLED2
			 ESP8266_SendString ( DISABLE,commandCloseStr1,strlen(commandOpenStr1),Multiple_ID_1);	
			 printf("�ر�LED2\r\n");
		}
		else if(lightData<50){
		//ESPKLED2
			 ESP8266_SendString ( DISABLE,commandOpenStr1,strlen(commandOpenStr1),Multiple_ID_1);	
			 printf("��LED2\r\n");
		}
		
		if(lightData>800){
		//ESPKLED2
			 ESP8266_SendString ( DISABLE,commandCloseStr1,strlen(commandOpenStr1),Multiple_ID_1);	
			 printf("�ر�LED2\r\n");
		}
		else if(lightData<50){
		//ESPKLED2
			 ESP8266_SendString ( DISABLE,commandOpenStr1,strlen(commandOpenStr1),Multiple_ID_1);	
			 printf("��LED2\r\n");
		}

	  DHT11_Read_Data(&temp,&humi);
		if(humi > 40){
			 ESP8266_SendString ( DISABLE,commandCloseStr3,strlen(commandCloseStr3),Multiple_ID_1);
       delay_ms(500);			
			 ESP8266_SendString ( DISABLE,commandCloseStr2,strlen(commandCloseStr2),Multiple_ID_1);	
			 printf("�رռ̵���3��2\r\n");
		}
		else if(humi<25){
		   ESP8266_SendString ( DISABLE,commandOpenStr3,strlen(commandOpenStr3),Multiple_ID_1);
       delay_ms(500);			
			 ESP8266_SendString ( DISABLE,commandOpenStr2,strlen(commandOpenStr2),Multiple_ID_1);	
			 printf("�򿪼̵���3��2\r\n");
		}
		CLR_Buf();
//    ESP8266_SendString ( DISABLE,carbonStr,strlen(carbonStr),Multiple_ID_1 );
//		ESP8266_SendString ( DISABLE,illumilationStr,strlen(illumilationStr),Multiple_ID_1 );
//		ESP8266_SendString ( DISABLE,temperatureStr,strlen(temperatureStr),Multiple_ID_1 );
//		ESP8266_SendString ( DISABLE,humidityStr,strlen(humidityStr),Multiple_ID_1 );
//		ESP8266_SendString ( DISABLE,"ESPKLED1",strlen("ESPKLED1"),Multiple_ID_1 );		
//	  ESP8266_SendString ( DISABLE,"ESPKLED1",strlen("ESPKLED1"),Multiple_ID_2 );
	  delay_ms(1800);
	
		
		if( flag1||flag2||flag3)
		{
			printf("����\r\n");
			USART_ITConfig ( USART2, USART_IT_RXNE, DISABLE ); //���ô��ڽ����ж�		
			printf("start\r\n");
			printf ( "\r\n%s\r\n", ESP8266_Fram_Record_Struct .Data_RX_BUF );
			printf("end\r\n");			
			if(flag1){
					printf("flag1��λ\r\n");
					if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,1,4:1H" ) ) != 0 )   
					{
						printf("get humidity1\r\n");	
						//+IPD,1,4:1H47
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								humidity[0]=(*(cCh)-48)*10+(*(cCh+1)-48);
					}			
					if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,1,4:1T" ) ) != 0 ) 
					{
						printf("get temerature1\r\n");
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								temerature[0]=(*(cCh)-48)*10+(*(cCh+1)-48);			 
					}
					flag1 = 0;
			}
			
			if(flag2){
					printf("flag2��λ\r\n");
					if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,2,4:2H" ) ) != 0 )   
					{
						printf("get humidity2\r\n");	
						//+IPD,1,4:1H47
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								humidity[1]=(*(cCh)-48)*10+(*(cCh+1)-48);
					}			
					if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,2,4:2T" ) ) != 0 ) 
					{
						printf("get temerature2\r\n");
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								temerature[1]=(*(cCh)-48)*10+(*(cCh+1)-48);			 
					}
					 flag2 = 0;
				}
			if(flag3){
				printf("flag3��λ\r\n");
				if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,3,4:3H" ) ) != 0 )   
					{
						printf("get humidity3\r\n");	
						//+IPD,1,4:1H47
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								humidity[2]=(*(cCh)-48)*10+(*(cCh+1)-48);
					}			
					if ( ( pCh = strstr ( ESP8266_Fram_Record_Struct .Data_RX_BUF, "+IPD,3,4:3T" ) ) != 0 ) 
					{
						printf("get temerature3\r\n");
						cCh =  pCh + 11 ;
						if((*(cCh))&&(*(cCh+1)))
								temerature[2]=(*(cCh)-48)*10+(*(cCh+1)-48);			 
					}
					flag3 = 0;
			}		 	
			USART_ITConfig ( USART2, USART_IT_RXNE, ENABLE ); //ʹ�ܴ��ڽ����ж�
			printf("�뿪\r\n");
		}
		
		for ( i =0 ;i<3;i++){
			printf("��%d����ģ����¶�Ϊ:%d\r\n\r\n",i+1,temerature[i]);
			printf("��%d����ģ���ʪ��Ϊ:%d\r\n\r\n",i+1,humidity[i]);
		
		}
	  OLED_Clear();
		OLED_ShowString(0,0,"T1:     ",16);
		intTostring(temerature[0],str1,10);
		OLED_ShowString(8*3,0,str1,16);
		strcpy(str1,"   ");
		OLED_ShowString(64,0,"H1:     ",16);
		intTostring(humidity[0],str1,10);
		OLED_ShowString(64+8*3,0,str1,16);
		strcpy(str1,"   ");
		
		OLED_ShowString(0,16*1,"T2:     ",16);
		intTostring(temerature[1],str1,10);
		OLED_ShowString(8*3,16*1,str1,16);
		strcpy(str1,"   ");
		OLED_ShowString(64,16*1,"H2:     ",16);
		intTostring(humidity[1],str1,10);
		OLED_ShowString(64+8*3,16*1,str1,16);
		strcpy(str1,"   ");
		
		OLED_ShowString(0,16*2,"T3:     ",16);
		intTostring(temerature[2],str1,10);
		OLED_ShowString(8*3,16*2,str1,16);
		strcpy(str1,"   ");		
		OLED_ShowString(64,16*2,"H3:     ",16);
		intTostring(humidity[2],str1,10);
		OLED_ShowString(64+8*3,16*2,str1,16);
		strcpy(str1,"   ");
		OLED_Refresh_Gram();  //ˢ��GRAM����	
		delay_ms(1500);
		
		
		if(TcpClosedFlag) //����Ƿ�ʧȥ����
		{
			ESP8266_ExitUnvarnishSend(); //�˳�͸��ģʽ
			do
			{
				res = ESP8266_Get_LinkStatus();     //��ȡ����״̬
			} 	
			while(!res);
			
			if(res == 4)                     //ȷ��ʧȥ���Ӻ�����
			{
				printf ( "\r\n���Եȣ����������ȵ�ͷ�����...\r\n" );
				
				while (!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD ) );			
				while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Multiple_ID_0 ) );
        //while (!ESP8266_Link_Server(enumTCP, phone_ESP8266_TCPServer_IP, phone_ESP8266_TCPServer_PORT, Multiple_ID_1 ) );
	//			while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer1_IP, User_ESP8266_TCPServer1_PORT, Multiple_ID_0 ) );
	//			while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer2_IP, User_ESP8266_TCPServer2_PORT, Multiple_ID_0 ) );
	//			while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer3_IP, User_ESP8266_TCPServer3_PORT, Multiple_ID_3));
				printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );
			} 
			while(!ESP8266_UnvarnishSend());					
		}
	  led1=!led1;		
	}
}

void display_Cppm(u32 K,u8 *table)
{
	u8 count=0,num=0;
  u32 K0;
  K0=K;
  while(K)
  {
		 K=K/10;
		 count++;
  }
	
	for(num=4+count;num>4;num--)
  {
		table[num]=0x30;
	}
	
  for(num=4+count;num>4;num--)
  {
		table[num]=(u8)(K0%10+48);
		K0=K0/10;
  
	}	
	table[5+count]=0X70;
	table[6+count]=0X70;
	table[7+count]=0X6D;
	table[8+count]='\0';
	table[9+count]='\n';

} 

char* intTostring(int value, char *string, int radix)
{
  int     i, d;
	int     flag = 0;
	char    *ptr = string;
	if (radix != 10){
		*ptr = 0;
		return string;
	}
	if (!value){
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}
	if (value < 0){
		*ptr++ = '-';

		/* Make the value positive. */
		value *= -1;		
	}
	for (i = 10000; i > 0; i /= 10){
		d = value / i;

		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}

	*ptr = 0;
	return string;
}


