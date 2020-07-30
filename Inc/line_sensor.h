/*
 * line_sensor.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef LINE_SENSOR_H_
#define LINE_SENSOR_H_

#include "stm32f4xx_hal.h"


typedef struct LINE_SENSOR {
	float measured_error;
	uint8_t line_lost;
	int8_t *weights;
	uint16_t sensors[8];
	uint8_t *thresholds;

	ADC_HandleTypeDef *adc_handle;

} LINE_SENSOR_T;


void init_line_sensor(ADC_HandleTypeDef *adc_handle, uint8_t thresholds[8], int8_t weights[8]);
void compute_error();
LINE_SENSOR_T *getLineSensorPtr();


#endif /* LINE_SENSOR_H_ */
