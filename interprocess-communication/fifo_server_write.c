#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

 

int main(int argc, char *argv[])

{
	int fd;
	int ret;
	ret = mkfifo("./my_fifo", 777);//���������ܵ�
	if(ret != 0)
	{
		perror("mkfifo");
	}

	printf("before open\n");
	fd = open("my_fifo", O_WRONLY); //����ֻ��
	if(fd < 0)
	{
		perror("open fifo");
	}
	printf("after open\n");
	printf("before write\n");

	// 5s����������ܵ�д���ݣ�û����ǰ������read()����
	sleep(5);
	char send[100] = "Hello Mike";
	write(fd, send, strlen(send));
	printf("write to my_fifo buf=%s\n", send);
	return 0;

}