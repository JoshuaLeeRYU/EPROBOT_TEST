#include "main.h"

HAL_StatusTypeDef Encoder_Init(TIM_HandleTypeDef *htim);
float Get_Encoder_RPS_Excount(int32_t counter,uint8_t channel,uint32_t encoder_p,float encoder_k);
float Get_Encoder_RPS(TIM_HandleTypeDef *htim,uint32_t encoder_p,float encoder_k);
float Get_Encoder_Ang_V(TIM_HandleTypeDef *htim,uint32_t encoder_p,float encoder_k);