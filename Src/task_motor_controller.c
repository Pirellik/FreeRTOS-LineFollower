/*
 * motor_controller.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#include "cmsis_os.h"
#include "task_motor_controller.h"
#include "encoders.h"
#include "pid.h"
#include "motors.h"
#include "main.h"
#include "config.h"

static TaskHandle_t motorControllerTaskHandle = NULL;

static MOTOR_CONTROLLER_T left_motor_controller, right_motor_controller;
static CONFIG_T *config;

static int16_t angularSpeedToPWM(float angular_speed);
static void taskMotorController(void *p);


MOTOR_CONTROLLER_T *getLeftMotorControllerPtr()
{
	return &left_motor_controller;
}
MOTOR_CONTROLLER_T *getRightMotorControllerPtr()
{
	return &right_motor_controller;
}

void initTaskMotorController()
{
	if(motorControllerTaskHandle == NULL)
	{
		config = getConfigPtr();

		init_PWM();

		init_motor(getRightMotorPtr(), &(TIM3->CCR1), BIN_1_GPIO_Port, BIN_2_GPIO_Port, BIN_1_Pin, BIN_2_Pin);
		init_motor(getLeftMotorPtr(), &(TIM3->CCR2), AIN_1_GPIO_Port, AIN_2_GPIO_Port, AIN_1_Pin, AIN_2_Pin);

		set_pid_params(getRightMotorPidPtr(), config->motorPIDkP, config->motorPIDkI, config->motorPIDkD, config->motorPIDIntSaturation);
		set_pid_params(getLeftMotorPidPtr(), config->motorPIDkP, config->motorPIDkI, config->motorPIDkD, config->motorPIDIntSaturation);
		update_pid_set_point(getRightMotorPidPtr(), 0);
		update_pid_set_point(getLeftMotorPidPtr(), 0);

		left_motor_controller.motor_ptr = getLeftMotorPtr();
		left_motor_controller.motor_pid_ptr = getLeftMotorPidPtr();
		left_motor_controller.motor_enc_ptr = getLeftEncoderPtr();

		left_motor_controller.angular_speed_setpoint = 0;

		right_motor_controller.motor_ptr = getRightMotorPtr();
		right_motor_controller.motor_pid_ptr = getRightMotorPidPtr();
		right_motor_controller.motor_enc_ptr = getRightEncoderPtr();

		right_motor_controller.angular_speed_setpoint = 0;

		xTaskCreate(taskMotorController,
					(const char *const)"MotorControllerTask",
					configMINIMAL_STACK_SIZE,
					0,
					configMAX_PRIORITIES-1,
					&motorControllerTaskHandle);

	}
}

static void taskMotorController(void *p)
{
	while(1)
	{
		float control, speed_error;

		speed_error = left_motor_controller.angular_speed_setpoint - left_motor_controller.motor_enc_ptr->angular_speed;

		update_pid_error(left_motor_controller.motor_pid_ptr, speed_error);
		control = get_pid_control(left_motor_controller.motor_pid_ptr);
		set_PWM(left_motor_controller.motor_ptr, (angularSpeedToPWM(left_motor_controller.angular_speed_setpoint) + (int16_t) control));

		speed_error = right_motor_controller.angular_speed_setpoint - right_motor_controller.motor_enc_ptr->angular_speed;

		update_pid_error(right_motor_controller.motor_pid_ptr, speed_error);
		control = get_pid_control(right_motor_controller.motor_pid_ptr);
		set_PWM(right_motor_controller.motor_ptr, (angularSpeedToPWM(right_motor_controller.angular_speed_setpoint) + (int16_t) control));

		osDelay(1);
	}
}


void newLeftMotorSpeed(float angular_speed)
{
	left_motor_controller.angular_speed_setpoint = angular_speed;
}

void newRightMotorSpeed(float angular_speed)
{
	right_motor_controller.angular_speed_setpoint = angular_speed;
}

static int16_t angularSpeedToPWM(float angular_speed)
{
	int16_t pwm = 0;
	if(angular_speed > 1)
	{
		pwm = (int16_t) 2.31 * angular_speed + 75;
	}
	else if(angular_speed < -1)
	{
		pwm = (int16_t) 2.31 * angular_speed - 75;
	}
	else
	{
		pwm = 0;
	}
	return pwm;
}

