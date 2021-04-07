/* Name: Sankha Das*/
/* ID No.: 2019A7PS0029P */

#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"
#include "linkedList.h"

int decideHeadsOrTails(){
    int randNum = rand()%100;
    if(randNum < 50)
        return 0;   // HEADS : does not make linked list cyclic
    else
        return 1;   // TAILS : makes linked list cyclic
}

LinkedList* createList(int N){

    // initiate linked list
    LinkedList* ls = (LinkedList*) myalloc(sizeof(LinkedList));
    ls->head = NULL;
    ls->size = 0;

    Node* node;
    // add N nodes to the linked list
    for(int i = 0; i < N; i++){
        node = (Node*) myalloc(sizeof(node));
        if(node==NULL)
            break;

        // select value for node randomly
        node->element = rand()%100000+1;
        node->next = NULL;

        if(ls->head == NULL){
            ls->head = node;
            ls->tail = node;
            ls->size = 1;
        }else{
            ls->tail->next = node;
            ls->tail = node;
            ls->size += 1;
        }
    }

    FILE* fout = fopen("heapSpace.txt","a");
    fprintf(fout, "HEAP SPACE = %d\n", heapSpace);

    return ls;
}

LinkedList* createCycle(LinkedList* ls){

    int isCycle = decideHeadsOrTails(); // coin-tossing step

    if(isCycle){

        // create cycle
        int r = rand()%(ls->size);      // randomly select the node from the head to which
                                        // tail of the list has to be linked to make the cycle
        Node* curr = ls->head;
        while(r--)
            curr = curr->next;
        
        // link tail of linked list to the rth node from the head
        ls->tail->next = curr;
    } 

    return ls;
}


