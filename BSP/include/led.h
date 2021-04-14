/******************************Copyright (c)***********************************
**    Nanjing University Jinling College
**
**-----------------------------------------------------------------------------
** Created by:          James Ho
** Created date:        2013-07-01
** Version:             V1.00
**-----------------------------------------------------------------------------
******************************************************************************/

#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern ¡°c¡±{
#endif

extern void BUZZER_Config(void);
extern void BUZZER_On(void);
extern void LED_Config(void);
extern void LED_On (uint32_t led);
extern void LED_Off (uint32_t led);
extern void LED_Toggle(uint32_t led);
extern void LED_AndOn (uint32_t led);

#ifdef __cplusplus
}
#endif  
#endif
