#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stringRecord{
    int firstIndex;
    int countOccurences;
    stringRecord* next;
} Record;

int tableSize = 11;
int baseNumber = 5;

int hashFunction(char* str, int tableSize, int baseNumber){
    int asciiSum = 0;
    for(int i = 0; i < strlen(str); i++){
        asciiSum += int(str[i]);
    }

    int hash = (asciiSum % baseNumber) % tableSize;
    return hash;
}

void** createHashTable(int tableSize, int baseNumber){
    void** HASH_TABLE[tableSize+3];
    for(int i = 0; i < tableSize; i++){
        HASH_TABLE[i] = NULL;
    }

    int* elementCount = 0;
    int* insertionCost = 0;
    int* queryingCost = 0;

    HASH_TABLE[tableSize] = elementCount;
    HASH_TABLE[tableSize+1] = insertionCost;
    HASH_TABLE[tableSize+2] = queryingCost;
    return HASH_TABLE;
}

void insert(void** hashTable, char** strArr, int j, int n){
    // if hashTable[j] is empty
    if(hashTable[j] == NULL){
        Record* newRecord = (Record*) malloc(sizeof(Record));
        int firstInd;
        for(int i = 0; i < n; i++){
            if (strcpy(strArr[i], strArr[j]) == 0){
                firstInd = i;
                break;
            }
        }
        newRecord->firstIndex = firstInd;
        newRecord->countOccurences = 1;
        newRecord->next = NULL;

        hashTable[j] = newRecord;
    }else{
        // if hashTable[j] is not empty
        Record* curr = hashTable[j];
        Record* last = NULL;
        int checkIndex;
        while(curr != NULL){
            checkIndex = curr->firstIndex;
            if(strcpy(strArr[checkIndex], strArr[j])==0){
                // string already exists in this node of the chain of the hash table
                curr->countOccurences += 1;
                break;
            }
            last = curr;
            curr = curr->next;
        }

        // the string doesn't exist in this chain yet, so insert a new record for the string
        if(curr==NULL){
            Record* newRecord = (Record*) malloc(sizeof(Record));
            int firstInd;
            for(int i = 0; i < n; i++){
                if (strcpy(strArr[i], strArr[j]) == 0){
                    firstInd = i;
                    break;
                }
            }
            newRecord->firstIndex = firstInd;
            newRecord->countOccurences = 1;
            newRecord->next = NULL;

            last->next = newRecord;
        }
    }

    *(hashTable[tableSize])++;
}

int insertAll(void** hashTable, int tableSize, int baseNumber, char** strArr){
    int n = strlen(strArr);
    for(int i = 0; i < n; i++){
        insert(hashTable, strArr, hashFunction(strArr[i], tableSize, baseNumber));
        *(hashTable[tableSize+1])++;
    }
    return *(hashTable[tableSize+1]);
}

Record* lookUp(void** hashTable, int tableSize, int baseNumber, char* str, char** strArr){
    int i = hashFunction(str, tableSize, baseNumber);
    *(hashTable[tableSize+2]) = 0;
    if(hashTable[i]==NULL){
        *(hashTable[tableSize+2])++;
        return NULL;
    }else{
        Record* curr = hashTable[i];
        while(curr!=NULL){
            *(hashTable[tableSize+2])++;
            if(strcpy(str, strArr[curr->firstIndex])==0){
                break;
            }
        }
        return curr;
    }
}

int lookUpAll(void** hashTable, int tableSize, int baseNumber, char** strArr, float m, int n){
    *(hashTable[tableSize+2]) = 0;
    for(int i = 0; i < m*n; i++){
        if(hashTable[i]==NULL){
            *(hashTable[tableSize+2])++;
            return NULL;
        }else{
            Record* curr = hashTable[i];
            while(curr!=NULL){
                *(hashTable[tableSize+2])++;
                if(strcpy(strArr[i], strArr[curr->firstIndex])==0){
                    break;
                }
            }
        }
    }
    return *(hashTable[tableSize+2]);
}
