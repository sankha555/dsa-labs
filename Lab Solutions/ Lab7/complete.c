/* Name: Sankha Das | ID: 2019A7PS0029P | Lab 7  */
/* List of all function definitions I have written in this lab assignment
(I haven't listed helper methods and main method that I defined, here) */

// In employee.c
Employee* readRecords(char* filename, int N){
    char name[11];
    int id;

    Employee empArr[N];

    fin = fopen(filename, "r");
    int i = 0;
    while(!feof(fin)){
        fscanf(fin, "%s %d\n", name, &id);
        
        Employee newEmp;
        strcpy(newEmp.name, name);
        newEmp.empID = id;

        empArr[i++] = newEmp;
    }

    return empArr;
}

// In sorting.c

/* Quicksort Part */
int partition(Employee* empArr, int l, int r) {
	int p = empArr[r].empID;
	int i = l - 1, j = l;

	while(j++ < r)
		if(empArr[j].empID <= p) {
			i++;
			// swapping the employee records at positions i and j
            strcpy(tempName, empArr[i].name);
            strcpy(empArr[i].name, empArr[j].name);
            strcpy(empArr[j].name, tempName);

            tempID = empArr[i].empID;
            empArr[i].empID = empArr[j].empID;
            empArr[j].empID = temp;
		}
	}

    i++;
	// swapping the employee records at position i and chosen pivot's postion
    strcpy(tempName, empArr[i].name);
    strcpy(empArr[i].name, empArr[r].name);
    strcpy(empArr[r].name, tempName);

    tempID = empArr[i].empID;
    empArr[i].empID = empArr[r].empID;
    empArr[r].empID = temp;
	return i;
}

void quickSort(Employee* empArr, int s, int N) {
    int x, y, diff, p;

	push(0);
    push(N-1);
	while (TOP>=0) {
		x = pop();
		y = pop();
		diff = x - y + 1;   // size of a sublist

        /* diff marks the size of a sublist. Now if diff is greater than the limit s that we
        we passed in the function argument, only then we will proceed in further sorting the 
        sublist. The question otherwise wants us to proceed with insertion sort. */
		if(diff > s){
            // getting the pivot element
            p = partition(empArr, y, x);
            // proceeding for sorting the left subsublist
            push(y);
            push(p-1);
            // proceeding for sorting the right subsublist
            push(p);
            push(x);
        }

        printf("Y = %d, X = %d, SIZE OF SUBLIST = %d\n", y, x, diff);
	}
}



/* Insertion Sort Part */
void insertionSort(Employee* empArr, int N){
    for(int i = 1; i < N; i++){
        int j = i-1;
        while(empArr[j--].empID > empArr[i].empID){
            // swapping the employee records at position i and position j
            strcpy(tempName, empArr[i].name);
            strcpy(empArr[i].name, empArr[j].name);
            strcpy(empArr[j].name, tempName);

            tempID = empArr[i].empID;
            empArr[i].empID = empArr[j].empID;
            empArr[j].empID = temp;
        }
    }
}


/* A specialized sorting method which does quicksort until a threshold limit s 
(as in the quicksort method) and then proceeds with insertion sort to sort the rest of the array. */
void optimizedSort(Employee* empArr, int s, int N){
    quickSort(empArr, s, N);
    insertionSort(empArr, N);
}


// In Analysis.c
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