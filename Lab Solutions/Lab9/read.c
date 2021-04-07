/*************************************************************/
/*  Name: SANKHA DAS    ID NO. 2019A7PS0029P    Lab Sec. P6  */   
/*  DSA Lab 9 - Hash Table Functions Implementation          */
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/******** GLOBAL VARIABLE DECLARATIONS *******/

// file streams
FILE* fin;
FILE* fout;

int countValid;             // variable to store count of valid strings in the text file
int tableSize, baseNumber;  // variables to store optimal table size and base number

// attributes of the hash table
int elementCount = 0;
int insertionCost = 0;
int queryingCost = 0;

/* structure definition for string record */
typedef struct stringRecord{
    int firstIndex;
    int countOccurences;
    struct stringRecord* next;
} Record;

/******* FUNCTIONS START HERE *******/

/* hash function to map string to sum of ASCII value of its characters */
int hashFunction(char* str, int tableSize, int baseNumber){
    int asciiSum = 0;
    for(int i = 0; i < strlen(str); i++){
        asciiSum += (int)str[i];
    }

    int hash = (asciiSum % baseNumber) % tableSize;
    return hash;
}

/* function to determine the collision frequency and find the optimal table size and base number */
void calcCollisions(char** strArr, int n){
    
    // variable and array declarations
    int tableSizes[3] = {5000, 50000, 500000};
    int baseNumbers[18] = {
        5003, 5009, 5011, 5000011, 5001443, 5004757, 
        50021, 74383, 98689, 50000017, 50001841, 50005531, 
        521669, 700001, 6111953, 500000003, 500001797, 500006083
    };
    int collisions[18] = {0};       // array to track the number of collisions in each combination

    short hashPossibilities[500000] = {0};  // a primitive version of a hash map to detect collision
    int hash;

    // evaluating collision frequency for each table size and base number
    for(int t = 0; t < 3; t++){
        // initializing the hash map 
        for(int i = 0; i < tableSizes[t]; i++)
            hashPossibilities[i] = 0;

        for(int b = 0; b < 6; b++){
            for(int i = 0; i < n; i++){
                hash = hashFunction((strArr+i), tableSizes[t], baseNumbers[b+6*t]);
                if(hashPossibilities[hash]==1){         // collision has been detected
                    collisions[b+6*t]++;                // increase the collision count for this combination
                }else{
                    hashPossibilities[hash] = 1;        
                }
            }
        }
    }

    // printing results of collisions for each table size and base number
    for(int t = 0; t < 3; t++){
        for(int b = 0; b < 6; b++){
            printf("Table Size = %d, Base Number = %d, Collisions = %d\n", tableSizes[t], baseNumbers[b+6*t], collisions[b+6*t]);
        }
    }

    // determining the optimal table size and base number
    int tsIndex = 0, bnIndex = 0;
    int min = collisions[0];
    int mini, i;
    for(i = 1; i < 18; i++){
        if(collisions[i]<min){
            mini = i;
            min = collisions[i];
        }
    }
    tsIndex = mini/6;
    bnIndex = mini%6;
    tableSize = tableSizes[tsIndex];    // table size determined
    baseNumber = baseNumbers[bnIndex];  // base number determined
}

/* function to parse the textfile and return the array of strings */
char** parseText(){
    fin = fopen("aliceinwonderland.txt", "r");  // initializing input stream
    char buffer[100];                           // input string buffer
    countValid = 0;                             

    int currSize = 20, flag;
    char book[30000][100];                      // array of strings
    while(!feof(fin)&&countValid<30000){        
        fscanf(fin, "%s", buffer);              // scan the file line-by-line till the end
        
        flag = 0;
        for(int i = 0; buffer[i]!='\0'; i++){
            if(!isalpha(buffer[i])){
                // ignoring the string with non-English characters
                flag = 1;
                break;
            }
        }
        
        if(!flag){
            // string ends
            strcpy(book[countValid++], buffer); // new string entered into array of strings
        }
        buffer[0] = '\0';                       // emptying the buffer for reading the next line 
    }
    fclose(fin);

    // printing no. of valid strings
    printf("There are %d valid strings in the file\n", countValid);

    // writing all the valid strings to a text file
    fout = fopen("book.txt", "w");
    for(int i = 0; i < countValid; i++){
        fprintf(fout, "%s\n", book+i);
    }

    return book;    // returning the array of strings
}

/* function to create and initialize the hash table */
void** createHashTable(int tableSize, int baseNumber){
    void* HASH_TABLE[tableSize];
    for(int i = 0; i < tableSize; i++){
        HASH_TABLE[i] = NULL;   
    }
    return HASH_TABLE;
}

/* function to insert a new string record in the hash table */
void** insert(void** hashTable, char** strArr, int j, int n){
    // if hashTable[j] is empty
    if(hashTable[j] == NULL){
        Record* newRecord = (Record*) malloc(sizeof(Record));   // new record to be inserted
        
        int firstInd;
        // finding the first occurence index for this string in the string array
        for(int i = 0; i < n; i++){
            if (strcmp((strArr+i), (strArr+j)) == 0){
                firstInd = i;
                break;
            }
        }
        newRecord->firstIndex = firstInd;
        //printf("first index = %d\n", firstInd);
        newRecord->countOccurences = 1;
        newRecord->next = NULL;

        hashTable[j] = newRecord;
        insertionCost++;
    }else{
        // if hashTable[j] is not empty
        Record* curr = hashTable[j];
        Record* last = NULL;            // to track the node one behind the current node
        int checkIndex;
        while(curr != NULL){
            // trying to find the string in the corresponding chain
            checkIndex = curr->firstIndex;
            if(strcmp((strArr+checkIndex), (strArr+j))==0){
                // string already exists in this node of the chain of the hash table
                curr->countOccurences += 1;
                break;
            }
            last = curr;
            curr = curr->next;
            insertionCost++;     // increasing the insertion cost 
        }

        // the string doesn't exist in this chain yet, so insert a new record for the string
        if(curr==NULL){
            Record* newRecord = (Record*) malloc(sizeof(Record));
            
            int firstInd;
            // finding the first occurence index for this string in the string array
            for(int i = 0; i < n; i++){
                if (strcmp((strArr+i), (strArr+j)) == 0){
                    firstInd = i;
                    break;
                }
            }
            // attaching a new record to the end of the chain
            newRecord->firstIndex = firstInd;
            newRecord->countOccurences = 1;
            newRecord->next = NULL;
            last->next = newRecord;

            insertionCost++;    // increasing the insertion cost
        }
    }

    elementCount++;         // updating the number of elements stored in the hash table
    return hashTable;       // returning the updated hash table
}

/* function to insert all string records in the string array */
int insertAll(void** hashTable, int tableSize, int baseNumber, char** strArr, int n){
    for(int i = 0; i < n; i++){
        hashTable = insert(hashTable, strArr, hashFunction((strArr+i), tableSize, baseNumber), n);
    }
    int ic = insertionCost;     // returning the total insertion cost incurred in inserting all the strings in the array
    return ic;
}

/* function to query and find presence of a string in the hash table */
Record* lookUp(void** hashTable, int tableSize, int baseNumber, char* str, char** strArr){
    int i = hashFunction(str, tableSize, baseNumber);   // hash value of the string
    int fi;
    queryingCost = 0;
    if(hashTable[i]==NULL){
        // if the string doesn not exist in the hash table
        queryingCost++;
        return NULL;
    }else{
        // search the string in the corresponding chain in the hash table
        Record* curr = hashTable[i];
        while(curr!=NULL){
            queryingCost++;
            fi = curr->firstIndex;
            if(strcmp(str, (strArr+fi))==0){
                break;
            }
            curr = curr->next;
        }
        return curr;    // returning the found record for the string that was to be looked up
    }
}

/* function to query and find presence of all strings from the string array in the hash table  */
int lookUpAll(void** hashTable, int tableSize, int baseNumber, char** strArr, float m, int n){
    queryingCost = 0;   // initializing querying cost to 0 before the operation
    for(int i = 0; i < (int)(m*(float)n); i++){
        if(hashTable[i]==NULL){
            // string doesn't exist in the hash table
            queryingCost++;
        }else{
            // search the string in the corresponding chain in the hash table
            Record* curr = hashTable[i];
            while(curr!=NULL){
                queryingCost++;
                if(strcmp((strArr+i), (strArr+(curr->firstIndex)))==0){
                    break;
                }
                curr = curr->next;
            }
        }
    }
    int qc = queryingCost;  // returning the total querying cost incurred in looking up all the strings in the array
    return qc;
}

/* main function */
int main(){

    // Implementation of Exercise 2 for Lab 9    

    // taking the array of strings
    char** book = parseText();

    // finding the optimal table size and base number for the hash table and hash function
    calcCollisions(book, countValid);
    printf("Optimal table size = %d, base number = %d\n", tableSize, baseNumber);

    // creating the hash table
    void** hashTable = createHashTable(tableSize, baseNumber);

    // inserting all the strings in the book array and printing the total insertion cost incurred
    int i = insertAll(hashTable, tableSize, baseNumber, book, countValid);
    printf("Insertion cost = %d\n", i);

    // looking up all the strings in the book array and printing the total querying cost incurred
    int q = lookUpAll(hashTable, tableSize, baseNumber, book, 0.2f, countValid);
    printf("Quering cost = %d\n", q);

    return 0;
}
