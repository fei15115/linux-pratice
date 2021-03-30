#include <stdio.h>
#include <pthread.h>

unsigned int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *read_count()
{
    pthread_mutex_lock(&lock);
    printf("count is %d\r\n",count);
    pthread_mutex_unlock(&lock);
}

void *plus_count()
{
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
}

int main()
{
    pthread_t pthread_tid[100];
    int i = 0;
    for(i = 0;i<99;i++)
    {
        if(i%2)
            pthread_create(&pthread_tid[i],NULL,(void *)plus_count,NULL);
        else
            pthread_create(&pthread_tid[i],NULL,(void *)read_count,NULL);
    }
    sleep(2);
    pthread_mutex_destroy(&lock);
}