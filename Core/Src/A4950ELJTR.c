#include "A4950ELJTR.h"
#include "stm32f4xx_hal_tim.h"

HAL_StatusTypeDef A4950_Init(TIM_HandleTypeDef *htim)
{
    return HAL_TIM_PWM_Init(htim);
}

void A4950_Duty_Cycle(TIM_HandleTypeDef *htim,float dutycycle)
{
    
}