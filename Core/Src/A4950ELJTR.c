#include "main.h"
#include "A4950ELJTR.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"
#include <stdint.h>

#define _1_TIM &htim3
#define _1_IN1 TIM_CHANNEL_3
#define _1_IN2 TIM_CHANNEL_4
void A4950_Init_1_()
{
    HAL_TIM_PWM_Start(_1_TIM, _1_IN1);
    HAL_TIM_PWM_Start(_1_TIM, _1_IN2);
    __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN1, 0);
    __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN2, 0);
}

void A4950_CTRL_1_(float CCR,uint8_t way)
{
switch (way) {
    case 0:
        __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN1, CCR);
        __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN2, 0);
        break;
    case 1:
        __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN2, CCR);
        __HAL_TIM_SET_COMPARE(_1_TIM, _1_IN1, 0);
        break;
    default:
}
return;
}
