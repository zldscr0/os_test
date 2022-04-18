// multithread_count.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM 50000

int count = 0;
int inside[2]={0,0};
int turn = 0;
int turn_num[2]={1,0};
void * worker_func(void *arg)
{
    int index = *(int *)arg;
    inside[index]=1;
    turn = turn_num[index];
    while(inside[turn_num[index]]&&turn==turn_num[index]);

    /*临界区*/
    for (int i = 0; i < NUM; i++) { 
        count++;
    }
    inside[index]=0;
    
   // printf("%d\n",index);
    return NULL;
}


int main(void)
{
    pthread_t worker1, worker2;
    void *worker1_status;
    void *worker2_status;
    int index0=0;
    int index1=1;
    pthread_create(&worker1, NULL, worker_func, &index0);
    pthread_create(&worker2, NULL, worker_func, &index1);

    pthread_join(worker1, &worker1_status);
    pthread_join(worker2, &worker2_status);

    printf("Count: %d\n", count);

    return 0;
}