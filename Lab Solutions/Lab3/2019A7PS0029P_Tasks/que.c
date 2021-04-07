#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "que.h"

struct Queue* newQ(){
    
    // creation of a new Queue entity and a allocating it to a pointer
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
    
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}

struct Queue* addQ(struct Queue* q, int elem){

    // creation of a new node of the queue and a allocating it to a pointer
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    
    // adding the new node to the end of the queue
    if(newNode != NULL){
        newNode->element = elem;
        newNode->next = NULL;

        if(q->front == NULL){
            q->front = newNode;
            q->rear = newNode;
        }else{
            q->rear->next = newNode;
            q->rear = newNode;
        }

        q->size += 1;

    }else{
        printf("No space in memory to insert new node...\n");
    }

    return q;
}

struct Queue* delQ(struct Queue* q){

    if(isEmpty(q)){
        printf("Queue is empty. No elements can be deleted...\n");
    }else{
        int temp = q->front->element;
        q->front = q->front->next;
        q->size -= 1;

        if(isEmpty(q))
            q->rear = NULL;
        
        printf("%d was removed from queue...\n", temp);
    }

    return q;
}

int front(struct Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty...\n");
        return -1;
    }else{
        return q->front->element;
    }
}

int length(struct Queue* q){
    if(q->front == NULL)
        return 0;
    else{
        struct node* temp = q->front;
        int count = 1;
        while(temp != q->rear){
            temp = temp->next;
            count++;
        }

        return count;
    }
}

bool isEmpty(struct Queue* q){
    if(length(q) == 0)
        return true;
    else
        return false;
}
