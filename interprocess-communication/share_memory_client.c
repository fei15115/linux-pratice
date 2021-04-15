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

// ��ʼ���ź���
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

// P����:
//  ���ź���ֵΪ1����ȡ��Դ�����ź���ֵ-1
//  ���ź���ֵΪ0�����̹���ȴ�
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*���*/
    sbuf.sem_op = -1; /*P����*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V������
//  �ͷ���Դ�����ź���ֵ+1
//  ����н������ڹ���ȴ�����������
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*���*/
    sbuf.sem_op = 1;  /*V����*/
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
        //���������ڴ�
    if((mem_id = shmget(sem_key,512,IPC_CREAT|0666)) == -1)
    {
        printf("mem get error!\r\n");
    }
    //����
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