#include <stdio.h>
#include <string.h>
#include "lpc17xx.h"
#include "lpc1768_rtc.h"
#include "joystick.h"
#include "LCD.h"

extern volatile unsigned short TextColor, BackColor;
extern uint16_t X, Y, XL, YL;
extern char *LOCATION;
extern char *DOCK;
static uint8_t ON;

static int state=1;  //定义初始状态为1
RTCTime LocalTime;   //定义实时时钟

RTCTime Alarm;       //定义闹钟
int Alarm_1_Hour=0;  //定义闹钟的小时位
int Alarm_1_Min=0;   //定义闹钟的分钟位
int Alarm_1_Sec=0;   //定义闹钟的秒钟位
char real_alarm_1[]="00:00:00";

int Alarm_2_Hour=0;  //定义闹钟的小时位
int Alarm_2_Min=0;   //定义闹钟的分钟位
int Alarm_2_Sec=0;   //定义闹钟的秒钟位
char real_alarm_2[]="00:00:00";
char real_alarm[];

int alarm_flag_1=0;

char Clk_On_Off_1[]="OFF";  //初始闹钟显示为关闭状态
static int alarm_on_off=0;  //初始闹钟处于关闭状态
unsigned char a[8];
unsigned char b[8];   //如果有报错首先看这！！！！！！！！！！


void Gui_More( void )
{
	  
	if( ON==1 )
		LCD_DisplayString2( 48, 32, "Night Mode    On" ); //显示夜间模式文字
	else LCD_DisplayString2( 48, 32, "Night Mode   Off" ); //不显示夜间模式文字
	LCD_DisplayString2( 88, 32, "alarm   clock1" ); //显示闹钟1
	LCD_DisplayString2( 128, 32, "alarm   clock2" ); //显示闹钟2
	LCD_DisplayString2( 168, 32, "Factory    Reset" ); //显示设置日期按钮
	
	Square( 32-2, 48-2-1, 256+4, 24+4, TextColor ); //显示夜间模式外框
	Square( 32-2, 88-2-1, 256+4, 24+4, TextColor ); //显示闹钟1外框
	Square( 32-2, 128-2-1, 256+4, 24+4, TextColor ); //显示闹钟2外框
	Square( 32-2, 168-2-1, 256+4, 24+4, TextColor ); //显示设置日期按钮外框
	
	if( strcmp(LOCATION,"mode1")==0 )
	{
		X = 32-2;
		Y = 48-2-1;
		XL = 256+4;
		YL = 24+4;
	}
	else if( strcmp(LOCATION,"mode2")==0 )
	{
		X = 32-2;
		Y = 88-2-1;
		XL = 256+4;
		YL = 24+4;
	}
	else if( strcmp(LOCATION,"mode3")==0 )
	{
		X = 32-2;
		Y = 128-2-1;
		XL = 256+4;
		YL = 24+4;
	}
	else if( strcmp(LOCATION,"mode4")==0 )
	{
		X = 32-2;
		Y = 168-2-1;
		XL = 256+4;
		YL = 24+4;
	}
	else XL=0;  //非以上四种状态即位于More
}

void More( uint8_t value )
{
	int i=0;
  int j=0;
	KEY_TypeDef key; //定义五向按键结构体
	switch( value )
	{
		case 0:
		{
			XL = 0;
			DOCK = "More";
			LOCATION = "More";
			
			LCD_ClearScreen( BackColor ); //清屏
			Always(); //常显底栏和顶栏
			break;
		}
		case KEY_VALUE_UP:
		{
			if( strcmp(LOCATION,"More")==0 )
			{
				LOCATION = "mode4";
			}
			else if( strcmp(LOCATION,"mode4")==0 )
			{
				LOCATION = "mode3";
			}
			else if( strcmp(LOCATION,"mode3")==0 )
			{
				LOCATION = "mode2";
			}
			else if( strcmp(LOCATION,"mode2")==0 )
			{
				LOCATION = "mode1";
			}
			break;
		}
		case KEY_VALUE_DOWN:
		{
			if( strcmp(LOCATION,"mode1")==0 )
			{
				LOCATION = "mode2";
			}
			else if( strcmp(LOCATION,"mode2")==0 )
			{
				LOCATION = "mode3";
			}
			else if( strcmp(LOCATION,"mode3")==0 )
			{
				LOCATION = "mode4";
			}
			else if( strcmp(LOCATION,"mode4")==0 )
			{
				LOCATION = "More";
			}
			break;
		}
		case KEY_VALUE_LEFT:
		{
			if( strcmp(LOCATION,"More")==0 )
			{
				Time(0);
				return;
			}
		}
		case KEY_VALUE_RIGHT:
		{
			break;
		}
		case KEY_VALUE_ENTER:
		{
			if( strcmp(LOCATION,"mode1")==0 )
			{
				ON = Night(ON);
				LCD_ClearScreen( BackColor ); //清屏
				Always(); //常显底栏和顶栏
			}
			else if( strcmp(LOCATION,"mode2")==0 )
			{
				while(1)			 
					{ 
            LCD_ClearScreen( BackColor ); //清屏
						Always(); //常显底栏和顶栏
						Alarm = RTC_GetAlarm();
						//LCD1602_DispStr(0,0,clk_1,5);			    //在第一行第一列显示'CLK1：'
						sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);	
						LCD_DisplayString2(88,32,real_alarm_1);		//显示闹钟的时间
						LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟的开关
						Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示时外框
	          Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示分外框
						Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示秒外框
						Square( 256-2, 88-1-2, 32+15+2, 24+2, TextColor ); //显示OFF键外框
						if( strcmp(LOCATION,"Alarm_1_Hour")==0 ) //时闪烁光标
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_1_Min")==0 ) //分闪烁光标
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_1_Sec")==0 ) //秒闪烁光标
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"OFF")==0 ) //闹钟开关键闪烁光标
	{
		X = 256-2;
		Y = 88-1-2;
		XL = 32+15+2;
		YL = 24+2;
	}
	else XL=0;


						while(1)
						{
							
							LocalTime = RTC_GetTime();
							key=GetKey();
							LOCATION = "Alarm_1_Hour";
							switch( value )
							{

							case KEY_VALUE_UP: //按上键
							{
								if(!(strcmp(Clk_On_Off_1,"OFF")))//如果上一个状态是关，则改为开
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//如果上一个状态是开，则改为关
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟状态
								if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
								

			{
				Alarm_1_Hour = ( Alarm_1_Hour + 1 ) % 24; //时有效值0~23
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				Alarm_1_Min = ( Alarm_1_Min + 1 ) % 60; //分有效值0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_1_sec")==0 )
			{
				Alarm_1_Sec = ( Alarm_1_Sec + 1 ) % 60; //秒有效值0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			
			break;
							}
							
							
							case KEY_VALUE_DOWN: //按下键
							
								if(!(strcmp(Clk_On_Off_1,"OFF")))//如果上一个状态是关，则改为开
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//如果上一个状态是开，则改为关
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟状态	
							
							
							if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
			{
				Alarm_1_Hour = ( Alarm_1_Hour - 1 ) % 24; //时有效值0~23
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				Alarm_1_Min = ( Alarm_1_Min - 1 ) % 60; //分有效值0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_1_sec")==0 )
			{
				Alarm_1_Sec = ( Alarm_1_Sec - 1 ) % 60; //秒有效值0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//显示闹钟时间
			}
			break;
			
			
			case KEY_VALUE_LEFT: //按左键
		{
			
			if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				LOCATION = "Alarm_1_Hour"; //分左边为时
			}
			else if( strcmp(LOCATION,"Alarm_1_Sec")==0 )
			{
				LOCATION = "Alarm_1_Min"; //秒左边为分
			}
			else if( LOCATION=="OFF" )
			{
				LOCATION = "Alarm_1_Sec"; //OK键左边为秒
			}
			break;
		}
		case KEY_VALUE_RIGHT: //按右键
		{
			
		  if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
			{
				LOCATION = "Alarm_1_Min"; //时右边为分
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				LOCATION = "Alarm_1_Sec"; //分右边为秒
			}
			else if( strcmp(LOCATION,"Alarm_1_Sec")==0 )
			{
				LOCATION = "OFF"; //秒右边为OK键
			}
			break;
		}
							}
								
							
              if(!(strcmp(Clk_On_Off_1,"ON "))) //如果闹钟为开
							{
								alarm_flag_1=1;               //闹钟开关状态为开
								Alarm = RTC_GetAlarm();
								Alarm.RTC_Hour=Alarm_1_Hour;
								Alarm.RTC_Min=Alarm_1_Min;
								RTC_SetAlarm(Alarm);          //将闹钟赋值
							}
                            if(!(strcmp(Clk_On_Off_1,"OFF"))) //如果闹钟为关
							{
								alarm_flag_1=0;
								Alarm = RTC_GetAlarm();       //闹钟开关状态为关
								Alarm.RTC_Hour=Alarm_1_Hour;    
								Alarm.RTC_Min=Alarm_1_Min;
								RTC_SetAlarm(Alarm);
							}
							a[1]=Alarm_1_Hour;			    //将闹钟1的开关状态，时间存进数组a
							a[2]=Alarm_1_Min;
							a[3]=alarm_flag_1;
							if(key.KeyValue==KEY_VALUE_ENTER&&key.Pressed) {state=4;E2PROM_WriteSeq(0x10,a,8);break;}
							//如果按下enter，将闹钟开关状态及小时分钟写入E2PROM并退出闹钟功能
						}
						break;
					}break;
			    //}
           // }continue;
		//}     
	//}
//}
				return;
			}
			else if( strcmp(LOCATION,"mode3")==0 )
			{
				while(1)			 
					{ 
            LCD_ClearScreen( BackColor ); //清屏
						Alarm = RTC_GetAlarm();
						//LCD1602_DispStr(0,0,clk_1,5);			    //在第一行第一列显示'CLK1：'
						sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);	
						LCD_DisplayString2(88,32,real_alarm_2);		//显示闹钟的时间
						LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟的开关
						Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示时外框
	          Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示分外框
						Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //显示秒外框
						Square( 256-2, 88-1-2, 32+15+2, 24+2, TextColor ); //显示OFF键外框
						if( strcmp(LOCATION,"Alarm_2_Hour")==0 ) //时闪烁光标
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_2_Min")==0 ) //分闪烁光标
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_2_Sec")==0 ) //秒闪烁光标
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"OFF")==0 ) //闹钟开关键闪烁光标
	{
		X = 256-2;
		Y = 88-1-2;
		XL = 32+15+2;
		YL = 24+2;
	}
	else XL=0;


						while(1)
						{
							
							LocalTime = RTC_GetTime();
							key=GetKey();
							LOCATION = "Alarm_2_Hour";
							switch( value )
							{

							case KEY_VALUE_UP: //按上键
							{
								if(!(strcmp(Clk_On_Off_1,"OFF")))//如果上一个状态是关，则改为开
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//如果上一个状态是开，则改为关
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟状态
								if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
								

			{
				Alarm_2_Hour = ( Alarm_2_Hour + 1 ) % 24; //时有效值0~23
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				Alarm_2_Min = ( Alarm_2_Min + 1 ) % 60; //分有效值0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_2_sec")==0 )
			{
				Alarm_2_Sec = ( Alarm_2_Sec + 1 ) % 60; //秒有效值0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			
			break;
							}
							
							
							case KEY_VALUE_DOWN: //按下键
							
								if(!(strcmp(Clk_On_Off_1,"OFF")))//如果上一个状态是关，则改为开
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//如果上一个状态是开，则改为关
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//显示闹钟状态	
							
							
							if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
			{
				Alarm_2_Hour = ( Alarm_2_Hour - 1 ) % 24; //时有效值0~23
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				Alarm_2_Min = ( Alarm_2_Min - 1 ) % 60; //分有效值0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			else if( strcmp(LOCATION,"Alarm_2_sec")==0 )
			{
				Alarm_2_Sec = ( Alarm_2_Sec - 1) % 60; //秒有效值0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//显示闹钟时间
			}
			break;
			
			
			case KEY_VALUE_LEFT: //按左键
		{
			
			if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				LOCATION = "Alarm_2_Hour"; //分左边为时
			}
			else if( strcmp(LOCATION,"Alarm_2_Sec")==0 )
			{
				LOCATION = "Alarm_2_Min"; //秒左边为分
			}
			else if( LOCATION=="OFF" )
			{
				LOCATION = "Alarm_2_Sec"; //OK键左边为秒
			}
			break;
		}
		case KEY_VALUE_RIGHT: //按右键
		{
			
		  if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
			{
				LOCATION = "Alarm_2_Min"; //时右边为分
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				LOCATION = "Alarm_2_Sec"; //分右边为秒
			}
			else if( strcmp(LOCATION,"Alarm_2_Sec")==0 )
			{
				LOCATION = "OFF"; //秒右边为OK键
			}
			break;
		}
							}
								
							
              if(!(strcmp(Clk_On_Off_1,"ON "))) //如果闹钟为开
							{
								alarm_flag_1=1;               //闹钟开关状态为开
								Alarm = RTC_GetAlarm();
								Alarm.RTC_Hour=Alarm_2_Hour;
								Alarm.RTC_Min=Alarm_2_Min;
								RTC_SetAlarm(Alarm);          //将闹钟赋值
							}
                            if(!(strcmp(Clk_On_Off_1,"OFF"))) //如果闹钟为关
							{
								alarm_flag_1=0;
								Alarm = RTC_GetAlarm();       //闹钟开关状态为关
								Alarm.RTC_Hour=Alarm_2_Hour;    
								Alarm.RTC_Min=Alarm_2_Min;
								RTC_SetAlarm(Alarm);
							}
							b[1]=Alarm_2_Hour;			    //将闹钟1的开关状态，时间存进数组a
							b[2]=Alarm_2_Min;
							b[3]=alarm_flag_1;
							if(key.KeyValue==KEY_VALUE_ENTER&&key.Pressed) {state=4;E2PROM_WriteSeq(0x10,b,8);break;}
							//如果按下enter，将闹钟开关状态及小时分钟写入E2PROM并退出闹钟功能
						}
						break;
					}break;
					return;
			}
			else if( strcmp(LOCATION,"mode4")==0 )
			{
				Factory();
			}
			break;
		}
		default: ;
	}
	Gui_More();
}
