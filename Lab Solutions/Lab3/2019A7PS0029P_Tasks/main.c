#include <stdio.h>
#include "multiq.h"

FILE * fin;

int main(int argc, char *argv[]){
    
    fin = fopen(argv[1], "r");
    
    int num = 100;
    struct MultiQ* mq = createMQ(num);
    
    int tid, p;
    struct Task newTask;
    while(!feof(fin)){
        fscanf(fin, "%d,%d", &tid, &p);
        
        newTask.tid = tid;
        newTask.p = p;

        mq = addMQ(mq, newTask);
    }

    for(int i = 0; i < 5; i++){
        printf("Next task to be executed is Task ID %d\n", nextMQ(mq).tid);
        delNext(mq);
        printf("Size of multi queue = %d\n", sizeMQ(mq));
    }

    printf("Queue from front is %d", front(getQueueFromMQ(mq, 3)));
    printf("Size of queue 3 is %d", sizeMQbyPriority(mq, 3));
    
    return 0;
}
