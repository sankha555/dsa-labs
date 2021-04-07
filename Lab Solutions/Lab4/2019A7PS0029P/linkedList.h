#include <stdio.h>
#include <stdlib.h>

/* a structure to define a linked list node */
typedef struct node{
    int element;
    struct node* next;
} Node;

/* a structure to define the linked list */
typedef struct linkedList{
    Node* head;
    Node* tail; 
    long size;
} LinkedList;

/* function to create a linear linked list with N nodes */
extern LinkedList* createList(int N);

/* function to convert a linear linked list to a cycle based on internal computations */
extern LinkedList* createCycle(LinkedList* ls);
