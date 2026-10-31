#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include <stdint.h>
#include "encoder.h"

#define ENCODER_CHANNEL_NUMBER 10
#define PI 3.1415926f
#define P2I 6.2831853f


HAL_StatusTypeDef Encoder_Init(TIM_HandleTypeDef *htim)
{
    return HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}

static int32_t last_counter[ENCODER_CHANNEL_NUMBER]={0};
static uint8_t Inited[ENCODER_CHANNEL_NUMBER]={0};
float Get_Encoder_RPS_Fxdt(TIM_HandleTypeDef *htim,uint8_t encoder_channel,float dt_s,uint32_t encoder_p,float encoder_k) //计算转速（r/s）,自己获得编码器值.encoder_p = 分辨率*倍率，encoder_k = 齿轮系数
{
    if (Inited[encoder_channel]==0) {
        Inited[encoder_channel]=1;
        last_counter[encoder_channel]=(int32_t)__HAL_TIM_GET_COUNTER(htim);
        return 0.0f;
    }
    uint32_t counter = __HAL_TIM_GET_COUNTER(htim);
    int16_t d_counter = (int16_t)((uint16_t)counter - (uint16_t)last_counter[encoder_channel]);
    last_counter[encoder_channel]=counter;
    return encoder_k*(d_counter/((dt_s)*encoder_p));
}

