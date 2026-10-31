#include "servo.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_tim.h"
#include <stdint.h>
#include <sys/_intsup.h>

#define DUTY_MIN 0.025f
#define DUTY_MAX 0.125f
#define ANG_RANGE 180
#define SERVO_CHANNEL TIM_CHANNEL_2
void Servo_Init(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Init(htim);
    __HAL_TIM_SET_COMPARE(htim, SERVO_CHANNEL, 0);
    return;
}

static uint32_t duty_to_ccr(float duty,TIM_HandleTypeDef *htim)
{
    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(htim);
    if (duty <= 0.0f) return 0;
    uint32_t ccr = (uint32_t)(duty * (float)(arr + 1) + 0.5f);
    return (ccr > arr + 1) ? (arr + 1) : ccr;
}

void Servo_Set_Ang(TIM_HandleTypeDef *htim,int ang)
{
    float duty=DUTY_MIN+((DUTY_MAX-DUTY_MIN)/ANG_RANGE)*ang;
    uint32_t ccr=duty_to_ccr(duty, htim);
    __HAL_TIM_SET_COMPARE(htim, SERVO_CHANNEL, ccr);
    return;
}
