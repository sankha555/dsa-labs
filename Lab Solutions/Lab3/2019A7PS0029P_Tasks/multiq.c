#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "que.h"
#include "multiq.h"

struct MultiQ* createMQ(int num){

    // creation of a new Multi-Queue entity and a allocating it to a pointer
    struct MultiQ* mq = (struct MultiQ*) malloc(sizeof(struct MultiQ));

    mq->num = num;
    mq->queues = (struct Queue**) calloc(num, sizeof(struct Queue*));

    for(int i = 0; i < num; i++){
        (mq->queues)[i] = newQ();
    }
    return mq;
}

struct MultiQ* addMQ(struct MultiQ* mq, struct Task t){
    
    // extracting information about the task from the task entity
    int priority = t.p;
    int task_id = t.tid;

    // adding the task to the queue storing the tasks with priority "priority"
    (mq->queues)[priority-1] = addQ((mq->queues)[priority-1], task_id); 

    return mq;
}

struct Task nextMQ(struct MultiQ* mq){

    struct Task nextTask; 
    if(isEmptyMQ(mq)){
        printf("All queues are empty...\n");
    }else{
        // getting the first non-empty queue in decreasing order of priority
        for(int i = (mq->num)-1; i >= 0; i--){
            if(!isEmpty((mq->queues)[i])){
                nextTask.tid = front((mq->queues)[i]);
                nextTask.p = i+1;
                return nextTask;
            }
        }
    }

    // Return a task with null values
    nextTask.tid = -1;
    nextTask.p = -1;
    return nextTask;
}

struct MultiQ* delNext(struct MultiQ* mq){

    if(isEmptyMQ(mq)){
        printf("All queues are empty, nothing to delete...\n");
    }else{
        // getting the first non-empty queue in decreasing order of priority
        for(int i = (mq->num)-1; i >= 0; i--){
            if(!isEmpty((mq->queues)[i])){
                (mq->queues)[i] = delQ((mq->queues)[i]);
                break;
            }
        }
    }
   
    return mq;
}

bool isEmptyMQ(struct MultiQ* mq){

    for(int i = 0; i < mq->num; i++){
        // if any queue is non-empty, the multi-queue is still non-empty
        if(!isEmpty((mq->queues)[i]))
            return false;
    }

    // all queues are empty
    return true;
}

int sizeMQ(struct MultiQ* mq){

    int size = 0;
    if(!isEmptyMQ(mq)){
        // summing the sizes of each of the queues in the multi-queue
        for(int i = 0; i < mq->num; i++){
            size += length((mq->queues)[i]);
        }
    }

    return size;
}

int sizeMQbyPriority(struct MultiQ* mq, int p){
    
    return length((mq->queues)[p-1]);

}

struct Queue* getQueueFromMQ(struct MultiQ* mq, int p){

    return (mq->queues)[p-1];

}
