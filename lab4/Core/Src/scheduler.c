/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Hoang
 */
#include "scheduler.h"


sTasks SCH_tasks_G[SCH_MAX_TASKS]; // Array stores tasks
uint8_t current_index_task = 0; // Index of array

void SCH_Init(void){
	current_index_task = 0;
}
void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	// Add tasks into scheduler
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++; // increase current index
	}
}
void SCH_Delete_Task(uint32_t TaskID){
	// Delete tasks with given ID
	if (TaskID == current_index_task-1){ // Task is at the end of array
		current_index_task--; // decrease current index
		return;
	}
	for(int i = TaskID; i < current_index_task - 1; i++){ // shift left array
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period =  SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
	}
	current_index_task--; // decrease current index
}
void SCH_Update(void){
	//Update Delay of task
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}
		else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period; // Assign Period
			SCH_tasks_G[i].RunMe += 1; // Increase RunMe
		}
	}
}
void SCH_Dispatch_Tasks(void){
	// Execute functon of Task when RunMe = 1
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].RunMe > 0){
		    SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
	}
}
