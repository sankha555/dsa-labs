/* Name: Sankha Das*/
/* ID No.: 2019A7PS0029P */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "alloc.h"

void* myalloc(size_t size){
    void* ptr = (void*) malloc(size);

    // if there is not enough space left in memory to allocate
    if(ptr == NULL){
        printf("Not enough heap space to allocate memory...\n");
        return ptr;
    }
    heapSpace += size;

    return ptr;
}

void myfree(void* ptr, size_t size){
    heapSpace -= size;
    free(ptr);
}