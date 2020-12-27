#include "stm32f4xx.h"
#include "system_timetick.h"
#include "driver.h"

void init_main(void);
void PWM0_Set_Freq(uint32_t freq);
void PWM0_Set_Duty(int16_t d);
int32_t ENC0_GetPos(void);
int32_t 	pulse_cur = 0.0;


/* Get encoder counter 32 bit */
int32_t ENC0_GetPos(void)
{
	static int32_t 	p = 0, p_pre = 0, dp = 0;
	
	p = (int32_t)TIM1->CNT;
	dp = p - p_pre;
	if (dp > 32768)
		dp -= 65536;
	else if (dp < -32768)
		dp += 65536;
	p_pre = p;
	pulse_cur += dp;
	
	return pulse_cur;
}

/* Setup pwm frequency - unit: Hz */
void PWM0_Set_Freq(uint32_t freq)
{
	uint32_t period;
	
	period = 84000000/(freq*(TIM12->PSC+1))-1;	
	if (period > 0xffff)
		period = 0xffff;
	
	TIM12->ARR = period;
}

/* Output pwm frequency - unit: 0.1% */
void PWM0_Set_Duty(int16_t d)
{
	if (d<-1000)
		d = -600;
	else if (d>1000)
		d = 600;

	if (d == 0)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);  	// disable pwm
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}	
	else if (d > 0)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_10);	// enabe pwm
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); 	// dir = 1
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);	// enabe pwm
		GPIO_SetBits(GPIOB,GPIO_Pin_15); 		// dir = 0
		d = -d;
	}
	d = (TIM12->ARR+1)*d/1000;
	TIM12->CCR1 = (uint32_t)d;
}

void init_main(void)
{
	GPIO_InitTypeDef 				GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 			TIM_OCInitStructure;
	
	//**********PWM*********
	/* TIM clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 

	/* PULSE pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
	
	/* DIR, EN pins configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* TIM CH1 configuration */
	TIM_TimeBaseStructure.TIM_Period = 1000-1;// 2M/1000=2k
	TIM_TimeBaseStructure.TIM_Prescaler = 42 - 1;// 84M/42=2M
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);

	TIM_Cmd(TIM12, ENABLE);
		
	//**********ENCODER*********
	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* TIM1 channel1,2 configuration */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);

	/* Initialise encoder interface */
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	/* TIM enable counter */
	TIM1->CNT = 0;
	TIM_Cmd(TIM1, ENABLE);	

}

void delay_us(uint16_t period){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  	TIM6->PSC = 83;		// clk = SystemCoreClock / 4 / (PSC+1) *2 = 1MHz
  	TIM6->ARR = period-1;
  	TIM6->CNT = 0;
  	TIM6->EGR = 1;		// update registers;

  	TIM6->SR  = 0;		// clear overflow flag
  	TIM6->CR1 = 1;		// enable Timer6

  	while (!TIM6->SR);
    
  	TIM6->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}

void delay_01ms(uint16_t period){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  	TIM6->PSC = 8399;		// clk = SystemCoreClock / 4 / (PSC+1) *2 = 10KHz
  	TIM6->ARR = period-1;
  	TIM6->CNT = 0;
  	TIM6->EGR = 1;		// update registers;

  	TIM6->SR  = 0;		// clear overflow flag
  	TIM6->CR1 = 1;		// enable Timer6

  	while (!TIM6->SR);
    
  	TIM6->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}
