/multithread_count.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM 50000

int count = 0;
int key[2]={0,0};
int lock=0;
void SWAP(int *a,int *b)
{
    asm volatile("xchgl %0,%1":"=a"(*a):"m"(*b),"a"(*a));
}
void * worker_func(void *arg)
{
    int index = *(int *)arg;
    key[index]=1;
    do{
        SWAP(&key[index],&lock);
          }while(key[index]);
    /*临界区*/
    for (int i = 0; i < NUM; i++) {
        count++;
    }
    SWAP(&key[index],&lock);


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