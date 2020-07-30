/*
 * config.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32f4xx_hal.h"

typedef enum
{
	SET_MAIN_PID_KP = 4,
	SET_MAIN_PID_KI = 5,
	SET_MAIN_PID_KD = 6,
	SET_MAIN_PID_MAX_INT_VALUE = 7,

	SET_NORMAL_MODE_SPEED = 8,
	SET_LOST_TRACK_SPEED = 9,
	SET_TRACK_RECORDING_SPEED = 10,

	SET_MOTOR_PID_KP = 11,
	SET_MOTOR_PID_KI = 12,
	SET_MOTOR_PID_KD = 13,
	SET_MOTOR_PID_MAX_INT_VALUE = 14,

	SET_SENSOR_WEIGHTS = 15,
	SET_SENSOR_THRESHOLDS = 16

} ENUM_SET_REQUEST_T;


typedef struct CONFIG
{
	float mainPIDkP;
	float mainPIDkI;
	float mainPIDkD;
	float mainPIDIntSaturation;

	float normalModeSpeed;
	float lostTrackSpeed;
	float trackRecordingSpeed;

	float motorPIDkP;
	float motorPIDkI;
	float motorPIDkD;
	float motorPIDIntSaturation;

	int8_t weights[8];
	uint8_t thresholds[8];

} CONFIG_T;

void param_configuration(uint8_t *data);
void set_initial_config();
CONFIG_T *getConfigPtr();

#endif /* CONFIG_H_ */
