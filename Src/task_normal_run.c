/*
 * task_encoder_handler.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */


#include "task_normal_run.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "motors.h"
#include "main.h"
#include "task_motor_controller.h"
#include "line_sensor.h"
#include "config.h"


static TaskHandle_t normalRunTaskHandle = NULL;
static LINE_SENSOR_T *line_sensor_ptr;
static PID_PARAMS_T *main_pid_ptr;
static CONFIG_T *config;

static void taskNormalRun(void *p)
{
	while(1)
	{
		float control;
		update_pid_error(main_pid_ptr, line_sensor_ptr->measured_error);
		control = get_pid_control(main_pid_ptr);
		if(!line_sensor_ptr->line_lost)
		{
			newLeftMotorSpeed(config->normalModeSpeed - control);
			newRightMotorSpeed(config->normalModeSpeed + control);
		}
		else
		{
			newLeftMotorSpeed(config->lostTrackSpeed - control);
			newRightMotorSpeed(config->lostTrackSpeed + control);
		}
		osDelay(3);
	}
	vTaskDelete(NULL);
}

void initTaskNormalRun()
{
	if(normalRunTaskHandle == NULL)
	{
		line_sensor_ptr = getLineSensorPtr();
		main_pid_ptr = getMainPidPtr();
		config = getConfigPtr();
		set_pid_params(main_pid_ptr, config->mainPIDkP, config->mainPIDkI, config->mainPIDkD, config->mainPIDIntSaturation);
		update_pid_set_point(main_pid_ptr, 0);

		xTaskCreate(taskNormalRun,
				(const char *const)"NormalRunTask",
				configMINIMAL_STACK_SIZE,
				0,
				configMAX_PRIORITIES-1,
				&normalRunTaskHandle);

		vTaskSuspend(normalRunTaskHandle);
	}
}


void resetTaskDataNormalRun()
{
	newLeftMotorSpeed(0);
	newRightMotorSpeed(0);
}

eTaskState getNormalRunTaskState()
{
	return eTaskGetState(normalRunTaskHandle);
}

void suspendTaskNormalRun()
{
	if(getNormalRunTaskState() != eSuspended)
	{
		vTaskSuspend(normalRunTaskHandle);
		resetTaskDataNormalRun();
	}
}


void resumeTaskNormalRun()
{
	if(getNormalRunTaskState() == eSuspended)
	{
		vTaskResume(normalRunTaskHandle);
	}
}


