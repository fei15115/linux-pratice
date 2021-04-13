#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/ipc.h>

struct mymesg{
    long mtype;
    char mtext[512];
};

int main()
{
    key_t mesg_key = ftok("./",1);
    int msgid;
    char buff[256];
    int buff_len = 255;
    struct mymesg recv_buff;

    if((msgid = msgget(mesg_key,666)) < 0)
    {
        printf("message get error!\r\n");
    }
    if((msgrcv(msgid,&recv_buff,buff_len,0,666)) < 0)
    {
        printf("send error!\r\n");
    }else{
        printf("recv a message :%s\r\n",recv_buff.mtext);
    }
    exit(0);

}