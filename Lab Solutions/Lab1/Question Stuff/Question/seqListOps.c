/***********file:   Ops.c *********/
/* Name: Sankha Das ID: 2019A7PS0029P */
#include <stdio.h>

#include "storage.h"
#include "compare.h"
int nextfreeloc = 0;
Store st;

SeqList createlist()
{
 SeqList sl;
 sl.head = nextfreeloc++;
 sl.size = 0;
 st[sl.head].next = -1;
 return (sl);
}

void printJob (Job j)
{
printf ("JOB ID = %d, Priority = %d, Execution time = %d, Arrival time = %d \n",j.id,j.pri,j.et,j.at);
}


int inputJobs (JobList list)
{
 int i; int size;

 printf("\n Enter the Number of Jobs :");
 scanf("%d", &size);

 for (i=0;i<size;i++)
 {
  printf ("\nEnter job ID");
  scanf ("%d",&list[i].id);
  printf ("Enter Priority (from 0 - 2)");
  scanf ("%d",&list[i].pri);
  printf ("Execution Time");
  scanf ("%d",&list[i].et);
  printf ("Arrival Time");
  scanf ("%d",&list[i].at);
 }
 return size;
}

SeqList insert(Job j , SeqList sl)
{
    if(st[sl.head].next == -1){
        st[sl.head].next = nextfreeloc++;
        st[st[sl.head].next].ele = j;
        st[st[sl.head].next].next = -1;
    }else{
        int curr_loc = st[sl.head].next;
        int prev_loc = sl.head;
        while(curr_loc != -1 && compare(j, st[curr_loc].ele) != LESSER){
            prev_loc = curr_loc;
            curr_loc = st[curr_loc].next;
        }
        int new_loc = nextfreeloc++;
        st[new_loc].ele = j;
        st[new_loc].next = curr_loc;
        st[prev_loc].next = new_loc;
    }
}
  
void insertelements (JobList list , int size, SeqList s[3])
{
    /*for(int i = 0; i < size; i++){
        switch (list[i].pri){
            case PRI_0:
                insert(list[i], s[0]);
                break;

            case PRI_1:
                insert(list[i], s[1]);
                break;

            case PRI_2:
                insert(list[i], s[2]);
                break;
        }
    }*/
    
    /* For assignment using triple loop */
    for(int p = 0; p < 3; p++){
        for(int i = 0; i < size; i++){
            if(list[i].pri == p){
                insert(list[i], s[p]);
            }
        }
    }
}

void copy_sorted_ele(SeqList s[3] , JobList ele)
{   
    int loc = 0;
    for(int i = 2; i >= 0; i--){
        SeqList sl = s[i];
        int curr_loc = st[sl.head].next;
        while(curr_loc!=-1){
            ele[loc++] = st[curr_loc].ele;
            curr_loc = st[curr_loc].next;
        }
    }
}

void printlist(SeqList sl)
{   
    int curr_loc = st[sl.head].next;
    while(curr_loc!=-1){
        printJob(st[curr_loc].ele);
        curr_loc = st[curr_loc].next;
    }
}

void printJobList(JobList list, int size)
{
    for(int i = 0; i < size; i++){
        printJob(list[i]);
    }
}

void sortJobList(JobList list, int size)
{
 SeqList seq[3];
 seq[0] = createlist();
 seq[1] = createlist();
 seq[2] = createlist();
 insertelements (list, size, seq);
 //printlist(seq[0]);   
 //printlist(seq[1]);
 //printlist(seq[2]);
 printf("\n");
 copy_sorted_ele (seq , list); 
}
