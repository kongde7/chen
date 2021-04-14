#include <string.h>
#include "lpc17xx.h"
#include "LCD.h"

extern volatile unsigned short TextColor, BackColor;
extern char *DOCK;

//���Բ���
void Always( void )
{
	LCD_DisplayString2( 214, 8, "Home Date Time More" ); //��ʾ�ײ�����
	
	LineY( 79, 208, 32, TextColor );
	LineY( 159, 208, 32, TextColor );
	LineY( 239, 208, 32, TextColor ); //��ʾ��������
	
	LineX( 0, 31, 320, TextColor ); //��ʾ��������
	
	if( strcmp(DOCK,"Home")==0 ) //��ʾHomeҳ��ײ�����
	{
		LineX( 79, 208, 240, TextColor );
	}
	else if( strcmp(DOCK,"Date")==0 ) //��ʾDateҳ��ײ�����
	{
		LineX( 0, 208, 80, TextColor );
		LineX( 159, 208, 160, TextColor );
	}
	else if( strcmp(DOCK,"Time")==0 ) //��ʾTimeҳ��ײ�����
	{
		LineX( 0, 208, 160, TextColor );
		LineX( 239, 208, 80, TextColor );
	}
	else if( strcmp(DOCK,"More")==0 ) //��ʾMoreҳ��ײ�����
	{
		LineX( 0, 208, 240, TextColor );
	}
}
