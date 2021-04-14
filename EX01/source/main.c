#include "lpc17xx.h"
// // #include "led.h"
// // #include "lpc1768_timer.h"
// // #include "joystick.h"
// // #include "key.h"
#include "bmboard.h"
// #include "lpc1768_i2c.h"
#include <stdio.h>
#include <string.h>
// #include "logo.h"
#include "lpc1768_rtc.h"
#include "lpc1768_timer.h"
#include "lpc1768_timer.h"
#include "joystick.h"
#include "LCD.h"

extern volatile unsigned short TextColor, BackColor;
uint16_t X=0, Y=0, XL=0, YL=0;
extern uint32_t DelayCounter;
char *LOCATION="Home";
char *DOCK="Home";


void main( void )
{
	uint8_t temp=0;
	uint32_t i, mon;
	char time[10], date[12];  
	RTCTime LocalTime;
	KEY_TypeDef key; //�������򰴼��ṹ��
	
	DelayCounter=300;
	Timer_Init(0); //��ʼ����ʱ��
	
	RTC_Init();
	
	LED_Config(); //��ʼ��LED
	
	Joystick_Config(); //��ʼ������״̬��
	
	LCD_Init();
// 	LCD_SetTextColor (LCD_COLOR_WHITE);
// 	LCD_SetBackColor (LCD_COLOR_BLACK);
	LCD_ClearScreen( BackColor ); //����
	Always();
	
	LocalTime = RTC_GetTime(); //��ȡ��ǰ�·�
	mon = LocalTime.RTC_Mon;
	Home(0);
	
	while(1)
	{
		i = 10000;
		while( i-- ) //�ӳ�һ��ʱ��
		{
			if( DelayCounter>300 )
			{
				if( temp==0 )
				{
					Square( X, Y, XL, YL, TextColor );
					temp++;
				}
				else if( temp==1 )
				{
					Square( X, Y, XL, YL, BackColor );
					temp = 0;
				}
				DelayCounter = 300;
			}

			if( SecondInt )
			{
				LocalTime = RTC_GetTime();
				if( mon!=LocalTime.RTC_Mon && strcmp(DOCK,"Home")==0 )  //����·ݷ����䶯����������
					Home(0);
				mon = LocalTime.RTC_Mon;
				
				sprintf( date, "%04d-%02d-%02d", LocalTime.RTC_Year, LocalTime.RTC_Mon, LocalTime.RTC_Mday );
				LCD_DisplayString2( 6, 10, date ); //��ʾ����
				
				sprintf( time, "%02d:%02d:%02d", LocalTime.RTC_Hour, LocalTime.RTC_Min, LocalTime.RTC_Sec );
				LCD_DisplayString2( 6, 182, time ); //��ʾʱ��
				
				SecondInt = 0;
			}
		}

		key = GetKey(); //��ȡ���µ����ĸ���

		if( key.KeyValue && key.Pressed )
		{
			if( strcmp(DOCK,"Home")==0 )
				Home( key.KeyValue );
			
			else if( strcmp(DOCK,"Date")==0 )
				Date( key.KeyValue );
			
			else if( strcmp(DOCK,"Time")==0 )
				Time( key.KeyValue );
			
			else if( strcmp(DOCK,"More")==0 )
				More( key.KeyValue );
		}
		if( key.KeyValue && key.Released )
		{
			if( strcmp(DOCK,"SetTime")==0 )
			{
				if( key.KeyValue==KEY_VALUE_UP )
					LCD_DisplayString2( 50, 250, "UP" );
				else if( key.KeyValue==KEY_VALUE_DOWN )
					LCD_DisplayString2( 50, 250, "DO" );
			}
			if( strcmp(DOCK,"SetDate")==0 )
			{
				if( key.KeyValue==KEY_VALUE_UP )
					LCD_DisplayString2( 50, 250, "UP" );
				else if( key.KeyValue==KEY_VALUE_DOWN )
					LCD_DisplayString2( 50, 250, "DO" );
			}
		}
	}
}
// 	LCD_ShowBmp (  10,   10, 100,  124, (uint16_t*)logo);
