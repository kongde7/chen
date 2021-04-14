#include "lpc17xx.h"
#include "bmboard.h"
#include "lpc1768_timer.h"
#include "joystick.h"

void (*oldcb) (void);
static KEY_FSM_STATUS status; //不一样，静态
static KEY_TypeDef Key; //不一样，静态

static uint8_t pressedkey; //无

void Joystick_Config()
{
	LPC_PINCON->PINSEL3 = 0;
	LPC_GPIO1->FIODIR = ~( JOY_ENTER | JOY_LEFT | JOY_RIGHT | JOY_UP | JOY_DOWN );
	
	oldcb = pTimer0Callback;
	pTimer0Callback = KeyboardScan;
	
	status = KEY_IDLE;
	
	Key.KeyValue = KEY_VALUE_NOKEY; //无
	Key.Pressed = 0; //无
	Key.Released = 0; //无
}

KEY_TypeDef GetKey()
{
	KEY_TypeDef CurKey;
	CurKey.KeyValue = Key.KeyValue;
	CurKey.Pressed = Key.Pressed;
	CurKey.Released = Key.Released;
	
	if( status == KEY_RELEASE_CONFIRMED )
	{
		Key.KeyValue = KEY_VALUE_NOKEY;
		Key.Pressed = 0;
		Key.Released = 0;
		status = KEY_IDLE;
	}
	else if( status == KEY_PRESS_CONFIRMED || status == KEY_RELEASED )
	{
		Key.Pressed = 0;
	}
	return CurKey;
}

static void KeyboardScan()
{
	static uint8_t counter=0;
	uint32_t key;
	
	if( counter++ < 15 )
	{
		oldcb();
		return;
	}
	else
	{
		counter = 0;
		key = ~(LPC_GPIO1->FIOPIN) & 0x3E000000;
		
		if( key & JOY_UP )
			key = KEY_VALUE_UP;
		else if( key & JOY_DOWN )
			key = KEY_VALUE_DOWN;
		else if( key & JOY_LEFT )
			key = KEY_VALUE_LEFT;
		else if( key & JOY_RIGHT )
			key = KEY_VALUE_RIGHT;
		else if( key & JOY_ENTER )
			key = KEY_VALUE_ENTER;
		else
			key = KEY_VALUE_NOKEY;		
	}
	
	switch( status )
	{
		case KEY_IDLE:
			if(key)
				status = KEY_PRESSED;
		break;
		
		case KEY_PRESSED:
			if(key)
			{
				status = KEY_PRESS_CONFIRMED;
				Key.KeyValue = key;
				Key.Pressed = 1;
				pressedkey = key; //无
			}
			else
				status = KEY_IDLE;
		break;
			
		case KEY_PRESS_CONFIRMED:
			if(!key) //不一样，但是可以
				status = KEY_RELEASED;
		break;
			
		case KEY_RELEASED:
			if(key)
				status = KEY_PRESS_CONFIRMED;
			else
			{
			status = KEY_RELEASE_CONFIRMED;
			Key.Released = 1;
			Key.KeyValue = pressedkey; //无
			}
		break;
		
		case KEY_RELEASE_CONFIRMED:
			if(key)
			{
				status = KEY_PRESSED;
				Key.KeyValue = pressedkey; //不一样
			}
		break;
	}
	oldcb();
}
