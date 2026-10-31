#include <stdint.h>

float Clc_PID_Duty(uint8_t channel,float dt_s,float err, float kp,float ki ,float kd);//单位为s