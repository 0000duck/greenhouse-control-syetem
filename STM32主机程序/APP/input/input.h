#ifndef _input_H
#define _input_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

extern u8 TIM5CH1_CAPTURE_STA; //输入捕获的状态
extern u16 TIM5CH1_CAPTURE_VAL;//输入捕获值

extern u32 Cppm,High_length,Low_length;
extern u8 high_flag;															
extern u8 low_flag;

void inputCapture_Init(void);
void input_init(void);
void display_Cppm(u32 K,u8 *table);
#endif
