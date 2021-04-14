#include "LPC17xx.h"
#include "bmboard.h"
#include "led.h"
#include "key.h"

void Key_init( void ) //������ʼ������
{
	uint32_t pincon;
	pincon = LPC_PINCON->PINSEL4; //PINSEL4���ó�EINT0
	pincon &= ~(0x03 << 20);
	pincon |= (0x01 << 20);
	LPC_PINCON->PINSEL4 = pincon;
	
	LPC_SC->EXTMODE |= (1UL << 0); //�����ⲿ�ж�
	LPC_SC->EXTPOLAR &= ~(1UL << 0);
	
	NVIC_EnableIRQ( EINT0_IRQn );
	
	LPC_GPIO2->FIODIR      &= ~(KEY1); //����GPIO�ж�
	LPC_GPIOINT->IO2IntEnF |=  (KEY1); //KEY1����˫�ش���
	LPC_GPIOINT->IO2IntEnR |=  (KEY1);
	LPC_GPIO2->FIODIR      &= ~(KEY2);
	LPC_GPIOINT->IO2IntEnF |=  (KEY2); //KEY2����˫�ش���
	LPC_GPIOINT->IO2IntEnR |=  (KEY2);
	
	NVIC_EnableIRQ( EINT3_IRQn );
}

void EINT0_IRQHandler() //�ⲿ�жϷ������
{
	static char OnOff = 0;
	
	LPC_SC->EXTINT |= (1UL << 0); //����
	
	if (OnOff == 1)
		{
			LED_Off(LED04); //����KEY0��LED4Ϩ��
			OnOff = 0;
		}
	else
		{
			LED_On (LED04); //�ٴΰ���KEY0��LED4����
			OnOff = 1;
		}
}

void EINT3_IRQHandler() //GPIO�жϷ������
{
	static char OnOff1 = 0, OnOff2 = 0;
	uint32_t status, status2, led;
	
	status = LPC_GPIOINT->IO2IntStatF; //�����½��ش������ж�
	status2 = LPC_GPIOINT->IO2IntStatR; //�����Ͻ��ش������ж�
	
	LPC_GPIOINT->IO2IntClr |= KEY1; //����
	LPC_GPIOINT->IO2IntClr |= KEY2; //����
	
	if (status & KEY1) //��סKEY1��LED6����
		LED_On (LED06);
	
	if (status2 & KEY1) //�ɿ�KEY1��LED6Ϩ��
		LED_Off(LED06);
		
	if (status & KEY2) //��סKEY2��LED5����
		LED_On (LED05);
	
	if (status2 & KEY2) //�ɿ�KEY2��LED5Ϩ��
		LED_Off(LED05);
}
