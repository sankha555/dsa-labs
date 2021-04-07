/* Name: Sankha Das */
/* ID No.: 2019A7PS0029P */
#include <stdio.h>
#include "main.h"

/* procedure to read records of credit cards from text file */
extern CreditCard* readCreditCards(char* filename, int* currArraySize);

/* procedure to sort array of credit cards using insertion sort */
extern CreditCard* insertInOrder(CreditCard* cardArray, CreditCard card, int pos, int* currArraySize);