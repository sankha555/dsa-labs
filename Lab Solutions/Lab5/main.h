/* Name: Sankha Das */
/* ID No.: 2019A7PS0029P */
#include <stdio.h>

/* defining a structure to store information about credit cards */
typedef struct creditCard{
    long int cardNo;
    char bankCode[20];
    char expiryDate[10];
    char firstName[20];
    char lastName[20];
} CreditCard;

// a pointer to track the address of a dummy variable in top-of-stack frame
int* stackTop;
