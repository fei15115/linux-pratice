#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char cmd[20]="ifconfig";
    FILE *fp;
    char buff[100];

    fp = popen(cmd,"r");
    while(fgets(buff,100,fp) != NULL)
    {
        printf("read the output:%s\r\n",buff);
    }
    pclose(fp);
    return 0;
}