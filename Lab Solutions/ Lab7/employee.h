#include <stdio.h>

typedef struct employee{
    char name[11];
    int empID;
} Employee;

/* method to read employee records from file */
Employee* readRecords(char* filename, int N);