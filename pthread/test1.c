#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

unsigned int sleep (unsigned int seconds);
unsigned int gol_count = 0;
pthread_mutex_t lock;

void plus_count()
{
    pthread_t son_tid = pthread_self();
    //pthread_mutex_lock(&lock);
    gol_count+=2;
    //pthread_mutex_unlock(&lock);
    printf("=====tid is %lu===count is %d\r\n",son_tid,gol_count);
}

void read_count()
{
    pthread_t son_tid = pthread_self();
    //pthread_mutex_lock(&lock);
    //gol_count+=2;
    //pthread_mutex_unlock(&lock);
    printf("=====tid is %lu===count is %d\r\n",son_tid,gol_count);
}

void *pthread_print(long unsigned int *inter)
{
    // pthread_t son_tid = pthread_self();
    // printf("son tid is %lu\r\n",son_tid);
    // printf("main tid is %lu\r\n",*inter);
    int i=0;
    for(i;i<100;i++)
    {
        read_count();
        sleep(1);
        
    }
    pthread_exit((void *)3);
}

int main(void)
{
    pthread_mutex_init(&lock,NULL);
    char s[55]="pthread create";
    int i=0;
    pthread_t main_tid = pthread_self();
    printf("main tid is %lu\r\n",main_tid);

    pthread_t son_tid;
    pthread_t son2_tid;
    long unsigned int main_num = main_tid;
    pthread_create(&son_tid,NULL,(void *)pthread_print,&main_num);
    //long unsigned int main_num = main_tid;
    pthread_create(&son2_tid,NULL,(void *)pthread2_print,&main_num);

    // void *return_code1,*return_code2;
    // pthread_join(son_tid,&return_code1);
    // pthread_join(son2_tid,&return_code2);
    //printf("pthread1 return %ld \r\npthread2 return %ld\r\n",(long)return_code1,(long)return_code2);
    sleep(190);
    //printf("=====tid is %lu===count is %d\r\n",son_tid,gol_count);
    pthread_mutex_destroy(&lock);
    exit(0);
}