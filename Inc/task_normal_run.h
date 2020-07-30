/*
 * task_encoder_handler.h
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#ifndef TASK_NORMAL_RUN_H_
#define TASK_NORMAL_RUN_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

void initTaskNormalRun();
eTaskState getNormalRunTaskState();
void suspendTaskNormalRun();
void resumeTaskNormalRun();
void resetTaskDataNormalRun();

#endif /* TASK_NORMAL_RUN_H_ */
