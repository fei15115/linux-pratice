#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_barrier_t barrier[10];

void *yessir(void *arg)
{
    int count = (int)arg;
    pthread_barrier_wait(&barrier[count]);
    printf("num %d,sir! yes sir!!!\r\n",count);
    sleep(1);
    for(count=count+1;count<10;count++)
        pthread_barrier_wait(&barrier[count]);
    pthread_exit((void *)0);
}

int main()
{
    int i = 2,j = 2;
    pthread_t tid[10];
    for(i;i<10;i++)
    {
        pthread_barrier_init(&barrier[i],NULL,i);
        pthread_create(&tid[i],NULL,(void *)yessir,(void *)i);
    }
    for(i=2;i<10;i++)
    {
        pthread_barrier_wait(&barrier[i]);
    }
    sleep(5);
    for(i=2;i<10;i++)
    {
        pthread_barrier_destroy(&barrier[i]);
    }
    exit(0);
}