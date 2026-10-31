#include "stm32f4xx_hal.h"
#include <stdint.h>

#define PID_CHANNEL_NUMBER 10
#define DMIN 0.0f

static const float d_max[PID_CHANNEL_NUMBER]={0.9999f,10,10,10,10,10,10,10,10,10};
static float integral[PID_CHANNEL_NUMBER] = {0};
static float last_err[PID_CHANNEL_NUMBER] = {0};
static uint8_t inited[PID_CHANNEL_NUMBER]={0};
float Clc_PID_Duty(uint8_t channel,float dt_s,float err, float kp,float ki ,float kd)//单位为s
{
    const float dmax = d_max[channel];
    if (channel>=PID_CHANNEL_NUMBER) {
    return 0.0f;
    }
    if (inited[channel]==0) {
    inited[channel] = 1;
    last_err[channel] = err;
    integral[channel] = 0.0f;
    return 0.0f;
    }
    float D=kd*(err-last_err[channel])/dt_s;
    float PID = kp * err + ki * integral[channel] + D;
    if (!((PID > dmax && err > 0) ||
      (PID < DMIN && err < 0))) {
    integral[channel] += err * dt_s;
    }
    
    if (PID > dmax) {
        PID = dmax;
    }
    if (PID < DMIN) {
        PID = DMIN;
    }
    last_err[channel]=err;
    return PID;
}