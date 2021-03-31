#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int count = 0;
pthread_rwlock_t rwlock;

void *read_count()
{
    int i =0;
    while(i<400)
    {
        pthread_rwlock_rdlock(&rwlock);
        usleep(100);
        printf("count is %d\r\n",count);
        pthread_rwlock_unlock(&rwlock);
        i++;
    }
}

void *write_count()
{
    int i =0;
    while(i<400)
    {
        pthread_rwlock_wrlock(&rwlock);
        usleep(100);
        count++;
        pthread_rwlock_unlock(&rwlock);
        i++;
    }
}

int main()
{
    pthread_t pthread_tid[400];
    pthread_rwlock_init(&rwlock,NULL);
    int i = 0;
    for(i = 0;i<20;i++)
    {
        if((i%3)==0)
        pthread_create(&pthread_tid[i],NULL,(void *)write_count,NULL);
        else
        pthread_create(&pthread_tid[i],NULL,(void *)read_count,NULL);
    }
    for(i = 0;i<20;i++)
    {
       pthread_join(pthread_tid[i],NULL);
    }
    printf("at the end of count is %d\r\n",count);
    pthread_rwlock_destroy(&rwlock);
    return 0;
}