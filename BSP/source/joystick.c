#include "lpc17xx.h"
#include "bmboard.h"
#include "lpc1768_timer.h"
#include "joystick.h"

void (*oldcb) (void); //����һ���ص�����ָ��
KEY_FSM_STATUS status; //����ȫ�ֱ���������״̬����״̬
KEY_TypeDef Key; //�������򰴼��ṹ��

static void KeyboardScan()
{
	static uint8_t counter=0; //���������
	uint32_t key;
	
	if( counter++ < 15 ) //��û�е�15ms
	{
		oldcb();
		return; //����
	}
	else
	{
		counter = 0; //��15ms������������
		key = ~(LPC_GPIO1->FIOPIN) & 0x3E000000; //��ⰴ���˿�
		
		if( key & JOY_UP ) //�����⵽�ϣ���ֵ��key
			key = KEY_VALUE_UP;
		else if( key & JOY_DOWN ) //�����⵽�£�����Ӧֵ��key
			key = KEY_VALUE_DOWN;
		else if( key & JOY_LEFT ) //�����⵽�󣬸���Ӧֵ��key
			key = KEY_VALUE_LEFT;
		else if( key & JOY_RIGHT ) //�����⵽�ң�����Ӧֵ��key
			key = KEY_VALUE_RIGHT;
		else if( key & JOY_ENTER ) //�����⵽�У�����Ӧֵ��key
			key = KEY_VALUE_ENTER;
		else
			key = KEY_VALUE_NOKEY; //û�м�⵽������Ӧֵ��key
	}
	
	switch( status )
	{
		case KEY_IDLE: //����̬�����
			if(key)
				status = KEY_PRESSED; //�а��������밴��̬
		break;
		
		case KEY_PRESSED: //����̬�����
			if(key)
			{
				status = KEY_PRESS_CONFIRMED; //���а���������ȷ��̬
				Key.KeyValue = key; //���ͼ�ֵ
				Key.Pressed = 1;
			}
			else
				status = KEY_IDLE; //�ް��������ؿ���̬
		break;
			
		case KEY_PRESS_CONFIRMED: //����ȷ��̬�����
			if(!key)
				status = KEY_RELEASED; //���ɿ��������ͷ�̬
		break;
			
		case KEY_RELEASED: //�ͷ�̬�����
			if(key)
				status = KEY_PRESS_CONFIRMED; //�ְ��£����ذ���ȷ��̬
			else
			{
			status = KEY_RELEASE_CONFIRMED; //�����ɿ��������ͷ�ȷ��̬
			Key.Released = 1;
			}
		break;
		
		case KEY_RELEASE_CONFIRMED: //�ͷ�ȷ��̬�����
			if(key)
			{
				status = KEY_PRESSED; //�ְ��£�������һ������̬
				Key.KeyValue = key; //���ͼ�ֵ
			}
		break;
	}
	oldcb();
}

void Joystick_Config()
{
	LPC_PINCON->PINSEL3 = 0; //��������
	LPC_GPIO1->FIODIR = ~( JOY_ENTER | JOY_LEFT | JOY_RIGHT | JOY_UP | JOY_DOWN );
	
	oldcb = pTimer0Callback; //��״̬���Ͷ�ʱ����ϵ����
	pTimer0Callback = KeyboardScan; //��ʱ���ص�����ָ��״̬����KeyboardScan()����
	
	status = KEY_IDLE; //��ʼ��״̬ΪIDLE
}

KEY_TypeDef GetKey()
{
	KEY_TypeDef CurKey; //�������򰴼��ṹ��
	CurKey.KeyValue = Key.KeyValue;
	CurKey.Pressed = Key.Pressed;
	CurKey.Released = Key.Released; //����ǰ����״̬��Ϊ��ֵ
	
	if( status == KEY_RELEASE_CONFIRMED ) //����Ѿ�����ȡ���
	{
		Key.KeyValue = KEY_VALUE_NOKEY; //��Ϊ��
		Key.Pressed = 0;
		Key.Released = 0; //��հ���״̬
		status = KEY_IDLE; //����IDLE״̬
	}
	else if( status == KEY_PRESS_CONFIRMED || status == KEY_RELEASED ) //�������״̬����ȡ
	{
		Key.Pressed = 0; //����
	}
	return CurKey; //�������򰴼��ṹ��
}
