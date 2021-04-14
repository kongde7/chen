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

static int state=1;  //�����ʼ״̬Ϊ1
RTCTime LocalTime;   //����ʵʱʱ��

RTCTime Alarm;       //��������
int Alarm_1_Hour=0;  //�������ӵ�Сʱλ
int Alarm_1_Min=0;   //�������ӵķ���λ
int Alarm_1_Sec=0;   //�������ӵ�����λ
char real_alarm_1[]="00:00:00";

int Alarm_2_Hour=0;  //�������ӵ�Сʱλ
int Alarm_2_Min=0;   //�������ӵķ���λ
int Alarm_2_Sec=0;   //�������ӵ�����λ
char real_alarm_2[]="00:00:00";
char real_alarm[];

int alarm_flag_1=0;

char Clk_On_Off_1[]="OFF";  //��ʼ������ʾΪ�ر�״̬
static int alarm_on_off=0;  //��ʼ���Ӵ��ڹر�״̬
unsigned char a[8];
unsigned char b[8];   //����б������ȿ��⣡������������������


void Gui_More( void )
{
	  
	if( ON==1 )
		LCD_DisplayString2( 48, 32, "Night Mode    On" ); //��ʾҹ��ģʽ����
	else LCD_DisplayString2( 48, 32, "Night Mode   Off" ); //����ʾҹ��ģʽ����
	LCD_DisplayString2( 88, 32, "alarm   clock1" ); //��ʾ����1
	LCD_DisplayString2( 128, 32, "alarm   clock2" ); //��ʾ����2
	LCD_DisplayString2( 168, 32, "Factory    Reset" ); //��ʾ�������ڰ�ť
	
	Square( 32-2, 48-2-1, 256+4, 24+4, TextColor ); //��ʾҹ��ģʽ���
	Square( 32-2, 88-2-1, 256+4, 24+4, TextColor ); //��ʾ����1���
	Square( 32-2, 128-2-1, 256+4, 24+4, TextColor ); //��ʾ����2���
	Square( 32-2, 168-2-1, 256+4, 24+4, TextColor ); //��ʾ�������ڰ�ť���
	
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
	else XL=0;  //����������״̬��λ��More
}

void More( uint8_t value )
{
	int i=0;
  int j=0;
	KEY_TypeDef key; //�������򰴼��ṹ��
	switch( value )
	{
		case 0:
		{
			XL = 0;
			DOCK = "More";
			LOCATION = "More";
			
			LCD_ClearScreen( BackColor ); //����
			Always(); //���Ե����Ͷ���
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
				LCD_ClearScreen( BackColor ); //����
				Always(); //���Ե����Ͷ���
			}
			else if( strcmp(LOCATION,"mode2")==0 )
			{
				while(1)			 
					{ 
            LCD_ClearScreen( BackColor ); //����
						Always(); //���Ե����Ͷ���
						Alarm = RTC_GetAlarm();
						//LCD1602_DispStr(0,0,clk_1,5);			    //�ڵ�һ�е�һ����ʾ'CLK1��'
						sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);	
						LCD_DisplayString2(88,32,real_alarm_1);		//��ʾ���ӵ�ʱ��
						LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ���ӵĿ���
						Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾʱ���
	          Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
						Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
						Square( 256-2, 88-1-2, 32+15+2, 24+2, TextColor ); //��ʾOFF�����
						if( strcmp(LOCATION,"Alarm_1_Hour")==0 ) //ʱ��˸���
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_1_Min")==0 ) //����˸���
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_1_Sec")==0 ) //����˸���
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"OFF")==0 ) //���ӿ��ؼ���˸���
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

							case KEY_VALUE_UP: //���ϼ�
							{
								if(!(strcmp(Clk_On_Off_1,"OFF")))//�����һ��״̬�ǹأ����Ϊ��
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//�����һ��״̬�ǿ������Ϊ��
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ����״̬
								if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
								

			{
				Alarm_1_Hour = ( Alarm_1_Hour + 1 ) % 24; //ʱ��Чֵ0~23
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				Alarm_1_Min = ( Alarm_1_Min + 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_1_sec")==0 )
			{
				Alarm_1_Sec = ( Alarm_1_Sec + 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			
			break;
							}
							
							
							case KEY_VALUE_DOWN: //���¼�
							
								if(!(strcmp(Clk_On_Off_1,"OFF")))//�����һ��״̬�ǹأ����Ϊ��
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//�����һ��״̬�ǿ������Ϊ��
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ����״̬	
							
							
							if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
			{
				Alarm_1_Hour = ( Alarm_1_Hour - 1 ) % 24; //ʱ��Чֵ0~23
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				Alarm_1_Min = ( Alarm_1_Min - 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_1_sec")==0 )
			{
				Alarm_1_Sec = ( Alarm_1_Sec - 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_1, "%02d:%02d:%02d",Alarm_1_Hour,Alarm_1_Min,Alarm_1_Sec);
				LCD_DisplayString2(88,32,real_alarm_1);//��ʾ����ʱ��
			}
			break;
			
			
			case KEY_VALUE_LEFT: //�����
		{
			
			if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				LOCATION = "Alarm_1_Hour"; //�����Ϊʱ
			}
			else if( strcmp(LOCATION,"Alarm_1_Sec")==0 )
			{
				LOCATION = "Alarm_1_Min"; //�����Ϊ��
			}
			else if( LOCATION=="OFF" )
			{
				LOCATION = "Alarm_1_Sec"; //OK�����Ϊ��
			}
			break;
		}
		case KEY_VALUE_RIGHT: //���Ҽ�
		{
			
		  if( strcmp(LOCATION,"Alarm_1_Hour")==0 )
			{
				LOCATION = "Alarm_1_Min"; //ʱ�ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"Alarm_1_Min")==0 )
			{
				LOCATION = "Alarm_1_Sec"; //���ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"Alarm_1_Sec")==0 )
			{
				LOCATION = "OFF"; //���ұ�ΪOK��
			}
			break;
		}
							}
								
							
              if(!(strcmp(Clk_On_Off_1,"ON "))) //�������Ϊ��
							{
								alarm_flag_1=1;               //���ӿ���״̬Ϊ��
								Alarm = RTC_GetAlarm();
								Alarm.RTC_Hour=Alarm_1_Hour;
								Alarm.RTC_Min=Alarm_1_Min;
								RTC_SetAlarm(Alarm);          //�����Ӹ�ֵ
							}
                            if(!(strcmp(Clk_On_Off_1,"OFF"))) //�������Ϊ��
							{
								alarm_flag_1=0;
								Alarm = RTC_GetAlarm();       //���ӿ���״̬Ϊ��
								Alarm.RTC_Hour=Alarm_1_Hour;    
								Alarm.RTC_Min=Alarm_1_Min;
								RTC_SetAlarm(Alarm);
							}
							a[1]=Alarm_1_Hour;			    //������1�Ŀ���״̬��ʱ��������a
							a[2]=Alarm_1_Min;
							a[3]=alarm_flag_1;
							if(key.KeyValue==KEY_VALUE_ENTER&&key.Pressed) {state=4;E2PROM_WriteSeq(0x10,a,8);break;}
							//�������enter�������ӿ���״̬��Сʱ����д��E2PROM���˳����ӹ���
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
            LCD_ClearScreen( BackColor ); //����
						Alarm = RTC_GetAlarm();
						//LCD1602_DispStr(0,0,clk_1,5);			    //�ڵ�һ�е�һ����ʾ'CLK1��'
						sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);	
						LCD_DisplayString2(88,32,real_alarm_2);		//��ʾ���ӵ�ʱ��
						LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ���ӵĿ���
						Square( 32-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾʱ���
	          Square( 80-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
						Square( 128-2, 88-1-2, 32+2+2, 24+2, TextColor ); //��ʾ�����
						Square( 256-2, 88-1-2, 32+15+2, 24+2, TextColor ); //��ʾOFF�����
						if( strcmp(LOCATION,"Alarm_2_Hour")==0 ) //ʱ��˸���
	{
		X = 32-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_2_Min")==0 ) //����˸���
	{
		X = 80-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"Alarm_2_Sec")==0 ) //����˸���
	{
		X = 128-2;
		Y = 88-1-2;
		XL = 32+2+2;
		YL = 24+2;
	}
	else if( strcmp(LOCATION,"OFF")==0 ) //���ӿ��ؼ���˸���
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

							case KEY_VALUE_UP: //���ϼ�
							{
								if(!(strcmp(Clk_On_Off_1,"OFF")))//�����һ��״̬�ǹأ����Ϊ��
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//�����һ��״̬�ǿ������Ϊ��
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ����״̬
								if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
								

			{
				Alarm_2_Hour = ( Alarm_2_Hour + 1 ) % 24; //ʱ��Чֵ0~23
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				Alarm_2_Min = ( Alarm_2_Min + 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_2_sec")==0 )
			{
				Alarm_2_Sec = ( Alarm_2_Sec + 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			
			break;
							}
							
							
							case KEY_VALUE_DOWN: //���¼�
							
								if(!(strcmp(Clk_On_Off_1,"OFF")))//�����һ��״̬�ǹأ����Ϊ��
											{strcpy(Clk_On_Off_1,"ON ");}	
										else {strcpy(Clk_On_Off_1,"OFF");}//�����һ��״̬�ǿ������Ϊ��
										LCD_DisplayString2(88,256,Clk_On_Off_1);		//��ʾ����״̬	
							
							
							if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
			{
				Alarm_2_Hour = ( Alarm_2_Hour - 1 ) % 24; //ʱ��Чֵ0~23
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				Alarm_2_Min = ( Alarm_2_Min - 1 ) % 60; //����Чֵ0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			else if( strcmp(LOCATION,"Alarm_2_sec")==0 )
			{
				Alarm_2_Sec = ( Alarm_2_Sec - 1) % 60; //����Чֵ0~59
				sprintf(real_alarm_2, "%02d:%02d:%02d",Alarm_2_Hour,Alarm_2_Min,Alarm_2_Sec);
				LCD_DisplayString2(88,32,real_alarm_2);//��ʾ����ʱ��
			}
			break;
			
			
			case KEY_VALUE_LEFT: //�����
		{
			
			if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				LOCATION = "Alarm_2_Hour"; //�����Ϊʱ
			}
			else if( strcmp(LOCATION,"Alarm_2_Sec")==0 )
			{
				LOCATION = "Alarm_2_Min"; //�����Ϊ��
			}
			else if( LOCATION=="OFF" )
			{
				LOCATION = "Alarm_2_Sec"; //OK�����Ϊ��
			}
			break;
		}
		case KEY_VALUE_RIGHT: //���Ҽ�
		{
			
		  if( strcmp(LOCATION,"Alarm_2_Hour")==0 )
			{
				LOCATION = "Alarm_2_Min"; //ʱ�ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"Alarm_2_Min")==0 )
			{
				LOCATION = "Alarm_2_Sec"; //���ұ�Ϊ��
			}
			else if( strcmp(LOCATION,"Alarm_2_Sec")==0 )
			{
				LOCATION = "OFF"; //���ұ�ΪOK��
			}
			break;
		}
							}
								
							
              if(!(strcmp(Clk_On_Off_1,"ON "))) //�������Ϊ��
							{
								alarm_flag_1=1;               //���ӿ���״̬Ϊ��
								Alarm = RTC_GetAlarm();
								Alarm.RTC_Hour=Alarm_2_Hour;
								Alarm.RTC_Min=Alarm_2_Min;
								RTC_SetAlarm(Alarm);          //�����Ӹ�ֵ
							}
                            if(!(strcmp(Clk_On_Off_1,"OFF"))) //�������Ϊ��
							{
								alarm_flag_1=0;
								Alarm = RTC_GetAlarm();       //���ӿ���״̬Ϊ��
								Alarm.RTC_Hour=Alarm_2_Hour;    
								Alarm.RTC_Min=Alarm_2_Min;
								RTC_SetAlarm(Alarm);
							}
							b[1]=Alarm_2_Hour;			    //������1�Ŀ���״̬��ʱ��������a
							b[2]=Alarm_2_Min;
							b[3]=alarm_flag_1;
							if(key.KeyValue==KEY_VALUE_ENTER&&key.Pressed) {state=4;E2PROM_WriteSeq(0x10,b,8);break;}
							//�������enter�������ӿ���״̬��Сʱ����д��E2PROM���˳����ӹ���
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
