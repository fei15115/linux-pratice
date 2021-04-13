#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mymesg{
    long mtype;
    char mtext[512];
};

int main()
{
    key_t mesg_key = ftok("./",1);
    int msgid;
    char buff[256]="This is the first message!";
    struct mymesg send_buff;

    if((msgid = msgget(mesg_key,666)) < 0)
    {
        printf("message get error!\r\n");
    }
    send_buff.mtype=200;
    strcpy(send_buff.mtext,buff);
    sleep(5);
    if((msgsnd(msgid,&send_buff,strlen(buff),666)) < 0)
    {
        printf("send error!\r\n");
    }

}