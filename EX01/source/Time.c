
#include <stdio.h>
#include <string.h>
#include "lpc17xx.h"
#include "lpc1768_rtc.h"
#include "joystick.h"
#include "LCD.h"

extern volatile unsigned short TextColor, BackColor;
uint32_t HOUR, MIN, SEC;
extern uint16_t X, Y, XL, YL;
extern char *LOCATION;
extern char *DOCK;

void Gui_Time( void )
{
	char word[20];
	sprintf( word, "%02d:%02d:%02d", HOUR, MIN, SEC );
	LCD_DisplayString2( 88, 32, word ); //��ʾ�������ʱ���֡���
	
	Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾʱ���
	Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
	Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
	Square( 256-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾOK�����
	Square( 256-2, 128-1-2, 32+2+2, 24+2, TextColor ); //��ʾȡ�������
	
	if( strcmp(LOCATION,"hour")==0 ) //ʱ��˸���
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"min")==0 ) //����˸���
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"sec")==0 ) //����˸���
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"ok")==0 ) //ȷ�ϼ���˸���
	{
		X = 256-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"no")==0 ) //ȡ������˸���
	{
		X = 256-2;
		Y = 128-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else XL=0;
}

void Time( uint8_t value )
{
	RTCTime LocalTime;
	switch( value )
	{
		case 0:
		{
			XL = 0;
			DOCK = "Time";
			LOCATION = "Time";
			
			LCD_ClearScreen( BackColor ); //����
			Always(); //���Ե����Ͷ���
			
			LocalTime = RTC_GetTime();
			HOUR = LocalTime.RTC_Hour; //��ȡ��ǰʱ���֡���
			MIN = LocalTime.RTC_Min;
			SEC = LocalTime.RTC_Sec;
			
			LCD_DisplayString2( 88, 256, "OK" ); //��ʾOK��
			LCD_DisplayString2( 128, 256, "NO" ); //��ʾȡ����
			break;
		}
		case KEY_VALUE_UP: //���ϼ�
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				LOCATION = "hour";
			}
			else if( strcmp(LOCATION,"hour")==0 )
			{
				HOUR = ( HOUR + 1 ) % 24; //ʱ��Чֵ0~23
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				MIN = ( MIN + 1 ) % 60; //����Чֵ0~59
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				SEC = ( SEC + 1 ) % 60; //����Чֵ0~59
			}
			else if( strcmp(LOCATION,"no")==0 )
			{
				LOCATION = "ok";
			}
			break;
		}
		case KEY_VALUE_DOWN: //���¼�
		{
			if( strcmp(LOCATION,"hour")==0 )
			{
				if( HOUR==0 ) //��ֹʱΪ-1
					HOUR = 23;
				else HOUR--;
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				if( MIN==0 ) //��ֹ��Ϊ-1
					MIN = 59;
				else MIN--;
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				if( SEC==0 ) //��ֹ��Ϊ-1
					SEC = 59;
				else SEC--;
			}
			else if( LOCATION=="ok" )
			{
				LOCATION = "no";
			}
			break;
		}
		case KEY_VALUE_LEFT: //�����
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				Date(0); //Timeҳ�����ΪDateҳ��
				return;
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				LOCATION = "hour"; //�����Ϊʱ
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				LOCATION = "min"; //�����Ϊ��
			}
			else if( LOCATION=="ok" )
			{
				LOCATION = "sec"; //OK�����Ϊ��
			}
			break;
		}
		case KEY_VALUE_RIGHT: //���Ҽ�
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				More(0); //Timeҳ���ұ�ΪMoreҳ��
				return;
			}
			else if( strcmp(LOCATION,"hour")==0 )
			{
				LOCATION = "min"; //ʱ�ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				LOCATION = "sec"; //���ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				LOCATION = "ok"; //���ұ�ΪOK��
			}
			break;
		}
		case KEY_VALUE_ENTER: //��ȷ�ϼ�
		{
			if( strcmp(LOCATION,"ok")==0 ) //��OK��
			{
				LocalTime = RTC_GetTime();
				LocalTime.RTC_Hour = HOUR; //д�뵱ǰʱ���֡���
				LocalTime.RTC_Min = MIN;
				LocalTime.RTC_Sec = SEC;
				RTC_SetTime( LocalTime );
				Home(0); //������ҳ
			}
			else if( strcmp(LOCATION,"no")==0 ) //��ȡ����
			{
				Time(0); //���ص�ǰҳ
			}
			return;
		}
	}
	Gui_Time(); //���ƽ���
}