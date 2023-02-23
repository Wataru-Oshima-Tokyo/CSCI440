#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Function to initialize any global variables for the scheduler.
 */
PCB* processes[10];
int pid = 0;
void init(){
	PCB* proc = (PCB *) malloc(sizeof(PCB));
	for (int i=0; i< 10; i++){// initialize the proccesses
		processes[i] = proc;
	}
}

/**
 * Function to add a process to the scheduler
 * @Param process - Pointer to the process control block for the process that
 * 			needs to be scheduled. PCB is defined in the header.
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB* process){
	processes[process->pid] = process;
	return 0;
}

/**
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for
 * @Return returns pointer to process control block that needs to be executed
 * 		returns NULL if there is no process to be scheduled.
 */
PCB* nextProcess(int *time){
	*time =4;
	return processes[pid-1];
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
	if (processes[pid] != NULL){
		pid++;
		//need to figure out here 
		if (pid == 11)
			pid = 1;
		printf("pid: %d\n", pid);
		return 1;
	}else{
		return 0;
	}
	return 0;
}
