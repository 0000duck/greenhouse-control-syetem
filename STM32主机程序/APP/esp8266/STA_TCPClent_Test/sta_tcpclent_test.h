#ifndef _sta_tcpclent_test_H
#define _sta_tcpclent_test_H


#include "system.h"


#define User_ESP8266_SSID	  "PUZHONG"	       
#define User_ESP8266_PWD	  "puzhong168"	  

#define ESP8266_TCPServer_IP	  "192.168.191.3"	  //服务器开启的IP地址
#define ESP8266_TCPServer_PORT	  "8080"	  //服务器开启的端口
#define User_ESP8266_TCPServer_OverTime	  "1800"	  //服务器超时时间（单位：秒）

#define User_ESP8266_TCPServer_IP	  "192.168.191.1"	 
#define User_ESP8266_TCPServer_PORT	  "8080"	

#define User_ESP8266_TCPServer1_IP	  "192.168.191.2"	 
#define User_ESP8266_TCPServer1_PORT	  "5000"	

//#define phone_ESP8266_TCPServer_IP	  "192.168.191.3"	 
//#define phone_ESP8266_TCPServer_PORT	  "5000"	

//#define User_ESP8266_TCPServer1_IP	  "192.168.191.2"	 
//#define User_ESP8266_TCPServer1_PORT	  "5000"	

//#define User_ESP8266_TCPServer2_IP	  "192.168.191.3"	 
//#define User_ESP8266_TCPServer2_PORT	  "5000"

//#define User_ESP8266_TCPServer3_IP	  "192.168.191.4"	 
//#define User_ESP8266_TCPServer3_PORT	  "5000"

extern volatile uint8_t TcpClosedFlag; 


void ESP8266_STA_TCPClient_Test(void);



#endif
