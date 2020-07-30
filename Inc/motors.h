/*
 * motors.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#include "stm32f4xx_hal.h"


typedef struct MOTOR{
	int16_t pwm;

	__IO uint32_t *pwm_ptr;

	GPIO_TypeDef *IN1_port_ptr;
	GPIO_TypeDef *IN2_port_ptr;
	uint16_t IN1_pin;
	uint16_t IN2_pin;
} MOTOR_T;

void set_PWM(MOTOR_T *motor_ptr, int16_t signed_duty_cycle);
void init_PWM();
void stop_PWM();
void init_motor(MOTOR_T *motor_ptr, __IO uint32_t *pwm_ptr, GPIO_TypeDef *IN1_port_ptr, GPIO_TypeDef *IN2_port_ptr, uint16_t IN1_pin, uint16_t IN2_pin);
MOTOR_T *getLeftMotorPtr();
MOTOR_T *getRightMotorPtr();



#endif /* MOTORS_H_ */
