/* Name: Sankha Das */
/* ID No.: 2019A7PS0029P */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include "sorting.h"

int currArraySize = 10;
int* stackBottom = &currArraySize;

int main(int argc, char* argv[]){

    /* Implementation for Lab Sheet 5 - Q2 */

    /**********************************************************************************/
    /*  To run the program, please run the following commands in the command prompt:  */
    /*  1. gcc -c main.c sorting.c                                                    */
    /*  2. gcc -o exe main.o sorting.o                                                */
    /*  3. ./exe 10 (or any other input file)                                         */
    /**********************************************************************************/    

    struct timeval t1, t2;
    double elapsedTime;

    char* filename = argv[1];
    // Initializing the array by reading all credit cards information in the textfile
    CreditCard* cardArray = readCreditCards(filename, &currArraySize);

    // Start the timer
    gettimeofday(&t1, NULL);

    /* Running the insertion sort Algorithm */
    for(int i = 1; i < currArraySize; i++){
        insertInOrder(cardArray, cardArray[i], i, &currArraySize);
    }
    /* Sorting ends */

    // Stop the timer
    gettimeofday(&t2, NULL);

    // Calculate the time elapsed in program run
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    // Calculating stack space used
    long int stackSpace = stackTop - stackBottom;

    // Displaying Sorted Array
    for(int i = 0; i < currArraySize; i++){
        printf("%ld, %s, %s, %s, %s\n", cardArray[i].cardNo, cardArray[i].bankCode, cardArray[i].expiryDate, cardArray[i].firstName, cardArray[i].lastName);
    }

    // Writing program run statistics to a text file for analysis purposes
    // Order of Data : Array Size ; Stack Space Used ; Time Used (separated by semicolons)
    FILE* fout = fopen("stats.txt", "a");
    fprintf(fout, "%s;%ld;%f\n", filename, stackSpace, elapsedTime);

    // Freeing up memory 
    free(cardArray);
    
    return 0;
}
