/*
 * task_manager.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#include "task_normal_run.h"
#include "task_manager.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "state_machine.h"
#include "task_track_recording.h"

void updateRunningTasks(ENUM_PROGRAM_STATE_T state)
{
	switch(state)
	{
		case STATE_IDLE:
		{
			suspendTaskNormalRun();
			suspendTaskTrackRecording();
			break;
		}
		case STATE_RUN_NORMAL:
		{
			resumeTaskNormalRun();
			break;
		}
		case STATE_RUN_TRACK_RECORDING:
		{
			resumeTaskTrackRecording();
			break;
		}
		case STATE_RUN_WITH_RECORDED_TRACK:
		{

			break;
		}
		default:
		{
			break;
		}
	}
}

