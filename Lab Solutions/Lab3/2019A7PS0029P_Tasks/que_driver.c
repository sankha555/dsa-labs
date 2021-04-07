#include <stdio.h>
#include "que.h"

int main(){ 

    int n = 5;
    struct Queue* q = newQ();

    int temp;
    for(int i = 0; i < n; i++){
        printf("Enter element: ");
        scanf("%d", &temp);
        q = addQ(q, temp);
    }

    printf("%d is the front of the queue...\n", front(q));
    deleteQ(q);
    deleteQ(q);
    deleteQ(q);
    deleteQ(q);
    deleteQ(q);
    deleteQ(q);

    printf("%d is the front of the queue...\n", front(q));

    return 0;
}