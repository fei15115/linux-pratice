#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n,int1,int2;
    char line[256];
    while((n= read(STDIN_FILENO, line, 255)) > 0)
    {
        line[n] = 0;
        if(sscanf(line,"%d%d", &int1, &int2) == 2)
        {
            sprintf(line, "%d\n",int1 + int2);
            n = strlen(line);
            if(write(STDOUT_FILENO, line, n) != n)
                printf("write error!\r\n");
        }else
        {
            if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
                printf("write error!\r\n");
        }
    }
    exit(0);
}