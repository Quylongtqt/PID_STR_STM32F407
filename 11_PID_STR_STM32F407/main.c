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
#include "pid_speed.h"
#include "str.h"                       /* STR Model's header file */
#include "str_speed.h"
#include "rtwtypes.h"                  /* MathWorks types */
#include "variable_declare.h"    

#define TX_BUFF_SIZE	8	/* bytes */
#define RX_BUFF_SIZE	8	/* bytes */


#define BUFF_SIZE			8 /* bytes */    
#define POSITION
//#define UART
//#define SPEED
static boolean_T OverrunFlag = 0;

uint8_t txbuff[TX_BUFF_SIZE];
uint8_t rxbuff[RX_BUFF_SIZE];

//uint16_t data_handle[BUFF_SIZE];
uint16_t data_handle[BUFF_SIZE] = {0xAA,0x00,0x11,0x00,0x14,0x00,0x00,0x00};

uint8_t ASCII_Char_Udk[5] = {0};
uint8_t ASCII_Char_In2[5] = {0};
uint8_t ASCII_Char_Out2[5] = {0};

int16_t udk, pre_udk;

enumControlType ControlType;
enumMotorEn MotorEn;

/* Variable for Speed*/
double Pos = 0;
double Pre_Pos = 0;
double Speed = 0;
double Out_Speed = 0;
/* End of declare for Speed*/

/* Exported block signals */

real_T In1 = 0;                            /* '<Root>/Setpoint (Deg) or (RPM' */
real_T In2 = 0;                            /* '<Root>/In2' */
real_T Out1 = 0;                           /* '<Root>/Saturation' */
real_T Out2 = 0;                           /* '<Root>/Saturation' */

void rt_OneStep(void);
void init_uart_dma(void);
void Convert_To_ASCII(int16_t input, int8_t size, uint8_t *data_out);

int main(void)
{
	In1 = 0;
	In2 = 0;
	udk = 0;
	pre_udk = 0;
	
	/* Enable SysTick at 5ms interrupt */
  SysTick_Config(SystemCoreClock/200);
	init_uart_dma();
  delay_01ms(1000);
  init_main();	//init main in driver.c
  /* Set Freq and Duty for PWM */
	PWM0_Set_Freq(1000);
	PWM0_Set_Duty(0);
	while(1)
	{
		/* Check byte[0] -> 0xAA: start excuting*/
    if(data_handle[0]== 0xAA)
    {      
      /* Check byte[1]-> Stop motor */
			MotorEn = data_handle[1];
      if(MotorEn == MOTOR_DISABLE)
      {
        //Stop motor
        PWM0_Set_Duty(0);
				delay_01ms(1000);
      }
      else
      {
        /* Read Data byte [2-4]*/
        ControlType = data_handle[2];
        /* Initialize model */
        switch (ControlType)
        {
          case PID_POSITION:
          {
              pid_initialize();
              break;
          }
          case STR_POSITION:
          {		
              str_initialize();
              break;
          }
          case PID_SPEED:
          {
              pid_speed_initialize();
              break;
          }
          case STR_SPEED:
          {
              str_speed_initialize();
              break;
          }
          default:
          {
              break;
          }
        }
				
        
        while(1)
        {
					if(MotorEn == MOTOR_DISABLE)
					{
						//Stop motor
						PWM0_Set_Duty(0);
						delay_01ms(1000);
					}
					else
					{
						In1 = (data_handle[4]) + ((data_handle[3])<<8);
						switch(ControlType)
						{
						case PID_POSITION:
						case STR_POSITION:
						{
							if(tick_flag)
							{
								tick_flag = 0;
								/*------------------------Potisiton Control-----------------------*/
								/*------------------------PID, STR Position-----------------------*/
								/*After caculated, the value of encoder count/1 circle is 1510*/
								In2 = (double)ENC0_GetPos()/200000*360.0;
								rt_OneStep();
								Out1 = Out1*1000/10;
								udk = (int)Out1;
								/*------------------------Saturation for Output---------------------*/
								if((In2 > In1-In1/1000)&(In2<In1+In1/1000))
								{
									udk = 0;
								}
								PWM0_Set_Duty(udk);
								/*-----------------------Send data to Tx UART4---------------------*/
								if((440 <tick_count_uart)&(tick_count_uart < 450))
								{
										
									tick_count_uart = 0;
									if(USART_GetITStatus(UART4, USART_IT_TXE)==RESET)
									{
											USART_SendData(UART4,In2);
									}
									tick_count_uart = 0;
									DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
									DMA1_Stream4->NDTR = TX_BUFF_SIZE; // Have to re-assign NDTR because when transferd 1 byte, NDTR will decrese 1
									
								}
							 }
							 break;
							}
						
								/*------------------------Speed-----------------------------*/
						 case PID_SPEED:
							{
								/*---------------------PID Speed-----------------------*/
								Pos = (double)ENC0_GetPos()/200000*360; //Position
								delay_01ms(10); //Delay 1ms
								Pre_Pos = Pos;
								Pos = (double)ENC0_GetPos()/200000*360; // Update Position
								Speed = (Pos - Pre_Pos)*1000/360*60; // vong/phut
								//////////Speed Control//////////
								In2 = Speed;
								pre_udk = udk;
								rt_OneStep();
								Out1 = Out1*1000/10;
								udk = (int)Out1 + pre_udk;
								PWM0_Set_Duty(udk);
								/*-----------------------Send data to Tx UART4---------------------*/
								if((440 <tick_count_uart)&(tick_count_uart < 450))
								{
									tick_count_uart = 0;
									DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
									DMA1_Stream4->NDTR = TX_BUFF_SIZE; // Have to re-assign NDTR because when transferd 1 byte, NDTR will decrese 1
									DMA_Cmd(DMA1_Stream4, ENABLE);
								}
								break;
							}
							case STR_SPEED:
							{
								/*---------------------STR Speed-----------------------*/
								Pos = (double)ENC0_GetPos()/200000*360; //Position
								delay_01ms(10); //Delay 1ms
								Pre_Pos = Pos;
								Pos = (double)ENC0_GetPos()/200000*360; // Update Position
								Speed = (Pos - Pre_Pos)*1000/360*60; // vong/phut
								/*------------------------Speed Control------------------------*/
								In2 = Speed;
								rt_OneStep();
								Out1 = Out1*1000/10;
								udk = (int)Out1;
								PWM0_Set_Duty(udk);
								/*-----------------------Send data to Tx UART4---------------------*/
								if((440 <tick_count_uart)&(tick_count_uart < 450))
								{
									tick_count_uart = 0;
									DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
									DMA1_Stream4->NDTR = TX_BUFF_SIZE; // Have to re-assign NDTR because when transferd 1 byte, NDTR will decrese 1
									DMA_Cmd(DMA1_Stream4, ENABLE);
								}
								break;
							}
							default:
								break;
						}
					}
					/*--------------------Time out for Control--------------------*/
          //if(tick_count>10000)		break; // time = 5xN ms
        }
        PWM0_Set_Duty(0); //Stop motor
      }
    }
    else
    {
      /*------------------------Noise-----------------------------*/
    }
	}
}

/*---------------DMA - UART4 Rx Interrupt---------------------*/
void DMA1_Stream2_IRQHandler(void)
{
	uint16_t i;
  /* Clear the DMA1_Stream2 TCIF2 pending bit */
  DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
  for(i=0; i<BUFF_SIZE; i++)
	{
    data_handle[i] = rxbuff[i];
	}
	DMA_Cmd(DMA1_Stream2, ENABLE);
}
/*--------------------------------------*/

/*-----------Function rt_OneStep--------*/
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
	switch (ControlType)
	{
		case PID_POSITION:
		{
				pid_step();
				break;
		}
		case STR_POSITION:
		{		
				str_step();
				break;
		}
		case PID_SPEED:
		{
				pid_speed_step();
				break;
		}
		case STR_SPEED:
		{
				str_speed_step();
				break;
		}
		default:
		{
				break;
		}
	}
  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag--;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
/*------End of the Function rt_OneStep--------*/

/*--------- Function init_uart_dma -----------*/
void init_uart_dma(void)
{
  GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;   
	DMA_InitTypeDef  	DMA_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;	
   
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

  /* GPIO Configuration for USART4 Rx */
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
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&txbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = TX_BUFF_SIZE;
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
	
	/* DMA1 Stream2 Channel4 for USART4 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = RX_BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream2, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream2, ENABLE);
	
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);

}
/*------End of the Function init_uart_dma--------*/

/*-------- Function Convert_To_ASCII ------------*/
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
/*------End of the Function Convert_To_ASCII--------*/
