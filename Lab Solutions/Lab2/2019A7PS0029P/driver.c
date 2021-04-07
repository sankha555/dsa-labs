#include <stdio.h>
#include "linkedlist.h"
#include "stack.h"

int main(int argc, char *argv[]){

    // Create a file pointer and open the file read as command line argument.
    FILE * fileptr = fopen(argv[1], "r");

    // Declare a pointer to a linked list (head) and allocate memory to it.
    struct linkedList* head = (struct linkedList*) malloc (sizeof(struct linkedList));
    head->first = NULL;
    head->count = 0;

    // In a loop read the file and insert elements into the stack.
    while (!feof(fileptr)){
        // read the next element and store into the temp variable.
        int temp;
        fscanf(fileptr, "%d ", &temp);

        // insert temp into the stack.
        push(head,temp);
    }
    // close the file pointer
    fclose(fileptr);


    // Full stack is printed
    printf("\nThe stack is:");
    printList(head);

    // Writing stack to new file 
    fileptr = fopen("output.txt", "w+");
    if (fileptr == NULL) { 
        printf("Could not open file\n"); 
        return 0; 
    } 

    struct node* temp = head->first;

    fprintf(fileptr, "[ ");
    while(temp!=NULL){
        fprintf(fileptr, "%d, ", temp->element);
        temp = temp->next;
    }
    fprintf(fileptr, "]\n");

    fclose(fileptr);
    // File stream closed

    // Popping elements one-by-one from stack
    printf("\nResult of popping elements one by one from stack: \n");
    while(head->first!=NULL)
        printf("%d\n", pop(head)->element);
    
    printf("\nThe stack now is:");
    printList(head);
    printf("\n");

    return 0;
}