
#include "stm32f4xx.h"
#include "system_timetick.h"

void init_main(void);
void PWM0_Set_Freq(uint32_t freq);
void PWM0_Set_Duty(int16_t d);
extern int32_t ENC0_GetPos(void);

void delay_us(uint16_t period);
void delay_01ms(uint16_t period);
