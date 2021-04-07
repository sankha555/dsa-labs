#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include "analysis.h"

int main(int argc, char *argv[]) {
    /* Main function to run the estimateCutoff funtion */
    /* Analysis screenshot provided in the folder (I didn't have access to my Windows computer this week
    and dont have Excel in Mac, so I did the assignment this week on Online Excel web, and have attached
    the screenshot of it thus). Please find the screenshot in the folder and consider it for the analysis.) */
	char* filename = argv[1];
    int N = atoi(filename);
	Employee* empArr = readRecords(filename, N);
    
    printf("Cutoff size for %d records is %d\n", N, estimateCutoff(empArr, N));

    for(int i = 0; i < N; i++){
        free(empArr);
    }

    return 0;
}