#include <stdint.h>

float Clc_PID_Duty(uint8_t channel,float err, float kp,float ki ,float kd);//单位为s,控制周期不得小于1ms