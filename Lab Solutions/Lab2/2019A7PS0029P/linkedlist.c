#include "linkedlist.h"

void insertFirst(struct linkedList* head, int ele){

    //create a node
    struct node* link = (struct node*) malloc (sizeof(struct node));
    /* by this you are creating a node whose address is being stored in the link pointer. */
    link->element = ele;

    if(head->first==NULL){
        head->first = link;
        link->next = NULL;
    }else{
        //point it to old first node
        link->next = head->first;
        //point first to new first node
        head->first = link;
    }
    head->count += 1;
}

struct node* deleteFirst(struct linkedList* head){

    if(head->first==NULL){
        printf("The linked list is empty! Cannot delete any elements...\n");
        return NULL;
    }

    struct node* temp = head->first;     // temporary variable to store current first node
    head->first = temp->next;            // linking head to next node of current first node (unlinking from current first node)
    temp->next = NULL;                   // unlinking temp completely from the list
    head->count -= 1;                    // decrementing the count
    
    return temp;
}

void printList(struct linkedList * head){
    struct node *ptr = head->first;
    printf("\n[ ");

    //start from the beginning
    while(ptr != NULL){
        printf("%d, ", ptr->element);
        ptr = ptr->next;
    }

    printf(" ]\n");
}