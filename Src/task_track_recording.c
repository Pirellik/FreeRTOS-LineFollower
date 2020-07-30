/*
 * task_track_recording.c
 *
 *  Created on: 16.04.2019
 *      Author: kamil
 */

#include "task_track_recording.h"
#include "encoders.h"

volatile static TaskHandle_t trackRecordingTaskHandle = NULL;
volatile static uint16_t recorded_track_left[8192] = {0};
volatile static uint16_t recorded_track_right[8192] = {0};
volatile static ENCODER_T *leftEncPtr, *rightEncPtr;
volatile static uint16_t counter = 0;

static void taskTrackRecording(void *p)
{
	while(1)
	{
		recorded_track_left[counter] = leftEncPtr->ticks;
		recorded_track_right[counter] = rightEncPtr->ticks;
		counter ++;
		osDelay(10);
	}
	vTaskDelete(NULL);
}


void initTaskTrackRecording()
{
	if(trackRecordingTaskHandle == NULL)
	{
		leftEncPtr = getLeftEncoderPtr();
		rightEncPtr = getRightEncoderPtr();

			xTaskCreate(taskTrackRecording,
				(const char *const)"TrackRecordingTask",
				configMINIMAL_STACK_SIZE,
				0,
				configMAX_PRIORITIES-1,
				&trackRecordingTaskHandle);

		vTaskSuspend(trackRecordingTaskHandle);
	}

}

eTaskState getTrackRecordingTaskState()
{
	return eTaskGetState(trackRecordingTaskHandle);
}

void suspendTaskTrackRecording()
{
	if(getTrackRecordingTaskState() != eSuspended)
	{
		vTaskSuspend(trackRecordingTaskHandle);
	}
}

void resumeTaskTrackRecording()
{
	if(getTrackRecordingTaskState() == eSuspended)
	{
		resetTaskDataTrackRecording();
		vTaskResume(trackRecordingTaskHandle);
	}
}

void resetTaskDataTrackRecording()
{
	int i = 0;
	for(i = 0; i < 8192; i ++)
	{
		recorded_track_left[i] = 0;
		recorded_track_right[i] = 0;
	}

	resetEncoder(leftEncPtr);
	resetEncoder(rightEncPtr);
	counter = 0;
}

uint16_t *getLeftRecordedTrackPtr()
{
	return recorded_track_left;
}

uint16_t *getRightRecordedTrackPtr()
{
	return recorded_track_right;
}
