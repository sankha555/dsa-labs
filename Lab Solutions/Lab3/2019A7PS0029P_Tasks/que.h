#include <stdio.h>
#include <stdbool.h>

/* structure to represent each node of the queue  */
struct node{
    int element;
    struct node* next;
};

/* structure to represent the queue  */
struct Queue{
    struct node* front;     // front node of the queue
    struct node* rear;      // rear node of the queue
    int size;               // size of the queue
};

// creates and returns a new queue
extern struct Queue* newQ();

// checks if the queue is empty
extern bool isEmpty(struct Queue* q);

// deletes the front node from the queue
extern struct Queue* delQ(struct Queue* q);

// returns the element in the front node of the queue
extern int front(struct Queue* q);

// adds a new node to the queue
extern struct Queue* addQ(struct Queue* q, int elem);

// returns the length of the queue
extern int length(struct Queue* q);
