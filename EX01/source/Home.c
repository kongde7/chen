#include <stdio.h>
#include <string.h>
#include "lpc17xx.h"
#include "lpc1768_rtc.h"
#include "joystick.h"
#include "LCD.h"

extern volatile unsigned short TextColor, BackColor;
uint32_t YEARS, MONS;
extern uint16_t X, Y, XL, YL;
extern char *LOCATION;
extern char *DOCK;

//输入年和月，打印日历
void Calendar( uint32_t year, uint32_t month )
{
	uint16_t i, x, y, first, temp, trim=0, num[]={31,28,31,30,31,30,31,31,30,31,30,31};
	char word[8];
unsigned short tempcolor;
	
	if( year%4==0 || year%100 && year%400==0 ) //判断闰年
		num[1] = 29;
	
	first = weekday( year, month, 1); //计算该月1号是星期几，调用weekday函数后要加1
	
	x = 110 + 30 * first; //起始横坐标
	y = 40 + 24; //起始纵坐标
	
	tempcolor = TextColor;
	LCD_SetTextColor( LCD_COLOR_BLUE );
	LCD_DisplayString( 40, 104, "                              Sat" ); //蓝色显示星期六
	LCD_SetTextColor( tempcolor );
	LCD_DisplayString( 40, 104, "     Mon  Tur  Wed  Thu  Fri" ); //黑显示星期一到五
	LCD_SetTextColor( LCD_COLOR_RED );
	LCD_DisplayString( 40, 104, "Sun" ); //红色显示星期日
	
	for( temp=first, i=1; i<=num[month-1]; i++ )
	{
		if( i==10 ) //当数字超过两位数时，微调距离，使得居中显示
		{
			trim = 3;
		}
		switch( temp )
		{
			case 0: //星期日
				sprintf( word, "%d  ", i );
				LCD_SetTextColor( LCD_COLOR_RED );
				LCD_DisplayString( y, x, word ); //红色显示
				x = 104 - trim + 36; //横坐标右移1个单位
				temp++;
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: //星期一到五
				if( i==10 )
					x = x - trim;
				sprintf( word, "%d  ", i );
				LCD_SetTextColor( tempcolor );
				LCD_DisplayString( y, x, word ); //黑色显示
				x = x + 30; //横坐标右移1个单位
				temp++;
				break;
			case 6: //星期六
				if( i==10 )
					x = x - trim;
				sprintf( word, "%d", i );
				LCD_SetTextColor( LCD_COLOR_BLUE );
				LCD_DisplayString( y, x, word ); //蓝色显示
				x = 110 - trim ; //横坐标回到最左端
				y = y + 24; //纵坐标下移1个单位
				temp = 0;
				break;
		}
	}
	LCD_SetTextColor( tempcolor );
}

void Gui_Home( void )
{
	char word[20];
	if( strcmp(LOCATION,"Disc")==0 )
	{
		X = 18-3;
		Y = 112-3;
		XL = 60+6;
		YL = 8+6;
	}
	else if( strcmp(LOCATION,"curr")==0 )
	{
		X = 18-3;
		Y = 136-3;
		XL = 60+6;
		YL = 8+6;
	}
	else if( strcmp(LOCATION,"last")==0 )
	{
		X = 18-3;
		Y = 160-3;
		XL = 60+6;
		YL = 8+6;
	}
	else if( strcmp(LOCATION,"next")==0 )
	{
		X = 18-3;
		Y = 184-3;
		XL = 60+6;
		YL = 8+6;
	}
	else XL=0;
	
	sprintf( word, "Year : %02d", YEARS );
	LCD_DisplayString( 48, 18, word ); //显示当前年数
	sprintf( word, "Month : %02d", MONS );
	LCD_DisplayString( 72, 18, word ); //显示当前月数
	
	LCD_DisplayString( 112, 18, "Dsic clock" ); //显示当前月按钮文字
	LCD_DisplayString( 136, 18, "Curr Month" ); //显示当前月按钮文字
	LCD_DisplayString( 160, 18, "Last Month" ); //显示上月按钮文字
	LCD_DisplayString( 184, 18, "Next Month" ); //显示下月按钮文字
	
	Square( 18-3, 112-3, 60+6, 8+6, TextColor ); //显示当前月按钮外框
	Square( 18-3, 136-3, 60+6, 8+6, TextColor ); //显示当前月按钮外框
	Square( 18-3, 160-3, 60+6, 8+6, TextColor ); //显示上月按钮外框
	Square( 18-3, 184-3, 60+6, 8+6, TextColor ); //显示下月按钮外框
}

//主页第一屏
void Home( uint8_t value )
{
	RTCTime LocalTime;
	
	switch( value )
	{
		case 0:
		{
			XL = 0;
			DOCK = "Home";
			LOCATION = "Home";
			
			LCD_ClearScreen( BackColor ); //清屏，全白
			Always();
			
			LocalTime = RTC_GetTime();
			YEARS = LocalTime.RTC_Year;
			MONS = LocalTime.RTC_Mon;
			Calendar( YEARS, MONS );
			break;
		}
		case KEY_VALUE_UP:
		{
			if( strcmp(LOCATION,"Home")==0 )
			{
				LOCATION = "next";
			}
			else if( strcmp(LOCATION,"next")==0 )
			{
				LOCATION = "last";
			}
			else if( strcmp(LOCATION,"last")==0 )
			{
				LOCATION = "curr";
			}
			else if( strcmp(LOCATION,"curr")==0 )
			{
				LOCATION = "Disc";
			}
			break;
		}
		case KEY_VALUE_DOWN:
		{
			if( strcmp(LOCATION,"Disc")==0 )
			{
				LOCATION = "curr";
			}
			else if( strcmp(LOCATION,"curr")==0 )
			{
				LOCATION = "last";
			}
			else if( strcmp(LOCATION,"last")==0 )
			{
				LOCATION = "next";
			}
			else if( strcmp(LOCATION,"next")==0 )
			{
				LOCATION = "Home";
			}
			break;
		}
		case KEY_VALUE_LEFT:
		{
			break;
		}
		case KEY_VALUE_RIGHT:
		{
			if( strcmp(LOCATION,"Home")==0 )
				Date(0);
			return;
		}
		case KEY_VALUE_ENTER:
		{
			Clear();
			if( strcmp(LOCATION,"Disc")==0 )
			{
				
				break;
			}
			else if( strcmp(LOCATION,"curr")==0 )
			{
				LocalTime = RTC_GetTime();
				Calendar( LocalTime.RTC_Year, LocalTime.RTC_Mon );
				YEARS = LocalTime.RTC_Year;
				MONS = LocalTime.RTC_Mon;
				break;
			}
			else if( strcmp(LOCATION,"last")==0 )
			{
				MONS--;
				if( MONS==0 )
				{
					YEARS--;
					MONS = 12;
				}
			}
			else if( strcmp(LOCATION,"next")==0 )
			{
				MONS++;
				if( MONS==13 )
				{
					YEARS++;
					MONS = 1;
				}
			}
			Calendar( YEARS, MONS );

			break;
		}
	}
	Gui_Home();
}
