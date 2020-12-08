/*
 * File: ert_main.c
 *
 * Real-Time Workshop code generated for Simulink model pid.
 *
 * Model version                        : 1.18
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Fri Sep 30 17:01:27 2016
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Fri Sep 30 17:01:28 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "stm32f4xx.h"                 
#include "system_timetick.h"
#include "driver.h"
#include "pid.h"                       /* PID Model's header file */
#include "str.h"                       /* STR Model's header file */
#include "rtwtypes.h"                  /* MathWorks types */

#define BUFF_SIZE	20	/* bytes */

#define PID				0x0	
#define STR				0x1
#define	LQR				0x2

static boolean_T OverrunFlag = 0;

uint8_t Value_Buff[BUFF_SIZE] = {0};

uint8_t ASCII_Char_Udk[5] = {0};
uint8_t ASCII_Char_In2[5] = {0};
uint8_t ASCII_Char_Out2[5] = {0};

int16_t udk, i;
int ControlType = 0;
int32_t sCount = 0;

/* Exported block signals */
real_T In2;                            /* '<Root>/In2' */
real_T Out2;                           /* '<Root>/Setpoint (Deg)' */
real_T Out1;                           /* '<Root>/Saturation' */

void Convert_To_ASCII(int16_t input, int8_t size, uint8_t *data_out);
void rt_OneStep(void);
void Convert_To_ASCII(int16_t input, int8_t size, uint8_t *data_out);
void init_uart_dma(void);

int main(void)
{
	int16_t Temp = 0;
	In2 = 0;
	/* Enable SysTick at 5ms interrupt */
  SysTick_Config(SystemCoreClock/200);
	init_uart_dma();
  delay_01ms(1000);
  init_main();
	PWM0_Set_Freq(1000);
	PWM0_Set_Duty(0);
  /* Initialize model */
//	#ifdef PID
//		pid_initialize();
//	#endif
//	#ifdef STR
		str_initialize();
//	#endif
//	switch (ControlType)
//		case PID
//			pid_initialize();
//		case STR
//			str_initialize();
//		default
//			pid_initialize();
//	end
  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.005 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   */
  sCount = 0;
  while(1){			  
		if(tick_flag) { 
			tick_flag = 0;
			/*After caculated, the value of encoder count/1 circle is 1510*/
			In2 = (double)ENC0_GetPos()/9200*360.0;
			rt_OneStep();
			Out1 = Out1*1000/12;
			udk = (int)Out1;
			PWM0_Set_Duty(udk);
			if(tick_count>20000)		break;
		}
		if((200 <tick_count_uart)&(tick_count_uart < 210))
		{
			 Convert_To_ASCII(udk,5,ASCII_Char_Udk);
			 Convert_To_ASCII((int16_t)In2,5,ASCII_Char_In2);
			 Convert_To_ASCII(Out2,5,ASCII_Char_Out2);
			 for(int sCount =0;sCount<5;sCount++)
			 {
				 Value_Buff[sCount] = ASCII_Char_Out2[sCount];
				 Value_Buff[sCount+5+1] = ASCII_Char_Udk[sCount];
				 Value_Buff[sCount+10+2] = ASCII_Char_In2[sCount];
			 }
			 Value_Buff[sCount+5] = 0x20;
			 Value_Buff[sCount+11] = 0x20;
			 Value_Buff[18] = 0x0D;
			 Value_Buff[19] = 0x0A;
			 DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
			 DMA1_Stream4->NDTR = BUFF_SIZE; // Have to re-assign NDTR because when transferd 1 byte, NDTR will decrese 1
			 DMA_Cmd(DMA1_Stream4, ENABLE);
			 tick_count_uart = 0;
		}
	}	

	PWM0_Set_Duty(0);
#if 0
	while(1)
	{
uint8_t ASCII_Char_Udk[5] = {0};
uint8_t ASCII_Char_In2[5] = {0};
uint8_t ASCII_Char_Out2[5] = {0};		
	}
#endif
  /* Terminate model */
//  pid_terminate();

}
/*--------------------------------------*/
void rt_OneStep(void)
{
  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag++) {
    rtmSetErrorStatus(pid_M, "Overrun");
    return;
  }

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
//  pid_step();
	str_step();
  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag--;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
/*--------------------------------------*/
/*UART&DMA configuration*/
void init_uart_dma(void)
{
  GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;   
	DMA_InitTypeDef  	DMA_InitStructure;
   
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Connect UART4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 

  /* GPIO Configuration for UART4 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIO Configuration for USART Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART4, &USART_InitStructure);
	
	/* Enable USART */
  USART_Cmd(UART4, ENABLE);
	
	/* Enable UART4 DMA */
  USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 
	
	
	/* DMA1 Stream4 Channel4 for UART4 Tx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Value_Buff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //Not increase peripheral address
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //increase DMA address
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //UART have size 1 byte/transfering
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream4, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream4, ENABLE);

}
/*--------------------------------------*/
void Convert_To_ASCII(int16_t input, int8_t size, uint8_t *data_out)
{
	 if(input<0)
	 {
		 data_out[0] = 0x2D;
		 input = -input;
	 }
	 else
	 {
		 data_out[0] = 0x30;
	 }
	 uint8_t temp = 0;
	 for(int sCount_t =0; sCount_t<(size-1);sCount_t++)
	{
		temp = input%10;
		input = input/10;
		data_out[size - sCount_t -1] = temp+0x30;
	}
}
