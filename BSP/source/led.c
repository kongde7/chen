/******************************Copyright (c)***********************************
**    Nanjing University Jinling College
**
**-----------------------------------------------------------------------------
** Created by:          James Ho
** Created date:        2013-07-01
** Version:             V1.00
**-----------------------------------------------------------------------------
******************************************************************************/

#include "lpc17xx.h"
#include "bmboard.h"
#include "joystick.h"
#include "led.h"
/* on LT board, LED and LCD are both controled by Port2 */
void Set_LCD_DIR_A2B() {
        LPC_GPIO0->FIODIR |= ( LCD_PIN_DIR | LCD_PIN_EN);     
        LPC_GPIO0->FIOSET =  LCD_PIN_DIR;
	LPC_GPIO0->FIOCLR = LCD_PIN_EN;	
}

/*----------------------------------------------------------------------------
  configer LED pins
 *----------------------------------------------------------------------------*/
void LED_Config(void) {
        Set_LCD_DIR_A2B();
        LPC_PINCON->PINSEL4 = 0;	// function select: b00=GPIO
        LPC_GPIO2->FIODIR = LED_ALL; 
//	LPC_GPIO2->FIOMASK = ~(LED_ALL);
	LPC_GPIO2->FIOPIN &= ~(LED_ALL);
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *----------------------------------------------------------------------------*/
void LED_On (uint32_t led) {

        //LPC_GPIO2->FIOPIN |=  (led);                  /* Turn On  LED */
	LPC_GPIO2->FIOSET = led;
}

void LED_AndOn (uint32_t led) {

	LPC_GPIO2->FIOPIN = led;
}

/*------------------------------------------------------------------------------
  Switch off LEDs
 *-----------------------------------------------------------------------------*/
void LED_Off (uint32_t led) {

        //LPC_GPIO2->FIOPIN &= ~(led);                  /* Turn Off LED */
	LPC_GPIO2->FIOCLR = led;
}

void LED_Toggle(uint32_t led){
	uint32_t all;
	all = LPC_GPIO2->FIOPIN & LED_ALL;
	if(!(led & all))
		LPC_GPIO2->FIOSET = led;
	else
		LPC_GPIO2->FIOCLR = led;
}


void SoftDelay(uint32_t dlyTicks)
{
	while(dlyTicks--);
}

void BUZZER_Config(void) {       //·äÃùÆ÷
        Set_LCD_DIR_A2B();
        LPC_PINCON->PINSEL1 &=~(0x03<<20) ;
        LPC_GPIO0->FIODIR |= (1UL<<26); 
	      LPC_GPIO0->FIOPIN &= ~(1UL<<26);
}

void BUZZER_On(void)
{
	int j;
	for(j=150;j>0;j--)
		{
			LPC_GPIO0->FIOSET |=(1UL<<26);
			DelayMs(10);
			LPC_GPIO0->FIOCLR |=(1UL<<26);
		  DelayMs(10);
	    }
	LPC_GPIO0->FIOCLR |=(1UL<<26);	
  }