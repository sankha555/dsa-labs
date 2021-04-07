#include <stdio.h>
#include <stdbool.h>

/* structure to represent the multi-queue */
struct MultiQ{
    int num;
    struct Queue** queues;
};

/* structure to represent a Task entity */
struct Task{
    int tid;    // task ID
    int p;      // priority of the task
};

// creates and returns a new multi-queue with an array of "num" empty queues
extern struct MultiQ* createMQ(int num);

// adds a new task to the queue which has the priority number of the task
extern struct MultiQ* addMQ(struct MultiQ* mq, struct Task t);

// returns the task ID of the next task to be executed from the multi-queue
extern struct Task nextMQ(struct MultiQ* mq);

// removes (or executes) the next task to be executed from the multi-queue
extern struct MultiQ* delNext(struct MultiQ* mq);

// checks and returns if each of the queues (i.e. the entire multi-queue) is empty
extern bool isEmptyMQ(struct MultiQ* mq);

// returns the size of the multi-queue 
extern int sizeMQ(struct MultiQ* mq);

// returns the size of the queue storing tasks with priority p
extern int sizeMQbyPriority(struct MultiQ* mq, int p);

// returns the queue storing tasks with priority p
extern struct Queue* getQueueFromMQ(struct MultiQ* mq, int p);
