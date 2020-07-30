/*
 * encoders.h
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#ifndef ENCODERS_H_
#define ENCODERS_H_

#include "stm32f4xx_hal.h"

typedef struct ENCODER {
	uint16_t last_read;
	float rotated_angle;
	float angular_speed;

	TIM_TypeDef *timer_ptr;
	TIM_HandleTypeDef *htim_ptr;
	int32_t ticks;
	int32_t prev_ticks_for_speed_meas;
} ENCODER_T;


void initEncoder(ENCODER_T *encoder_ptr, TIM_TypeDef *timer_ptr, TIM_HandleTypeDef *htim_ptr);
void updateEncoder(ENCODER_T *encoder_ptr, int8_t side_mod);
void resetEncoder(ENCODER_T *encoder_ptr);

ENCODER_T *getLeftEncoderPtr();
ENCODER_T *getRightEncoderPtr();


#endif /* ENCODERS_H_ */
