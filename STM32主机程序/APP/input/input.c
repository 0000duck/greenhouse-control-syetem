#include "input.h"

u8 TIM5CH1_CAPTURE_STA=0; //输入捕获的状态
u16 TIM5CH1_CAPTURE_VAL=0;//输入捕获值
u32 Cppm=0,High_length=0,Low_length=0;
u8 high_flag=0;															
u8 low_flag=0;

void input_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//声明一个结构体变量，用来初始化定时器
	TIM_ICInitTypeDef TIM5_ICInitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启定时器5时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	 //使能TIM5时钟

		//清除状态寄存器(TIMx_SR)的第一第二位(CC1IF： 
	  //捕获/比较1 中断标记 (Capture/Compare 1 interrupt flag))
		//UIF： 更新中断标记 (Update interrupt flag)
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update|TIM_IT_CC1); //清除中断和捕获标志位

	TIM_TimeBaseInitStructure.TIM_Period = 0xffff;	 //设定计数器自动重装值 	
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;   //以1Mhz的频率计数 一次即是1us
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	  //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //TIM向上计数模式
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择输入端 IC1映射到TI1上 
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获 
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上 
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00; //IC1F=0000 配置输入滤波器 不滤波 
	TIM_ICInit(TIM5, &TIM5_ICInitStructure); //初始化TIM5输入捕获通道1	
	
	//中断分组初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;	//打开TIM5的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //响应优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	  //使能
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5,ENABLE); //使能或者失能TIMx外设
	TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE );	//使能或者失能指定的TIM中断
		
}

void inputCapture_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //声明一个结构体变量，用来初始化GPIO

	/* 开启GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//上拉输入  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  /* 初始化GPIO */
}


void TIM5_IRQHandler()	  //定时器5输入捕获中断函数
{
	if(!low_flag)//还未成功捕获
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	
		{
			if(TIM5CH1_CAPTURE_STA&0X40) //已经捕获到高电平了
			{
					TIM5CH1_CAPTURE_STA++;	
			}
		}	
	}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //捕获1发生捕获事件
	{
		
		if((TIM5CH1_CAPTURE_STA&0X80)&&(TIM5CH1_CAPTURE_STA&0X40)) //已经捕获到一个下降沿,又捕获到一个上升沿沿
		{
			low_flag=1;  																//一次捕获完成 
			TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5); //获得TIMx输入捕获1的值

			Low_length=TIM5CH1_CAPTURE_STA&0x3f;
			Low_length=Low_length*65536;		  //溢出时间总和
			Low_length=Low_length+TIM5CH1_CAPTURE_VAL;//得到总的高电平时间		
			TIM5CH1_CAPTURE_STA=0; //开启下一次低电平捕获
			
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //设置为上升沿捕获			
		}
		
		else if(TIM5CH1_CAPTURE_STA&0X40) //已经捕获到一个上升沿,又捕获到一个下跳沿
		{
			high_flag=1;
			TIM5CH1_CAPTURE_STA|=0X80; //标记成功捕获到一次下降沿 
			TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5); //获得TIMx输入捕获1的值

			High_length=TIM5CH1_CAPTURE_STA&0x3f;
			High_length=High_length*65536;		            //溢出时间总和
			High_length=High_length+TIM5CH1_CAPTURE_VAL;  //得到总的高电平时间		
			TIM5CH1_CAPTURE_STA&=(~0X3F);                 //溢出次数清零
			
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //设置为上升沿捕获			
		}
		else													 //还未捕获到一个上升沿
		{
			TIM5CH1_CAPTURE_STA=0; //清空 
			TIM5CH1_CAPTURE_VAL=0; 
			TIM_SetCounter(TIM5,0); 
			TIM5CH1_CAPTURE_STA|=0X40; //标记捕获到了上升沿 
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //设置为下降沿捕获
		}	
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

