/*
 * motor_controller.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef TASK_MOTOR_CONTROLLER_H_
#define TASK_MOTOR_CONTROLLER_H_

#include "pid.h"
#include "motors.h"
#include "encoders.h"

typedef struct MOTOR_CONTROLLER {
	float angular_speed_setpoint;

	PID_PARAMS_T *motor_pid_ptr;
	MOTOR_T *motor_ptr;
	ENCODER_T *motor_enc_ptr;

} MOTOR_CONTROLLER_T;


MOTOR_CONTROLLER_T *getLeftMotorControllerPtr();
MOTOR_CONTROLLER_T *getRightMotorControllerPtr();

void initTaskMotorController();
void newLeftMotorSpeed(float angular_speed);
void newRightMotorSpeed(float angular_speed);

#endif /* TASK_MOTOR_CONTROLLER_H_ */
