/*
 * state_machine.h
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

typedef enum
{
	STATE_IDLE = 0,
	STATE_RUN_NORMAL = 1,
	STATE_RUN_TRACK_RECORDING = 2,
	STATE_RUN_WITH_RECORDED_TRACK = 3
} ENUM_PROGRAM_STATE_T;

typedef enum
{
	REQ_BACK_TO_IDLE = 0,
	REQ_START_LF_NORMAL_MODE = 1,
	REQ_START_LF_TRACK_RECORDING = 2,
	REQ_START_LF_WITH_RECORDED_TRACK = 3
} ENUM_STATE_LEVEL_REQUEST_T;


void updateStateMachine(ENUM_STATE_LEVEL_REQUEST_T req);
uint8_t getCurrentState();

#endif /* STATE_MACHINE_H_ */
