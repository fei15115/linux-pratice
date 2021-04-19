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
    sem = sem_open("/aaa", O_CREAT|O_EXCL, S_IRWXU, 1);
    int looptime = 0;

    while(1)
    {
        sleep(10);
        printf("release it \r\n");
        sem_post(sem);
        looptime++;
        if(looptime >= 6)
        {
            sem_close(sem);
            break;
        }
    }
}