
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


#include "schedule.h"





//
// main - The simulator's main routine
//
int main(int argc, char **argv){
    int processes[10];
    init();
    int i;
    for(i=0;i<10;i++){
        processes[i]=100;
        printf("Scheduled Process: %d\n", i);
        PCB* proc = (PCB *) malloc(sizeof(PCB));
        proc->pid = i;
        proc->priority=0;
        addProcess(proc);
    }

    PCB* process = NULL;
    int time = 0;
    while(hasProcess()){
        process = nextProcess(&time);
        if(!process){
            printf("NULL Process, something went wrong in your code.\n");
            exit(1);
        }
        for(;time>0;time--){
            printf("Process %d executed\n", process->pid);
            processes[process->pid]--;
            printf("Process value %d\n", processes[process->pid]);
            if(processes[process->pid]<0){
                printf("Process %d Finished\n", process->pid);
                break;
            }
        }
        if(processes[process->pid]>=0){
            printf("pid %d\n",process->pid);
            addProcess(process);
        } else {
            free(process);
        }
    }


    exit(0); //control never reaches here
}
