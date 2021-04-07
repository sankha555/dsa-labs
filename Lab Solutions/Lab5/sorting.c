/* Name: Sankha Das */
/* ID No.: 2019A7PS0029P */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

FILE* fin;
CreditCard temp;

CreditCard* readCreditCards(char* filename, int* currArraySize){

    // textfile containing credit card informations
    fin = fopen(filename, "r");
    
    // Initializing the array for storing 10 (as given in currArraySize) cards initially
    CreditCard* cardArray = (CreditCard*) malloc(sizeof(CreditCard)*(*currArraySize)); 

    int i = 0;
    while(!feof(fin)){
        
        // a CreditCard variable to store information about the newly read card
        CreditCard newCard;
        
        /* Sequentially reading each individual attribute in each line of credit card data */
        fgetc(fin);                             // Absorbing the initial " character in each line
		fscanf(fin, "%ld", &newCard.cardNo);    // Reading the Card No.
        
        // Reading comma separated attributes and absorbing the final " character
		fscanf(fin, ",%[^,],%[^,],%[^,],%[^\"]\"\n", newCard.bankCode, newCard.expiryDate, newCard.firstName, newCard.lastName);    
		
        if(i < *currArraySize){
            cardArray[i++] = newCard;
        }else{
            (*currArraySize)++;
            cardArray = (CreditCard*) realloc(cardArray, sizeof(CreditCard)*(*currArraySize));
            cardArray[i++] = newCard;
        }
    }

    return cardArray;
}

CreditCard* insertInOrder(CreditCard* cardArray, CreditCard card, int pos, int* currArraySize){

    /* 
       In case the entire array has been traversed by the insertion sort algorithm 
       then the stack pointer has reached it's top most location (i.e. maximum stack usage 
       has been reached for the program run). Taking address of a dummy variable into the
       stackTop pointer to estimate the total stack space used.
    */
    if(pos == *currArraySize - 1){
        int stackTopInitializer;
        stackTop = &stackTopInitializer;
    }

    // Insert the current card into its appropriate position in the array
    int curr = pos-1;
    while(curr >= 0 && cardArray[curr].cardNo > card.cardNo){
        /* Shift the card just to the left of the current card, one place to the right */
        cardArray[curr+1].cardNo = cardArray[curr].cardNo;
        strcpy(cardArray[curr+1].bankCode, cardArray[curr].bankCode);
        strcpy(cardArray[curr+1].expiryDate, cardArray[curr].expiryDate);
        strcpy(cardArray[curr+1].firstName, cardArray[curr].firstName);
        strcpy(cardArray[curr+1].lastName, cardArray[curr].lastName);

        curr--;
    }

    // Appropriate position for the current card has been reached. 
    // Writing its contents to this position in the array.
    cardArray[curr+1].cardNo = card.cardNo;
    strcpy(cardArray[curr+1].bankCode, card.bankCode);
    strcpy(cardArray[curr+1].expiryDate, card.expiryDate);
    strcpy(cardArray[curr+1].firstName, card.firstName);
    strcpy(cardArray[curr+1].lastName, card.lastName);

    return cardArray;
}
