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

//��������£���ӡ����
void Calendar( uint32_t year, uint32_t month )
{
	uint16_t i, x, y, first, temp, trim=0, num[]={31,28,31,30,31,30,31,31,30,31,30,31};
	char word[8];
unsigned short tempcolor;
	
	if( year%4==0 || year%100 && year%400==0 ) //�ж�����
		num[1] = 29;
	
	first = weekday( year, month, 1); //�������1�������ڼ�������weekday������Ҫ��1
	
	x = 110 + 30 * first; //��ʼ������
	y = 40 + 24; //��ʼ������
	
	tempcolor = TextColor;
	LCD_SetTextColor( LCD_COLOR_BLUE );
	LCD_DisplayString( 40, 104, "                              Sat" ); //��ɫ��ʾ������
	LCD_SetTextColor( tempcolor );
	LCD_DisplayString( 40, 104, "     Mon  Tur  Wed  Thu  Fri" ); //����ʾ����һ����
	LCD_SetTextColor( LCD_COLOR_RED );
	LCD_DisplayString( 40, 104, "Sun" ); //��ɫ��ʾ������
	
	for( temp=first, i=1; i<=num[month-1]; i++ )
	{
		if( i==10 ) //�����ֳ�����λ��ʱ��΢�����룬ʹ�þ�����ʾ
		{
			trim = 3;
		}
		switch( temp )
		{
			case 0: //������
				sprintf( word, "%d  ", i );
				LCD_SetTextColor( LCD_COLOR_RED );
				LCD_DisplayString( y, x, word ); //��ɫ��ʾ
				x = 104 - trim + 36; //����������1����λ
				temp++;
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: //����һ����
				if( i==10 )
					x = x - trim;
				sprintf( word, "%d  ", i );
				LCD_SetTextColor( tempcolor );
				LCD_DisplayString( y, x, word ); //��ɫ��ʾ
				x = x + 30; //����������1����λ
				temp++;
				break;
			case 6: //������
				if( i==10 )
					x = x - trim;
				sprintf( word, "%d", i );
				LCD_SetTextColor( LCD_COLOR_BLUE );
				LCD_DisplayString( y, x, word ); //��ɫ��ʾ
				x = 110 - trim ; //������ص������
				y = y + 24; //����������1����λ
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
	LCD_DisplayString( 48, 18, word ); //��ʾ��ǰ����
	sprintf( word, "Month : %02d", MONS );
	LCD_DisplayString( 72, 18, word ); //��ʾ��ǰ����
	
	LCD_DisplayString( 112, 18, "Dsic clock" ); //��ʾ��ǰ�°�ť����
	LCD_DisplayString( 136, 18, "Curr Month" ); //��ʾ��ǰ�°�ť����
	LCD_DisplayString( 160, 18, "Last Month" ); //��ʾ���°�ť����
	LCD_DisplayString( 184, 18, "Next Month" ); //��ʾ���°�ť����
	
	Square( 18-3, 112-3, 60+6, 8+6, TextColor ); //��ʾ��ǰ�°�ť���
	Square( 18-3, 136-3, 60+6, 8+6, TextColor ); //��ʾ��ǰ�°�ť���
	Square( 18-3, 160-3, 60+6, 8+6, TextColor ); //��ʾ���°�ť���
	Square( 18-3, 184-3, 60+6, 8+6, TextColor ); //��ʾ���°�ť���
}

//��ҳ��һ��
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
			
			LCD_ClearScreen( BackColor ); //������ȫ��
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
