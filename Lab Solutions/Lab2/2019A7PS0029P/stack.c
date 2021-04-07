#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void push(struct linkedList* head, int ele){
    insertFirst(head, ele);
}

struct node* pop(struct linkedList* head){
    return deleteFirst(head);
}
