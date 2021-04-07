/* Name: Sankha Das | ID: 2019A7PS0029P | Lab 7  */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include <string.h>

FILE* fin;

/* function for reading records from file */
Employee* readRecords(char* filename, int N){
    // dummy variables for reading from file
    char name[11];
    int id;

    // a new array for employees
    Employee empArr[N];

    // reading records one by one from file
    fin = fopen(filename, "r");
    int i = 0;
    while(!feof(fin)){
        fscanf(fin, "%s %d\n", name, &id);
        
        // reading the values of name and id from file
        Employee newEmp;
        strcpy(newEmp.name, name);
        newEmp.empID = id;

        // appending to the employee array
        empArr[i++] = newEmp;
    }

    return empArr;
}
