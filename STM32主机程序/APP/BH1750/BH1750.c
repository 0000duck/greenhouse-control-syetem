#include "BH1750.h"
	
void bh_data_send(u8 command)  
{  
    do{  
    I2C_Start();                      //iic��ʼ�ź�  
    I2C_Send_Byte(BHAddWrite);       //����������ַ  
    }while(I2C_Wait_Ack());           //�ȴ��ӻ�Ӧ��  
    I2C_Send_Byte(command);          //����ָ��  
    I2C_Wait_Ack();                   //�ȴ��ӻ�Ӧ��  
    I2C_Stop();                       //iicֹͣ�ź�  
}

u16 bh_data_read(void)  
{  
    u16 buf;  
    I2C_Start();                       //iic��ʼ�ź�  
    I2C_Send_Byte(BHAddRead);         //����������ַ+����־λ  
    I2C_Wait_Ack();                     //�ȴ��ӻ�Ӧ��  
    buf=I2C_Read_Byte(1);              //��ȡ����  
    buf=buf<<8;                        //��ȡ������߰�λ����  
    buf+=0x00ff&I2C_Read_Byte(0);      //��ȡ������ڰ�λ����  
    I2C_Stop();                        //����ֹͣ�ź�   
    return buf;   
}

void BH1750_Sensitivity(u8 high_type,u8 low_type)
{
		I2C_Start();                          //��ʼ�ź�
    I2C_Send_Byte(BHAddWrite);   //�����豸��ַ+д�ź�
		I2C_Wait_Ack();
		I2C_Send_Byte(high_type);   //�����豸��ַ+д�ź�
		I2C_Wait_Ack();
		I2C_Stop();
	
		I2C_Start();                          //��ʼ�ź�
    I2C_Send_Byte(BHAddWrite);   //�����豸��ַ+д�ź�
		I2C_Wait_Ack();
		I2C_Send_Byte(low_type);   //�����豸��ַ+д�ź�
		I2C_Wait_Ack();
		I2C_Stop();
}

void BH1750_Sensitivity_Control(u8 mode)
{
		switch(mode)
		{
			case 1:
				BH1750_Sensitivity(0X40,0X7F);
				break;
			case 2:
				BH1750_Sensitivity(0X42,0X65);
				break;
			case 3:
				BH1750_Sensitivity(0X43,0X78);
				break;
			case 4:
				BH1750_Sensitivity(0X47,0X7E);
				break;
		}
}
void BH1750_Init(void)
{
	  I2C_INIT();
		bh_data_send(BHPowOn);    //������������  
    bh_data_send(BHReset);    //����Ĵ�������  
    bh_data_send(BHModeH2);   //���ø߾���Ϊģʽ2  
    delay_ms(180);            //������ɺ�Ҫ��һ���ӳ٣��ֲ���˵���180ms�Ϳ�����
}

void display_Lx(unsigned int Lx,u8 *table3)				//������ʾ����
{
	u8 count=0,num=0;
  unsigned int Lx0;
  Lx0=Lx;
  while(Lx)
  {
		 Lx=Lx/10;
		 count++;
  }
	
	for(num=5+count;num>5;num--)
  {
		table3[num]=0x30;
	}
	
  for(num=5+count;num>5;num--)
  {
		table3[num]=(u8)(Lx0%10+48);
		Lx0=Lx0/10;
  
	}
	table3[6+count]=' ';
	table3[7+count]='l';
	table3[8+count]='x';
	table3[9+count]='\0';
}	
