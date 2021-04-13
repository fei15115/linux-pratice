# Here is some notes when I learn the process-communication

## 管道
### 创建管道
管道类似于队列形式；**fd[1]入队列；fd[0]出队列；**通过write和read函数对描述符进行读写；默认半双工（现部分支持全双工）<br>
        #include <unistd.h>
        int pipe(int fd[2]);
### 管道读写
        write(fd[1],"hello world\n", 12);
        read(fd[0], &c, 1);
### 函数popen和pclose
常见的操作是创建一个连接到另一个进程的管道，然后读其输出或向输入端发送数据，为此，标准I/O提供了两个函数popen和pclose。这两个函数实现的操作是：创建一个管道，fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止。<br>
**FILE *popen(const char *xmdstring,const char *type);**<br>
**int pclose(FILE *fp);**<br>

## 协同进程
过滤程序：UNIX系统过滤程序从标准输入读取数据，对其进行适当处理后写到标准输出。几个过滤程序通常在shell管道命令行中线性的连接。当一个程序产生某个过滤程序的输入，同时又读取该过滤程序的输出时，则该过滤程序就成为协同进程。<br>
Korn Shell提供了协同进程，但是Bournce-again shell 和C Shell并没有提供按协同进程方式将进程连接起来的方法。协同进程在shell的后台运行，其标准输入和标准输出通过管道连接到另外一个程序。虽然初始化一个协同进程并将其输入和输出连接到另一个进程，用到的shell愈大是十分奇特的，但是协同进程在C语言中也非常有用。<br>
注意：popen只提供连接到另一个进程的标准输入或者标准输出的一个的单向管道，而对于协同进程，则它有连接到另外一个进程的两个单向管道————一个接到其标准输出、一个连接到其标准输入，经过其处理后，再从标准输出读取数据。所以，利用popen并不能实现协同进程。<br>

## FIFO 命名管道
**int mkfifo( const char *pathname, mode_t mode);**
命名管道和无名管道大致相同，但是不相同的有下面3点：
1、FIFO 在文件系统中作为一个特殊的文件而存在，但 FIFO 中的内容却存放在内存中。
2、当使用 FIFO 的进程退出后，FIFO 文件将继续保存在文件系统中以便以后使用。
3、FIFO 有名字，不相关的进程可以通过打开命名管道进行通信。
windows的文件系统不支持FIFO，所以在虚拟机中编译完成后，需要转移到linux目录下测试执行。