#include "lpc1768_i2c.h"
#include "lpc1768_rtc.h"
#include "LCD.h"

unsigned char wrdata[10];
unsigned char rddata[10];
int ss (void)
{
	RTCTime LocalTime;
	uint32_t i;
I2C_InitTypeDef I2C_InitStruct;
I2C_InitStruct.Mode = I2C_MASTER;
I2C_InitStruct.ClockRate = 400000;
I2C_InitStruct.InterruptMode = I2C_INTERRUPT_MODE;
I2C0_Init( &I2C_InitStruct ); /* initialize I2c */
	
		LocalTime = RTC_GetTime();
	sprintf( wrdata, "%04d-%02d-%02d", LocalTime.RTC_Year, LocalTime.RTC_Mon, LocalTime.RTC_Mday );
E2PROM_WriteSeq(0x0,wrdata, 10);
	i=150000;
	while(i--);
/* delay here, or break point here */
/* ������ʹ�öϵ㣬ͣ��һ�£��ȴ�д����� */
E2PROM_ReadSeq(0x0, rddata, 10);
/* ������ʹ�öϵ㣬ͨ��Watch���ڹ۲���� */
	i=150000;
	while(i--);
	LCD_DisplayString( 155, 32, rddata ); //��ʾ�������ʱ���֡���
}