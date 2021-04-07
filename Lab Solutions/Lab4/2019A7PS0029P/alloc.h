#include <stdio.h>
#include <stdlib.h>

/* Global Variable for Heap Space */
int heapSpace;

/* Modified Memory Allocation Function */
extern void* myalloc(size_t size);

/* Modified Memory De-Allocation Function */
extern void myfree(void* ptr, size_t size);