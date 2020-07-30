#ifndef TASK_TRACK_RECORDING_H_
#define TASK_TRACK_RECORDING_H_

#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

void initTaskTrackRecording();
eTaskState getTrackRecordingTaskState();
void suspendTaskTrackRecording();
void resumeTaskTrackRecording();
void resetTaskDataTrackRecording();
uint16_t *getLeftRecordedTrackPtr();
uint16_t *getRightRecordedTrackPtr();

#endif /* TASK_NORMAL_RUN_H_ */
