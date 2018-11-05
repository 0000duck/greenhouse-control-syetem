#include "input.h"

u8 TIM5CH1_CAPTURE_STA=0; //���벶���״̬
u16 TIM5CH1_CAPTURE_VAL=0;//���벶��ֵ
u32 Cppm=0,High_length=0,Low_length=0;
u8 high_flag=0;															
u8 low_flag=0;

void input_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//����һ���ṹ�������������ʼ����ʱ��
	TIM_ICInitTypeDef TIM5_ICInitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	/* ������ʱ��5ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	 //ʹ��TIM5ʱ��

		//���״̬�Ĵ���(TIMx_SR)�ĵ�һ�ڶ�λ(CC1IF�� 
	  //����/�Ƚ�1 �жϱ�� (Capture/Compare 1 interrupt flag))
		//UIF�� �����жϱ�� (Update interrupt flag)
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update|TIM_IT_CC1); //����жϺͲ����־λ

	TIM_TimeBaseInitStructure.TIM_Period = 0xffff;	 //�趨�������Զ���װֵ 	
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;   //��1Mhz��Ƶ�ʼ��� һ�μ���1us
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	  //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //ѡ������� IC1ӳ�䵽TI1�� 
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //�����ز��� 
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1�� 
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00; //IC1F=0000 ���������˲��� ���˲� 
	TIM_ICInit(TIM5, &TIM5_ICInitStructure); //��ʼ��TIM5���벶��ͨ��1	
	
	//�жϷ����ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;	//��TIM5��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //��Ӧ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	  //ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܻ���ʧ��TIMx����
	TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE );	//ʹ�ܻ���ʧ��ָ����TIM�ж�
		
}

void inputCapture_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //����һ���ṹ�������������ʼ��GPIO

	/* ����GPIOʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;	   //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //���ô�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  /* ��ʼ��GPIO */
}


void TIM5_IRQHandler()	  //��ʱ��5���벶���жϺ���
{
	if(!low_flag)//��δ�ɹ�����
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	
		{
			if(TIM5CH1_CAPTURE_STA&0X40) //�Ѿ����񵽸ߵ�ƽ��
			{
					TIM5CH1_CAPTURE_STA++;	
			}
		}	
	}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //����1���������¼�
	{
		
		if((TIM5CH1_CAPTURE_STA&0X80)&&(TIM5CH1_CAPTURE_STA&0X40)) //�Ѿ�����һ���½���,�ֲ���һ����������
		{
			low_flag=1;  																//һ�β������ 
			TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5); //���TIMx���벶��1��ֵ

			Low_length=TIM5CH1_CAPTURE_STA&0x3f;
			Low_length=Low_length*65536;		  //���ʱ���ܺ�
			Low_length=Low_length+TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��		
			TIM5CH1_CAPTURE_STA=0; //������һ�ε͵�ƽ����
			
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //����Ϊ�����ز���			
		}
		
		else if(TIM5CH1_CAPTURE_STA&0X40) //�Ѿ�����һ��������,�ֲ���һ��������
		{
			high_flag=1;
			TIM5CH1_CAPTURE_STA|=0X80; //��ǳɹ�����һ���½��� 
			TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5); //���TIMx���벶��1��ֵ

			High_length=TIM5CH1_CAPTURE_STA&0x3f;
			High_length=High_length*65536;		            //���ʱ���ܺ�
			High_length=High_length+TIM5CH1_CAPTURE_VAL;  //�õ��ܵĸߵ�ƽʱ��		
			TIM5CH1_CAPTURE_STA&=(~0X3F);                 //�����������
			
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //����Ϊ�����ز���			
		}
		else													 //��δ����һ��������
		{
			TIM5CH1_CAPTURE_STA=0; //��� 
			TIM5CH1_CAPTURE_VAL=0; 
			TIM_SetCounter(TIM5,0); 
			TIM5CH1_CAPTURE_STA|=0X40; //��ǲ����������� 
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //����Ϊ�½��ز���
		}	
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}

