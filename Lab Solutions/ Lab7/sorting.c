/* Name: Sankha Das | ID: 2019A7PS0029P | Lab 7  */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include <string.h>

/* definition of stack */

int STACK_LIMIT = 1000;
int STACK[STACK_LIMIT] = {0};
int TOP = -1;

/* Temporary variables */
char tempName[11];
int tempID;

/* Helper methods for stack operations  */
void push(int elem) {
	if(TOP == STACK_LIMIT-1) {
		printf("Stack limit reached, cannot push more elements...\n");
	}else{
        STACK[++TOP] = elem;
    }
}


int pop() {
	if(TOP==-1) {
		printf("Stack is empty, cannot pop any elements...\n");
		return -1;
	}else{
        int temp = STACK[TOP];
        STACK[TOP--] = 0;
        return temp;
    }
}


/* Quicksort Part */
int partition(Employee* empArr, int l, int r) {
	int p = empArr[r].empID;
	int i = l - 1, j = l;

	while(j++ < r)
		if(empArr[j].empID <= p) {
			i++;
			// swapping the employee records at positions i and j
            strcpy(tempName, empArr[i].name);
            strcpy(empArr[i].name, empArr[j].name);
            strcpy(empArr[j].name, tempName);

            tempID = empArr[i].empID;
            empArr[i].empID = empArr[j].empID;
            empArr[j].empID = temp;
		}
	}

    i++;
	// swapping the employee records at position i and chosen pivot's postion
    strcpy(tempName, empArr[i].name);
    strcpy(empArr[i].name, empArr[r].name);
    strcpy(empArr[r].name, tempName);

    tempID = empArr[i].empID;
    empArr[i].empID = empArr[r].empID;
    empArr[r].empID = temp;
	return i;
}

void quickSort(Employee* empArr, int s, int N) {
    int x, y, diff, p;

	push(0);
    push(N-1);
	while (TOP>=0) {
		x = pop();
		y = pop();
		diff = x - y + 1;   // size of a sublist

        /* diff marks the size of a sublist. Now if diff is greater than the limit s that we
        we passed in the function argument, only then we will proceed in further sorting the 
        sublist. The question otherwise wants us to proceed with insertion sort. */
		if(diff > s){
            // getting the pivot element
            p = partition(empArr, y, x);
            // proceeding for sorting the left subsublist
            push(y);
            push(p-1);
            // proceeding for sorting the right subsublist
            push(p);
            push(x);
        }

        printf("Y = %d, X = %d, SIZE OF SUBLIST = %d\n", y, x, diff);
	}
}



/* Insertion Sort Part */
void insertionSort(Employee* empArr, int N){
    for(int i = 1; i < N; i++){
        int j = i-1;
        while(empArr[j--].empID > empArr[i].empID){
            // swapping the employee records at position i and position j
            strcpy(tempName, empArr[i].name);
            strcpy(empArr[i].name, empArr[j].name);
            strcpy(empArr[j].name, tempName);

            tempID = empArr[i].empID;
            empArr[i].empID = empArr[j].empID;
            empArr[j].empID = temp;
        }
    }
}


/* A specialized sorting method which does quicksort until a threshold limit s 
(as in the quicksort method) and then proceeds with insertion sort to sort the rest of the array. */
void optimizedSort(Employee* empArr, int s, int N){
    quickSort(empArr, s, N);
    insertionSort(empArr, N);
}