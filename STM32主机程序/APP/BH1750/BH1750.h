#ifndef _BH1750_H
#define _BH1750_H

#include "iic.h"
 
#define BHAddWrite     0x46      //�ӻ���ַ+���д����λ  
#define BHAddRead      0x47      //�ӻ���ַ+��������λ  
#define BHPowDown      0x00      //�ر�ģ��  
#define BHPowOn        0x01      //��ģ��ȴ�����ָ��  
#define BHReset        0x07      //�������ݼĴ���ֵ��PowerOnģʽ����Ч  
#define BHModeH1       0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms  
#define BHModeH2       0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms  
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms  
#define BHSigModeH     0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ  
#define BHSigModeH2    0x21      //ͬ������  
#define BHSigModeL     0x23      // ������

void bh_data_send(u8 command);
u16 bh_data_read(void) ;
void BH1750_Init(void);
void BH1750_Sensitivity(u8 high_type,u8 low_type);
void BH1750_Sensitivity_Control(u8 mode);
void display_Lx(unsigned int Lx,u8 *table3);

#endif
