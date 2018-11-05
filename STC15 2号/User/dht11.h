#ifndef __DHT11_H_
#define __DHT11_H_

#include "oled12864.h" 
void Clear_Data (void);
void DHT11_Read_Data(byte *temp,byte *humi);
void data_pros(byte *temp_buf,byte *humi_buf);	//数据处理函数
void RH(void);
#endif

