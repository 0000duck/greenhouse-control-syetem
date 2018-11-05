#ifndef _led_H
#define _led_H

#include "system.h"

/*  LED时钟端口、引脚定义 */
//#define LED_PORT 			GPIOC
#define LED_PORT 			GPIOD
//#define LED_PIN 			(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED_PIN 			(GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11 )
//#define LED_PORT_RCC		RCC_APB2Periph_GPIOC
#define LED_PORT_RCC		RCC_APB2Periph_GPIOD

//#define led1 PCout(0)
//#define led2 PCout(1)
//#define led3 PCout(2)
//#define led4 PCout(3)
//#define led5 PCout(4)
//#define led6 PCout(5)
//#define led7 PCout(6)
//#define led8 PCout(7)
 
#define led1 PDout(8)
#define led2 PDout(9)
#define led3 PDout(10)
#define led8 PDout(11)
 
 
void LED_Init(void);


#endif
