/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
typedef enum _enumControlType
{
  PID_POSITION	= 0x00,
  STR_POSITION	= 0x01,
  PID_SPEED 		= 0x10,
  STR_SPEED 		= 0x11,
}enumControlType;

typedef enum _enumMotorEn
{
  MOTOR_ENABLE	= 0x00,
  MOTOR_DISABLE	= 0x01,
}enumMotorEn;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
