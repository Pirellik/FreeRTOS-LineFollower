/*
 * pid.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#include "pid.h"


static PID_PARAMS_T main_pid;
static PID_PARAMS_T left_motor_pid, right_motor_pid;


void set_pid_params(PID_PARAMS_T *pid_params_ptr, float kP, float kI, float kD, float integral_saturation)
{
	pid_params_ptr->kP = kP;
	pid_params_ptr->kI = kI;
	pid_params_ptr->kD = kD;

	pid_params_ptr->error = 0;
	pid_params_ptr->integrated_error = 0;
	pid_params_ptr->diff_error = 0;

	pid_params_ptr->integral_saturation = integral_saturation;
}

void update_pid_error(PID_PARAMS_T *pid_params_ptr, float error)
{
	pid_params_ptr->diff_error = error - pid_params_ptr->error;
	pid_params_ptr->error = error;
	pid_params_ptr->integrated_error += error;
	if(pid_params_ptr->integrated_error > pid_params_ptr->integral_saturation)
	{
		pid_params_ptr->integrated_error = pid_params_ptr->integral_saturation;
	}
	else if(pid_params_ptr->integrated_error < - pid_params_ptr->integral_saturation)
	{
		pid_params_ptr->integrated_error = - pid_params_ptr->integral_saturation;
	}
}

void update_pid_set_point(PID_PARAMS_T *pid_params_ptr, float set_point)
{
	pid_params_ptr->set_point = set_point;
}

float get_pid_control(PID_PARAMS_T *pid_params_ptr)
{
	float control;
	control = pid_params_ptr->kP * pid_params_ptr->error +
			  pid_params_ptr->kI * pid_params_ptr->integrated_error +
			  pid_params_ptr->kD * pid_params_ptr->diff_error;

	return control;
}

PID_PARAMS_T * getMainPidPtr()
{
	return &main_pid;
}
PID_PARAMS_T *getLeftMotorPidPtr()
{
	return &left_motor_pid;
}
PID_PARAMS_T *getRightMotorPidPtr()
{
	return &right_motor_pid;
}

