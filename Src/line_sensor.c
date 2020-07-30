/*
 * line_sensor.c
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#include "line_sensor.h"
#include "stm32f4xx_hal.h"


volatile static LINE_SENSOR_T line_sensor;

void init_line_sensor(ADC_HandleTypeDef *adc_handle, uint8_t thresholds[8], int8_t weights[8])//ADC_HandleTypeDef
{
	uint8_t i;
	line_sensor.adc_handle = adc_handle;
	HAL_ADC_Start_DMA(line_sensor.adc_handle, (uint32_t*) line_sensor.sensors, 8);
	line_sensor.measured_error = 0;
	line_sensor.line_lost = 0;
	line_sensor.thresholds = thresholds;
	line_sensor.weights = weights;

}


void compute_error()
{
	float error_tmp = 0;
	int8_t i, counter = 0;

	for(i = 0; i < 8; i++)
	{
		if(line_sensor.sensors[i] > line_sensor.thresholds[i])
		{
			error_tmp += line_sensor.weights[i];
			counter += 1;
		}
	}


	if(counter)
	{
		line_sensor.line_lost = 0;
		line_sensor.measured_error = error_tmp / ((float) counter);
	}
	else
	{
		line_sensor.line_lost = 1;

		if(line_sensor.measured_error < -0.01)
		{
			line_sensor.measured_error = line_sensor.weights[0];
		}
		else if(line_sensor.measured_error > 0.01)
		{
			line_sensor.measured_error = line_sensor.weights[7];
		}
		else
		{
			//do nothing
		}
	}
}

LINE_SENSOR_T *getLineSensorPtr()
{
	return &line_sensor;
}
