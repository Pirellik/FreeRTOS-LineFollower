/*
 * encoders.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */
#include "encoders.h"
#include "math.h"


static ENCODER_T left_encoder;
static ENCODER_T right_encoder;

void initEncoder(ENCODER_T *encoder_ptr, TIM_TypeDef *timer_ptr, TIM_HandleTypeDef *htim_ptr)
{
	encoder_ptr->ticks = 0;
	encoder_ptr->rotated_angle = 0;
	encoder_ptr->angular_speed = 0;

	encoder_ptr->timer_ptr = timer_ptr;
	encoder_ptr->htim_ptr = htim_ptr;
	encoder_ptr->last_read = 0;
	encoder_ptr->prev_ticks_for_speed_meas = 0;

	HAL_TIM_Encoder_Start(encoder_ptr->htim_ptr,TIM_CHANNEL_ALL);
}

void updateEncoder(ENCODER_T *encoder_ptr, int8_t side_mod)
{
	uint16_t read = encoder_ptr->timer_ptr->CNT;
	int32_t difference = side_mod * (read - encoder_ptr->last_read);
	encoder_ptr->last_read = read;
	if(difference >= 0 && difference < 2000)
	{
		encoder_ptr->ticks += difference;
	}
	else if(difference <= 0 && difference > - 2000)
	{
		encoder_ptr->ticks += difference;
	}
	else if(difference >= 2000)
	{
		encoder_ptr->ticks += difference - 65535;
	}

	else if(difference <= - 2000)
	{
		encoder_ptr->ticks += difference + 65535;
	}
	encoder_ptr->rotated_angle = 2 * M_PI * encoder_ptr->ticks / 120.0;
	encoder_ptr->angular_speed = (2 * M_PI * (encoder_ptr->ticks - encoder_ptr->prev_ticks_for_speed_meas) / 0.12);
	encoder_ptr->prev_ticks_for_speed_meas = encoder_ptr->ticks;


}

ENCODER_T *getLeftEncoderPtr()
{
	return &left_encoder;
}

ENCODER_T *getRightEncoderPtr()
{
	return &right_encoder;
}

void resetEncoder(ENCODER_T *encoder_ptr)
{
	encoder_ptr->ticks = 0;
	encoder_ptr->rotated_angle = 0;
	encoder_ptr->angular_speed = 0;
	encoder_ptr->last_read = 0;
	encoder_ptr->timer_ptr->CNT = 0;
	encoder_ptr->prev_ticks_for_speed_meas = 0;
}

