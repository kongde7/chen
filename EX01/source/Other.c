#include "lpc17xx.h"
#include "lpc1768_rtc.h"
#include "LCD.h"

uint8_t Night( uint8_t on )
{
	if( on==1 )
	{
		LCD_SetTextColor (LCD_COLOR_BLACK);
		LCD_SetBackColor (LCD_COLOR_WHITE);
		return 0;
	}
	else
	{
		LCD_SetTextColor (LCD_COLOR_WHITE);
		LCD_SetBackColor (LCD_COLOR_BLACK);
		return 1;
	}
}

void Factory( void )
{
	RTCTime LocalTime;
	
	LocalTime.RTC_Year = 2019;
	LocalTime.RTC_Mon = 12;
	LocalTime.RTC_Mday = 19;
	LocalTime.RTC_Hour = 23;
	LocalTime.RTC_Min = 59;
	LocalTime.RTC_Sec = 40;
	
	RTC_SetTime( LocalTime );
}
