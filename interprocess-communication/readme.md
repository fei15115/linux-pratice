# Here is some notes when I learn the process-communication

## 管道
### 创建管道
管道类似于队列形式；**fd[1]入队列；fd[0]出队列；**通过write和read函数对描述符进行读写；默认半双工（现部分支持全双工）
        #include <unistd.h>
        int pipe(int fd[2]);
### 管道读写
        write(fd[1],"hello world\n", 12);
        read(fd[0], &c, 1);
### 函数popen和pclose
常见的操作是创建一个连接到另一个进程的管道，然后读其输出或向输入端发送数据，为此，标准I/O提供了两个函数popen和pclose。这两个函数实现的操作是：创建一个管道，fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止。
**FILE *popen(const char *xmdstring,const char *type);**
**int pclose(FILE *fp);**