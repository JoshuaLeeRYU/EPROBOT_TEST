#include "stm32f4xx_hal.h"
#include <stdint.h>

#define PID_CHANNEL_NUMBER 10
#define DMIN 0.0f
static const float duty_max[PID_CHANNEL_NUMBER]={1.0f,10,10,10,10,10,10,10,10,10};
static uint32_t last_tick[PID_CHANNEL_NUMBER] = {0};
static float integral[PID_CHANNEL_NUMBER] = {0};
static float last_err[PID_CHANNEL_NUMBER] = {0};
static uint8_t inited[PID_CHANNEL_NUMBER]={0};
float Clc_PID_Duty(uint8_t channel,float err, float kp,float ki ,float kd)//单位为s,控制周期不得小于1ms
{
    const float dmax = duty_max[channel];
    if (channel>=PID_CHANNEL_NUMBER) {
    return 0.0f;
    }
    if (inited[channel]==0) {
    inited[channel] = 1;
    last_tick[channel]=HAL_GetTick();
    last_err[channel] = err;
    integral[channel] = 0.0f;
    return 0.0f;
    }
    uint32_t now=HAL_GetTick();
    uint32_t dt_ms=(now-last_tick[channel]);
    if (dt_ms == 0) {
    float out = kp * err + ki * integral[channel];
    if (out > dmax) out = dmax;
    if (out < DMIN) out = DMIN;
    return out;
    }
    float dt=dt_ms*0.001f;
    float D=kd*(err-last_err[channel])/dt;
    float PID = kp * err + ki * integral[channel] + D;
    if (!((PID > dmax && err > 0) ||
      (PID < DMIN && err < 0))) {
    integral[channel] += err * dt;
    }
    
    if (PID > dmax) {
        PID = dmax;
    }
    if (PID < DMIN) {
        PID = DMIN;
    }
    last_err[channel]=err;
    last_tick[channel]=now;
    return PID;
}