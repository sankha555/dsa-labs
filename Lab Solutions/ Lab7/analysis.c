/* Name: Sankha Das | ID: 2019A7PS0029P | Lab 7  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>
#include "employee.h"
#include "sorting.h"

double IStime, QStime, thisTime, AvgIStime, AvgQStime;

// function for running insertion sort and quicksort separately and caluclating their times
void testRun(Employee* empArr, int N){
    struct timeval t1, t2;
	IStime = 0;
    QStime = 0;

    // making a separate array for the insertion sort
	Employee ISArr[N];
	
    // running insertion sort on the array
	for(int i = 0; i < 20; i++){
        for(int i = 0; i < N; i++){
            ISArr[i] = empArr[i];
        }

        // start the timer
		gettimeofday(&t1, NULL); 
		
        insertionSort(ISArr, N);
		
        // stop the timer
        gettimeofday(&t2, NULL);
		
        // calculating the total time taken by insertion sort till now
        thisTime = 0;
		thisTime = (t2.tv_sec - t1.tv_sec) * 1000.0; 
		thisTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        IStime += thisTime;
	}

    // calculating average time taken by insertion sort
    AvgIStime = IStime/20;
	printf("Insertion sort =  %f ms | ", AvgIStime);


    // making a separate array for the quicksort
    Employee QSArr[N];

    // running quicksort on the array
	for(int i = 0; i < 20; i++){
        //making a separate array for the quick sort
		for(int i = 0; i < N; i++){
			QSArr[i] = empArr[i];
        };

        // start the timer
		gettimeofday(&t1, NULL); 

        // run normal quicksort with s factor as 1
		quickSort(QSArr, 1, N);

        // stop the timer
		gettimeofday(&t2, NULL);
		
        // calculating the total time taken by quicksort till now 
		thisTime = 0;
		thisTime = (t2.tv_sec - t1.tv_sec) * 1000.0; 
		thisTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        QStime += thisTime;
	}

    // calculating average time taken by quick sort
    AvgQStime = QStime/20;
	printf("Insertion sort =  %f ms \n", AvgQStime);
}

// estimating cutoff value according to pseudo-code
int estimateCutoff(Employee* empArr, int N){
    int mid;

    // deciding arbitrary values for min and max parameters in the pseudo-code
    int min = 5, max = N;
	testRun(empArr, min); 
	assert(AvgIStime < AvgQStime); // assert AvgIStime < AvgQStime
	testRun(empArr, max); 
	assert(AvgQStime > AvgIStime); // assert AvgQStime < AvgIStime

	do{
		mid = (min + max) / 2;
		min = mid;
		testRun(empArr, mid);
	}while(fabs(AvgIStime - AvgQStime) >= 0.001);

	return mid;
}
