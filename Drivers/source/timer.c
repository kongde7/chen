#include "lpc17xx.h"
#include "lpc1768_timer.h"
#include "led.h"
#include "bmboard.h"
#include "joystick.h"

void (*pTimer0Callback)(void);
static void nop(void){
	return;
}

uint32_t init_timer0(void)
{
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	LPC_TIM0->CTCR=0;
	LPC_TIM0->PR=(25000000UL/2000-1);
	LPC_TIM0->MR0=2-1;
	LPC_TIM0->MCR=3;
	LPC_TIM0->EMR=(0x03<<4);
	LPC_TIM0->TCR=TCR_COUNTER_ENABLE;// 0x01
	pTimer0Callback=nop;
	return(1);
}

volatile uint32_t DelayCounter=0;

void DelayMs(uint32_t delayInMs)
{
	if(delayInMs==0)
		return;
	DelayCounter=delayInMs;
	while(DelayCounter);
	return;
}

void TIMER0_IRQHandler(void)
{
	LPC_TIM0->IR=1;	//clear interrupt flag
	DelayCounter--;
	pTimer0Callback();
}	
