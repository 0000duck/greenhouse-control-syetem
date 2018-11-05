#ifndef _CO2_H
#define _CO2_H

#include "stm32f10x.h"


extern u8 receiveFlag;
extern  char RxBuffer2[10];
static char checksum;
static char RxCounter2;

extern u8  readGasDensityCmd[10]; 

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void getCheckSum(char *packet);
void USART4_Init(void);

void USART_SendData_Length(USART_TypeDef* USARTx, u8* Data,u16 length);
int chartoint(char dat);

#endif
