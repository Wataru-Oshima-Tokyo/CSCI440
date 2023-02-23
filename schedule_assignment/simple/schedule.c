#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Function to initialize any global variables for the scheduler.
 */
PCB* processes[10];
int i =0;
void init(){
	PCB* proc = (PCB *) malloc(sizeof(PCB));
	for (int i=0; i< 10; i++){// initialize the proccesses
		processes[i] = proc;
	}
}

/**
 * Function to add a process to the scheduler
 * @Param PCB * - pointer to the PCB for the process/thread to be added to the
 *      scheduler queue
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB *process){
	processes[process->pid] = process;
    return 0;
}

/**
 * Function to get the next process from the scheduler
 *
 * @Return returns the Process Control Block of the next process that should be
 *      executed, returns NULL if there are no processes
 */
PCB* nextProcess(){
	return processes[i-1];
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
	if (processes[i] != NULL){
		i++;
		return 1;
	}else{
		return 0;
	}
}
