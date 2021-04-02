#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
struct mess_que{
    struct mess_que *next;
    int message;
};
struct mess_que *queue;


// Ëæ»úÊý·¶Î§[mi, ma]
int randint(int mi, int ma) {
    double r = (double)rand() * (1.0 / ((double)RAND_MAX + 1.0));
    r *= (double)(ma - mi) + 1.0;
    return (int)r + mi;
}

void *costm_callback()
{
    struct mess_que *m;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(queue == NULL)
            pthread_cond_wait(&cond,&mutex);
        printf("[%s]queue message is %d\r\n",__func__,queue->message);
        m = queue;
        queue = m->next;
        pthread_mutex_unlock(&mutex);
    }
}

void *proc_callback()
{
    while(1)
    {
        usleep(randint(1000*100, 1000*200));
        struct mess_que *m = malloc(sizeof(*m));
        memset(m, 0, sizeof(*m));
        m->message = randint(0, 1000);
        printf("[%s]queue message is %d\r\n",__func__,m->message);
        pthread_mutex_lock(&mutex);
        m->next = queue;
        queue = m;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
}

int main() 
{
#define PRO_NUM 1
#define CON_NUM 8
    pthread_t tid_p[PRO_NUM];
    pthread_t tid_c[CON_NUM];

    int i;
    for (i = 0; i < PRO_NUM; ++i) {
        pthread_create(&tid_p[i], NULL, proc_callback, NULL);
    }
    for (i = 0; i < CON_NUM; ++i) {
        pthread_create(&tid_c[i], NULL, costm_callback, NULL);
    }


    for (i = 0; i < PRO_NUM; ++i) {
        pthread_join(tid_p[i], NULL);
    }
    for (i = 0; i < CON_NUM; ++i) {
        pthread_join(tid_c[i], NULL);
    }
    return 0;
}