#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *read_count()
{
    //pthread_mutex_lock(&lock);
    printf("count is %d\r\n",count);
    //pthread_mutex_unlock(&lock);
    sleep(20);
}

void *plus_count()
{
    sleep(1);
    //pthread_mutex_lock(&lock);
    count++;
    //pthread_mutex_unlock(&lock);
}

int main()
{
    pthread_t pthread_tid[400];
    int i = 0;
    for(i = 0;i<400;i++)
    {
        pthread_create(&pthread_tid[i],NULL,(void *)plus_count,NULL);
    }
    for(i = 0;i<400;i++)
    {
       pthread_join(pthread_tid[i],NULL);
    }
     printf("~~~~~~~~~~count is %d~~~~~~~~~~~~~~~\r\n",count);
    pthread_mutex_destroy(&lock);
    return 0;
}