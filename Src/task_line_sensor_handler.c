/*
 * task_line_sensor_handler.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#include "task_line_sensor_handler.h"
#include "line_sensor.h"
#include "adc.h"
#include "config.h"

static TaskHandle_t lineSensorHandlerTaskHandle = NULL;
static uint8_t thresholds[8] = { 170, 170, 170, 170, 170, 170, 170, 170 };
static int8_t weights[8] = { -16, -9, -4, -2, 2, 4, 9, 16 };
static CONFIG_T *config;

static void taskLineSensorHandler(void *p)
{
	while(1)
	{
		compute_error();
		osDelay(1);
	}
	vTaskDelete(NULL);
}

void initTaskLineSensorHandler()
{
	config = getConfigPtr();
	init_line_sensor(&hadc1, config->thresholds, config->weights);
	//init_line_sensor(&hadc1, thresholds, weights);

	xTaskCreate(taskLineSensorHandler,
			   (const char *const)"LineSensorHandlerTask",
	  		   configMINIMAL_STACK_SIZE,
	  		   0,
			   configMAX_PRIORITIES-1,
	  		   &lineSensorHandlerTaskHandle);
}

eTaskState getLineSensorHandlerTaskState()
{
	return eTaskGetState(lineSensorHandlerTaskHandle);
}

void suspendTaskLineSensorHandler()
{
	if(getLineSensorHandlerTaskState() != eSuspended)
	{
		vTaskSuspend(lineSensorHandlerTaskHandle);
	}
}


void resumeTaskLineSensorHandler()
{
	if(getLineSensorHandlerTaskState() == eSuspended)
	{
		vTaskResume(lineSensorHandlerTaskHandle);
	}
}

