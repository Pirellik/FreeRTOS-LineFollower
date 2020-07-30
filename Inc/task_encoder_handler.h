/*
 * task_encoder_handler.h
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#ifndef TASK_ENCODER_HANDLER_H_
#define TASK_ENCODER_HANDLER_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

void initTaskEncoderHandler();
eTaskState getEncoderHandlerTaskState();
void suspendTaskEncoderHandler();
void resumeTaskEncoderHandler();

#endif /* TASK_ENCODER_HANDLER_H_ */
