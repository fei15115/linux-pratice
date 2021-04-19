#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <semaphore.h>

int main()
{
    sem_t *sem;
    sem = sem_open("/aaa",0);
    int looptime = 0;

    while(1)
    {
        sem_wait(sem);
        printf("got it \r\n");
        looptime++;
        if(looptime >= 6)
        {
            sem_close(sem);
            break;
        }
    }
}