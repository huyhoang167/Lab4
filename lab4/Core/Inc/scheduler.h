/*
 * scheduler.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Hoang
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;
	uint32_t 	TaskID;
}sTasks;

#define SCH_MAX_TASKS 40 // Maximum tasks

void SCH_Init(void);

void SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD);

void SCH_Delete_Task(uint32_t TaskID);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);


#endif /* INC_SCHEDULER_H_ */
