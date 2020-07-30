/*
 * task_line_sensor_handler.h
 *
 *  Created on: 14.04.2019
 *      Author: kamil
 */

#ifndef TASK_LINE_SENSOR_HANDLER_H_
#define TASK_LINE_SENSOR_HANDLER_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"

void initTaskLineSensorHandler();
eTaskState getLineSensorHandlerTaskState();
void suspendTaskLineSensorHandler();
void resumeTaskLineSensorHandler();

#endif /* TASK_LINE_SENSOR_HANDLER_H_ */
