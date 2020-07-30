/*
 * communication.c
 *
 *  Created on: 13.04.2019
 *      Author: kamil
 */

#include "communication.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "cmsis_os.h"
#include "task_manager.h"
#include "state_machine.h"
#include "config.h"
#include "task_track_recording.h"

volatile static uint8_t data[50];

volatile static uint8_t received[9];
SemaphoreHandle_t SemaphoreUartHandling = NULL;

static void handleIncomingRequestsTask(void *pvParameters)
{
	while(1)
	{
		if( xSemaphoreTake( SemaphoreUartHandling, portMAX_DELAY ) == pdTRUE )
		{
			ENUM_PROGRAM_STATE_T current_state = getCurrentState();

			if(received[0] < 4)//if command is a state level request
			{
				updateStateMachine(received[0]);
				current_state = getCurrentState();
				updateRunningTasks(current_state);
				int size;
				size = sprintf(data, "%c", current_state);
				HAL_UART_Transmit(&huart2, data, size, 1000);
			}
			else if(current_state == STATE_IDLE  && received[0] < 20)
			{
				param_configuration(received);
			}
			else if(current_state == STATE_IDLE)
			{
				int i = 0;
				uint16_t *recorded_track_left = getLeftRecordedTrackPtr();
				uint16_t *recorded_track_right = getRightRecordedTrackPtr();

				for(i = 0; i < 2*8192; i += 256)
				{
					HAL_UART_Transmit(&huart2, ((uint8_t *)recorded_track_left) + i, 256, 1000);
					HAL_UART_Transmit(&huart2, ((uint8_t *)recorded_track_right) + i, 256, 1000);
				}

			}

			HAL_UART_Receive_IT(&huart2, received, 9);
		}
		else
		{
		}
	}
	vTaskDelete(NULL);
}

void initIncomingRequestsHandler()
{
	  // Creating semaphores
	  SemaphoreUartHandling = xSemaphoreCreateBinary();
	  if( SemaphoreUartHandling == NULL ) while(1);

	  xTaskCreate(handleIncomingRequestsTask,
	  	    		  (const char *const)"RequestsHandler",
	  	    		  configMINIMAL_STACK_SIZE,
	  	    		  0,
	  	    		  1,
	  	    		  0);

	  HAL_UART_Receive_IT(&huart2, received, 9);
}


void handleUart()
{
	BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	xSemaphoreGiveFromISR( SemaphoreUartHandling, &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
