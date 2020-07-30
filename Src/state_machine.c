/*
 * state_machine.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */


#include "state_machine.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

volatile static ENUM_PROGRAM_STATE_T state = STATE_IDLE;

void updateStateMachine(ENUM_STATE_LEVEL_REQUEST_T req)
{
	switch(state)
	{
		case STATE_IDLE:
		{
			if(req == REQ_START_LF_NORMAL_MODE)
			{
				state = STATE_RUN_NORMAL;
			}
			else if(req == REQ_START_LF_TRACK_RECORDING)
			{
				state = STATE_RUN_TRACK_RECORDING;
			}
			else if(req == REQ_START_LF_WITH_RECORDED_TRACK)
			{
				state = STATE_RUN_WITH_RECORDED_TRACK;
			}
			break;
		}
		case STATE_RUN_NORMAL:
		{
			if(req == REQ_BACK_TO_IDLE)
			{
				state = STATE_IDLE;
			}
			break;
		}
		case STATE_RUN_TRACK_RECORDING:
		{
			if(req == REQ_BACK_TO_IDLE)
			{
				state = STATE_IDLE;
			}
			break;
		}
		case STATE_RUN_WITH_RECORDED_TRACK:
		{
			if(req == REQ_BACK_TO_IDLE)
			{
				state = STATE_IDLE;
			}
			break;
		}
		default:
		{
			break;
		}
	}
}


uint8_t getCurrentState()
{
	return state;
}

