/***********file:   main.c *********/
/* Name: Sankha Das ID: 2019A7PS0029P */
#include <stdio.h>
#include "seqListOps.h"

int main(void)
{
 int i; int size;
 JobList list;
 size = inputJobs(list);
 printf("The Jobs waiting on CPU are:\n");
 printJobList(list, size);
 sortJobList(list, size);
 printf("The Jobs after sorting are:\n");
 printJobList(list, size);
 return 0;
}
 
