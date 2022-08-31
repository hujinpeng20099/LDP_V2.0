#ifndef __TASK_H
#define __TASK_H

#include "main.h"

#define DISPLAY_MODE	1

#define THREAD_PRIORITY         5
#define THREAD_STACK_SIZE       256
#define THREAD_TIMESLICE        1000



/*Data of spinbox*/
typedef struct {
    /*New data for this type */
	int16_t value;
	uint16_t range_max;
	uint8_t digit_count;
	uint8_t digit_pos;
	uint8_t dec_point;
	uint8_t index;
} Spinbox_TypeDef;


void LDP_Thread_Creat(void);

#endif



