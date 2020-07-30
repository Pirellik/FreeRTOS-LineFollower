/*
 * motors.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */


#include "motors.h"
#include "tim.h"
#include "main.h"


static MOTOR_T motor_R, motor_L;

void init_motor(MOTOR_T *motor_ptr, __IO uint32_t *pwm_ptr, GPIO_TypeDef *IN1_port_ptr, GPIO_TypeDef *IN2_port_ptr, uint16_t IN1_pin, uint16_t IN2_pin)
{
	motor_ptr->pwm = 0;
	*(motor_ptr->pwm_ptr) = 0;
	motor_ptr->pwm_ptr = pwm_ptr;
	motor_ptr->IN1_port_ptr = IN1_port_ptr;
	motor_ptr->IN2_port_ptr = IN2_port_ptr;
	motor_ptr->IN1_pin = IN1_pin;
	motor_ptr->IN2_pin = IN2_pin;
}

void init_PWM()
{
	// konfiguracja PWM
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}
void stop_PWM()
{
	// konfiguracja PWM
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
}

void set_PWM(MOTOR_T *motor_ptr, int16_t pwm)
{
		pwm = (pwm > 999) ? 999 : pwm;
		pwm = (pwm < -999) ? -999 : pwm;
		motor_ptr->pwm = pwm;
		*(motor_ptr->pwm_ptr) = abs(pwm);

		if(pwm > 0)
		{
			HAL_GPIO_WritePin(motor_ptr->IN1_port_ptr, motor_ptr->IN1_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(motor_ptr->IN2_port_ptr, motor_ptr->IN2_pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(motor_ptr->IN1_port_ptr, motor_ptr->IN1_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(motor_ptr->IN2_port_ptr, motor_ptr->IN2_pin, GPIO_PIN_SET);
		}
}

MOTOR_T *getLeftMotorPtr()
{
	return &motor_L;
}
MOTOR_T *getRightMotorPtr()
{
	return &motor_R;
}
