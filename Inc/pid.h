/*
 * pid.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef PID_H_
#define PID_H_

typedef struct PID_PARAMS{
	float kP;
	float kI;
	float kD;

	float error;
	float diff_error;
	float integrated_error;

	float integral_saturation;

	float set_point;
} PID_PARAMS_T;

void set_pid_params(PID_PARAMS_T *pid_params_ptr, float kP, float kI, float kD, float integral_saturation);
void update_pid_error(PID_PARAMS_T *pid_params_ptr, float error);
void update_pid_set_point(PID_PARAMS_T *pid_params_ptr, float set_point);
float get_pid_control(PID_PARAMS_T *pid_params_ptr);
PID_PARAMS_T *getMainPidPtr();
PID_PARAMS_T *getLeftMotorPidPtr();
PID_PARAMS_T *getRightMotorPidPtr();

#endif /* PID_H_ */
