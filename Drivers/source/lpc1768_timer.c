#include <stdarg.h>
#include <stdint.h>
#include "stdio.h"
#include "string.h"
#include "lpc1768_timer.h"
#include "lpc17xx.h"
#include "lpc1768_uart.h"
#include "bmboard.h"

void(*pTimer0Callback)(void); //����һ���ص�����ָ��

static void nop(void)
{
    return; //����һ���պ���
}

uint32_t Timer_Init( uint8_t timer_num )
{
    if( timer_num == 0 )
    {
        NVIC_EnableIRQ( TIMER0_IRQn ); //�����жϷ������
        LPC_TIM0->CTCR = 0; //���ö�ʱ��ģʽ
        LPC_TIM0->PR = (25000000UL/2000-1); //���÷�Ƶ2KHz
        LPC_TIM0->MR0 = 2-1; //����ÿ1ms����һ���ж�
        LPC_TIM0->MCR = 3; //���ü�������λ�����ж�
        LPC_TIM0->EMR = (0x3<<4); //���õ�ƽ��ת
        LPC_TIM0->TCR = TCR_COUNTER_ENABLE; //������ʱ��
        pTimer0Callback = nop; //ָ��պ���
        return(1);
    }
}

volatile uint32_t DelayCounter = 0; //��������ȫ�ֱ���
void DelayMs(uint32_t delayInMs)
{
    if( delayInMs == 0 ) //������������0
		return;
	DelayCounter = delayInMs; //������������ֵ
    while( DelayCounter ); //�ȴ���������������0
    return;
}

void TIMER0_IRQHandler(void)
{
    LPC_TIM0->IR = 1; //����жϱ�־
    DelayCounter--; //��������1
    pTimer0Callback(); //�ص�����
}
