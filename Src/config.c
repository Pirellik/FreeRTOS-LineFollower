/*
 * config.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#include "config.h"
#include "pid.h"

static CONFIG_T configuration;

CONFIG_T *getConfigPtr()
{
	return &configuration;
}

void param_configuration(uint8_t *data)
{
	switch(data[0])
	{
		case SET_MAIN_PID_KP:
		{
			PID_PARAMS_T *main_pid_ptr = getMainPidPtr();
			main_pid_ptr->kP = data[1] / 10.0;
			break;
		}
		case SET_MAIN_PID_KI:
		{
			PID_PARAMS_T *main_pid_ptr = getMainPidPtr();
			main_pid_ptr->kI = data[1] / 100.0;
			break;
		}
		case SET_MAIN_PID_KD:
		{
			PID_PARAMS_T *main_pid_ptr = getMainPidPtr();
			main_pid_ptr->kD = data[1] / 10.0;
			break;
		}
		case SET_MAIN_PID_MAX_INT_VALUE:
		{
			PID_PARAMS_T *main_pid_ptr = getMainPidPtr();
			main_pid_ptr->integral_saturation = data[1] + data[2] * 255;
			break;
		}
		case SET_NORMAL_MODE_SPEED:
		{
			configuration.normalModeSpeed = data[1] + data[2] * 255;
			break;
		}
		case SET_LOST_TRACK_SPEED:
		{
			configuration.lostTrackSpeed = data[1] + data[2] * 255;
			break;
		}
		case SET_TRACK_RECORDING_SPEED:
		{
			configuration.trackRecordingSpeed = data[1] + data[2] * 255;
			break;
		}
		case SET_MOTOR_PID_KP:
		{
			PID_PARAMS_T *motor_pid_ptr;
			motor_pid_ptr = getLeftMotorPidPtr();
			motor_pid_ptr->kP = data[1] / 10.0;
			motor_pid_ptr = getRightMotorPidPtr();
			motor_pid_ptr->kP = data[1] / 10.0;
			break;
		}
		case SET_MOTOR_PID_KI:
		{
			PID_PARAMS_T *motor_pid_ptr;
			motor_pid_ptr = getLeftMotorPidPtr();
			motor_pid_ptr->kI = data[1] / 100.0;
			motor_pid_ptr = getRightMotorPidPtr();
			motor_pid_ptr->kI = data[1] / 100.0;
			break;
		}
		case SET_MOTOR_PID_KD:
		{
			PID_PARAMS_T *motor_pid_ptr;
			motor_pid_ptr = getLeftMotorPidPtr();
			motor_pid_ptr->kD = data[1] / 10.0;
			motor_pid_ptr = getRightMotorPidPtr();
			motor_pid_ptr->kD = data[1] / 10.0;
			break;
		}
		case SET_MOTOR_PID_MAX_INT_VALUE:
		{
			PID_PARAMS_T *motor_pid_ptr;
			motor_pid_ptr = getLeftMotorPidPtr();
			motor_pid_ptr->integral_saturation = data[1] + data[2] * 255;
			motor_pid_ptr = getRightMotorPidPtr();
			motor_pid_ptr->integral_saturation = data[1] + data[2] * 255;
			break;
		}
		case SET_SENSOR_WEIGHTS:
		{
			int i = 0;
			for(i = 0; i < 4; i ++)
			{
				configuration.weights[i] = - data[i + 1] / 10;
			}
			for(i = 4; i < 8; i ++)
			{
				configuration.weights[i] =  data[i + 1] / 10;
			}
			break;
		}
		case SET_SENSOR_THRESHOLDS:
		{
			int i = 0;
			for(i = 0; i < 8; i ++)
			{
				configuration.thresholds[i] = data[i + 1];
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void set_initial_config()
{
	configuration.mainPIDkP = 1.5;//3.5;
	configuration.mainPIDkI = 0;
	configuration.mainPIDkD = 3.0;//6.0;
	configuration.mainPIDIntSaturation = 0;

	configuration.normalModeSpeed = 25;
	configuration.lostTrackSpeed = 50;
	configuration.trackRecordingSpeed = 50;

	configuration.motorPIDkP = 3.0;
	configuration.motorPIDkI = 0.2;
	configuration.motorPIDkD = 5.0;
	configuration.motorPIDIntSaturation = 1000;

	int8_t i = 0;

	for(i = 0; i < 8; i ++)
	{
		configuration.thresholds[i] = 170;
	}

	configuration.weights[0] = -16;
	configuration.weights[1] = -9;
	configuration.weights[2] = -4;
	configuration.weights[3] = -2;
	configuration.weights[4] = 2;
	configuration.weights[5] = 4;
	configuration.weights[6] = 9;
	configuration.weights[7] = 16;

}
