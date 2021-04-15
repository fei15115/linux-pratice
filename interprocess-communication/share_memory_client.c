#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};

// 初始化信号量
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P操作:
//  若信号量值为1，获取资源并将信号量值-1
//  若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = -1; /*P操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V操作：
//  释放资源并将信号量值+1
//  如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = 1;  /*V操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}

int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}

int main()
{
    key_t sem_key = ftok("./",1);
    int sem_id,mem_id;
    int tmp;
    if((sem_id = semget(sem_key, 1,IPC_CREAT|0666)) == -1)
    {
        printf("sem get error!\r\n");
    }
    //init_sem(sem_id,1);
        //创建共享内存
    if((mem_id = shmget(sem_key,512,IPC_CREAT|0666)) == -1)
    {
        printf("mem get error!\r\n");
    }
    //连接
    int *share_int = (int *)shmat(mem_id,0,0);
    if(*share_int == -1)
    {
        printf("connet error \r\n");
    }
    while(1)
    {
        sem_p(sem_id);
        printf("[client]get the source!\r\n");
        tmp = *share_int;
        (*share_int)++;
        printf("[CLIENT]read the share_int is %d;set to %d~~~~~~~\r\n",tmp,*share_int);
        sem_v(sem_id);
    }
    shmdt(share_int);
    del_sem(sem_id);

}