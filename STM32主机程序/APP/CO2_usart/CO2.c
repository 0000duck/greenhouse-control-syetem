#include "CO2.h"

 
u8 receiveFlag=0;
char RxBuffer2[10]={0};
u8  readGasDensityCmd[10]={
			0XFF,0X01,0X86,0X00,
			0X00,0X00,0X00,0X00,
			0X79,
}; 
static char checksum=0;
static char RxCounter2 =0;

//����4ʱ��ʹ��.
void RCC_Configuration(void)
{   
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  /* Enable USART4 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);  
}
/*
	����4�˿ڳ�ʼ��
*/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  /* Configure USART4 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

  /* Configure USART4 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
}

/*
����4�ж�����Ϊ��ռ���ȼ�Ϊ0���������ȼ�Ϊ0��
*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USART4 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
	����4����Ϊ������9600,
   8λ����λ��һλֹͣλ��
	����żУ��λ����Ӳ��������
  ����4�����ж�ʹ��
*/
void USART4_Init()
{
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(UART4, &USART_InitStructure);
	
   USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

  /* Enable the USART4 */
  USART_Cmd(UART4, ENABLE);	
}

int chartoint(char dat)
{
	int num=(dat&0XF0)>>4;
	num=(num<<4)+(dat&0X0F);
	return num;
}

void getCheckSum(char *packet)
{
	char i;
	for(i=1;i<8;i++)
	{
		checksum+=packet[i];
	}
	checksum=0XFF-checksum;
	checksum+=1;

}


void USART_SendData_Length(USART_TypeDef* USARTx, u8* Data,u16 length)  
{  
    u16 i;  
    for(i=0;i<length;i++)  
    {  
        USART_SendData(USARTx, Data[i]);//�򴮿ڷ�������  
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//�ȴ����ͽ���  
    }  
}

void UART4_IRQHandler(void)
{

  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
		RxBuffer2[RxCounter2++]  = USART_ReceiveData(UART4);//��ȡ9�ֽڵ�USART_RX_BUF_2  
		if(RxCounter2 == 9)  
		{		
			RxCounter2 = 0;//�����յ���9���ַ��󣬴�����USART_RX_BUF_1�Ŀ�ͷ��ʼд  
			getCheckSum(RxBuffer2);						
			if(checksum == RxBuffer2[8])//֤�����յ�����������ȷ��  
			{			
					receiveFlag=1;
			}
		}
		
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	}
} 	
