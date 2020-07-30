/*
 * task_manager.h
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

void updateRunningTasks(uint8_t state);

#endif /* TASK_MANAGER_H_ */
