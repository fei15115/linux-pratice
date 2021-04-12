#include <unistd.h>
#include <stdio.h>
#include <string.h>

int pip_read(int *fd)
{
    char buff[30];
    int len = 0;
    len = read(fd[0],&buff,16);
    buff[16] = 0;
    printf("[PIP-READ] %s \r\r\n",buff);
    return 0;
}

int pip_write(int *fd,char *str)
{
    int len = 0;
    len = write(fd[1],str,strlen(str));
    printf("[PIP-WRITE] %s\r\r\n",str);
    return 0;
}

int main()
{
    pid_t pid;
    int fd[2];
    if(pipe(fd) < 0)
        printf("pipe error!!!\r\n");
    
    if((pid = fork()) < 0)
    {
        printf("fork error!\r\n");
    }else if(pid > 0)
    {
        printf("Here is the child!\r\n");
        close(fd[1]);
        pip_read(fd);
    }else{
        printf("Here is the parent!\r\n");
        close(fd[0]);
        pip_write(fd,"I'm your father!");
    }
    return 0;
}