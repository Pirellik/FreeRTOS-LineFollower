/*
 * task_encoder_handler.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#include "task_encoder_handler.h"
#include "encoders.h"
#include "tim.h"

static TaskHandle_t encoderHandlerTaskHandle = NULL;

static void taskEncoderHandler(void *p)
{
	ENCODER_T *left_encoder_ptr1 = getLeftEncoderPtr();
	ENCODER_T *right_encoder_ptr1 = getRightEncoderPtr();

	while(1)
	{
		updateEncoder(left_encoder_ptr1, 1);
		updateEncoder(right_encoder_ptr1, -1);
		osDelay(1);
	}
	vTaskDelete(NULL);
}

void initTaskEncoderHandler()
{
    ENCODER_T *left_encoder_ptr = getLeftEncoderPtr();
    ENCODER_T *right_encoder_ptr = getRightEncoderPtr();
    initEncoder(left_encoder_ptr, TIM1, &htim1);
    initEncoder(right_encoder_ptr, TIM4, &htim4);

	xTaskCreate(taskEncoderHandler,
			   (const char *const)"EncoderHandlerTask",
	  		   configMINIMAL_STACK_SIZE,
	  		   0,
			   configMAX_PRIORITIES-1,
	  		   &encoderHandlerTaskHandle);
}

eTaskState getEncoderHandlerTaskState()
{
	return eTaskGetState(encoderHandlerTaskHandle);
}

void suspendTaskEncoderHandler()
{
	if(getEncoderHandlerTaskState() != eSuspended)
	{
		vTaskSuspend(encoderHandlerTaskHandle);
	}
}


void resumeTaskEncoderHandler()
{
	if(getEncoderHandlerTaskState() == eSuspended)
	{
		vTaskResume(encoderHandlerTaskHandle);
	}
}

