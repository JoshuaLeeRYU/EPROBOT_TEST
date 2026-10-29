#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include <stdint.h>
#include "encoder.h"

void Encoder_Init(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
    return;
}

static uint32_t last_tick[CHANNEL_NUMBER]={0};
static int32_t last_counter[CHANNEL_NUMBER]={0};
static uint8_t Inited[CHANNEL_NUMBER]={0};
float Get_Encoder_RPS_Excount(int32_t counter,uint8_t channel,uint32_t encoder_p,float encoder_k)  //计算转速（r/s）,外部给编码器值。encoder_p = 分辨率*倍率，encoder_k = 齿轮系数
{
    if(channel>=CHANNEL_NUMBER) return 0.0f;
    if (Inited[channel] == 0) {
        Inited[channel] = 1;
        last_tick[channel]=HAL_GetTick();
        last_counter[channel]=counter;
        return 0.0f;
    }
    uint32_t now=HAL_GetTick();
    int32_t d_counter = (int32_t)((uint32_t)counter - (uint32_t)last_counter[channel]);
    uint32_t dt = now-last_tick[channel];
    if (dt==0) return 0.0f;
    last_tick[channel]=now;
    last_counter[channel]=counter;
    return encoder_k*(d_counter/((dt/1000.0f)*encoder_p));
}

static int32_t last_counter1 = 0;
static uint8_t Inited1 = 0;
static uint32_t last_tick1 = 0;
float Get_Encoder_RPS(TIM_HandleTypeDef *htim,uint32_t encoder_p,float encoder_k) //计算转速（r/s）,自己获得编码器值.encoder_p = 分辨率*倍率，encoder_k = 齿轮系数
{
    if (Inited1==0) {
        Inited1=1;
        last_counter1=(int32_t)__HAL_TIM_GET_COUNTER(htim);
        last_tick1=HAL_GetTick();
        return 0.0f;
    }
    uint32_t counter = __HAL_TIM_GET_COUNTER(htim);
    uint32_t now=HAL_GetTick();
    int32_t d_counter = (int32_t)((uint32_t)counter - (uint32_t)last_counter1);
    uint32_t dt = now-last_tick1;
    last_tick1=now;
    last_counter1=counter;
    if (dt==0||encoder_p == 0) return 0.0f;
    return encoder_k*(d_counter/((dt/1000.0f)*encoder_p));
}

float Get_Encoder_Ang_V(TIM_HandleTypeDef *htim,uint32_t encoder_p,float encoder_k)//计算角速度(rad/s),自己获得编码器值.encoder_p = 分辨率*倍率，encoder_k = 齿轮系数
{
    return P2I*Get_Encoder_RPS(htim,encoder_p,encoder_k);//2pi*n
}