
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
	LCD_DisplayString2( 88, 32, word ); //显示调整后的时、分、秒
	
	Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示时外框
	Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示分外框
	Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示秒外框
	Square( 256-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示OK键外框
	Square( 256-2, 128-1-2, 32+2+2, 24+2, TextColor ); //显示取消键外框
	
	if( strcmp(LOCATION,"hour")==0 ) //时闪烁光标
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"min")==0 ) //分闪烁光标
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"sec")==0 ) //秒闪烁光标
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"ok")==0 ) //确认键闪烁光标
	{
		X = 256-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"no")==0 ) //取消键闪烁光标
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
			
			LCD_ClearScreen( BackColor ); //清屏
			Always(); //常显底栏和顶栏
			
			LocalTime = RTC_GetTime();
			HOUR = LocalTime.RTC_Hour; //读取当前时、分、秒
			MIN = LocalTime.RTC_Min;
			SEC = LocalTime.RTC_Sec;
			
			LCD_DisplayString2( 88, 256, "OK" ); //显示OK键
			LCD_DisplayString2( 128, 256, "NO" ); //显示取消键
			break;
		}
		case KEY_VALUE_UP: //按上键
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				LOCATION = "hour";
			}
			else if( strcmp(LOCATION,"hour")==0 )
			{
				HOUR = ( HOUR + 1 ) % 24; //时有效值0~23
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				MIN = ( MIN + 1 ) % 60; //分有效值0~59
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				SEC = ( SEC + 1 ) % 60; //秒有效值0~59
			}
			else if( strcmp(LOCATION,"no")==0 )
			{
				LOCATION = "ok";
			}
			break;
		}
		case KEY_VALUE_DOWN: //按下键
		{
			if( strcmp(LOCATION,"hour")==0 )
			{
				if( HOUR==0 ) //防止时为-1
					HOUR = 23;
				else HOUR--;
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				if( MIN==0 ) //防止分为-1
					MIN = 59;
				else MIN--;
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				if( SEC==0 ) //防止秒为-1
					SEC = 59;
				else SEC--;
			}
			else if( LOCATION=="ok" )
			{
				LOCATION = "no";
			}
			break;
		}
		case KEY_VALUE_LEFT: //按左键
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				Date(0); //Time页面左边为Date页面
				return;
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				LOCATION = "hour"; //分左边为时
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				LOCATION = "min"; //秒左边为分
			}
			else if( LOCATION=="ok" )
			{
				LOCATION = "sec"; //OK键左边为秒
			}
			break;
		}
		case KEY_VALUE_RIGHT: //按右键
		{
			if( strcmp(LOCATION,"Time")==0 )
			{
				More(0); //Time页面右边为More页面
				return;
			}
			else if( strcmp(LOCATION,"hour")==0 )
			{
				LOCATION = "min"; //时右边为分
			}
			else if( strcmp(LOCATION,"min")==0 )
			{
				LOCATION = "sec"; //分右边为秒
			}
			else if( strcmp(LOCATION,"sec")==0 )
			{
				LOCATION = "ok"; //秒右边为OK键
			}
			break;
		}
		case KEY_VALUE_ENTER: //按确认键
		{
			if( strcmp(LOCATION,"ok")==0 ) //按OK键
			{
				LocalTime = RTC_GetTime();
				LocalTime.RTC_Hour = HOUR; //写入当前时、分、秒
				LocalTime.RTC_Min = MIN;
				LocalTime.RTC_Sec = SEC;
				RTC_SetTime( LocalTime );
				Home(0); //返回主页
			}
			else if( strcmp(LOCATION,"no")==0 ) //按取消键
			{
				Time(0); //返回当前页
			}
			return;
		}
	}
	Gui_Time(); //绘制界面
}