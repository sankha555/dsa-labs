/* Name: Sankha Das */
/* ID No.: 2019A7PS0029P */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"

bool testCyclic(LinkedList* ls){
    
    /* Hare and Tortoise Algorithm */
    Node* slow = ls->head;                  // slow pointer
    Node* fast = ls->head;                  // fast pointer (moves at 2x speed)

    while(fast != NULL || slow != NULL){
        if(slow == fast)                    // slow and fast pointer have met after some cycle(s)
            return true;                    // this means there indeed was a cycle in the list

        slow = slow->next;                  
        fast = fast->next->next;            // double-step jump of the fast pointer
    }

    return false;                           // either the fast or slow pointer has become null
                                            // this means there is no cycle in the list
}
