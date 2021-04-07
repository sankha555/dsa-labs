/* Name: Sankha Das*/
/* ID No.: 2019A7PS0029P */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "alloc.h"
#include "cycle1.h"

int main(){

    /**********************************************************************************/
    /*  To run the program, please run the following commands in the command prompt:  */
    /*  1. gcc -c alloc.c cycle1.c linkedList.c main.c                                */
    /*  2. gcc -o exe alloc.o cycle1.o linkedList.o main.o                            */
    /*  3. ./exe                                                                      */
    /**********************************************************************************/

    /* Q4 Implementation */
    struct timeval t1, t2;
    double elapsedTime;
    heapSpace = 0;
    
    // start the timer
    gettimeofday(&t1, NULL);

    int N;

    // seed the random number generator with the current time
    srand(t1.tv_sec);
    N = ((double)(rand()%10000000)) + 1;    // generate a large random number for size of list

    LinkedList* ls = createList(N);         // create the list
    
    ls = createCycle(ls);

    // test if linked list was made cyclic
    if(testCyclic(ls))
        printf("Linked List is cyclic. N = %d\n", N);
    else    
        printf("Linked List is not cyclic. N = %d\n", N);

    // stop the timer
    gettimeofday(&t2, NULL);

    // calculate the time elapsed in program run
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("N = %d,TIME TAKEN = %f ms,HEAP SPACE = %d\n", N, elapsedTime, heapSpace);

    // free the memory after program run is over 
    Node* curr = ls->head;
    Node* temp;
    while(ls->head != NULL){
        ls->head = curr->next;
        myfree(curr, sizeof(*curr));
        curr = ls->head;
    }
    myfree(ls, sizeof(*ls));

    return 0;
}