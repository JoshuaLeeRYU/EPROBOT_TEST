#include "main.h"

HAL_StatusTypeDef Encoder_Init(TIM_HandleTypeDef *htim);
float Get_Encoder_RPS_Fxdt(TIM_HandleTypeDef *htim,uint8_t encoder_channel,float dt_s,uint32_t encoder_p,float encoder_k); //计算转速（r/s）,自己获得编码器值.encoder_p = 分辨率*倍率，encoder_k = 齿轮系数
float Get_Encoder_RPS(TIM_HandleTypeDef *htim,uint32_t encoder_p,float encoder_k);