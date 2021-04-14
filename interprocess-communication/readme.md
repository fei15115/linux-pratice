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
**int mkfifo( const char *pathname, mode_t mode);**<br>
命名管道和无名管道大致相同，但是不相同的有下面3点：<br>
1、FIFO 在文件系统中作为一个特殊的文件而存在，但 FIFO 中的内容却存放在内存中。<br>
2、当使用 FIFO 的进程退出后，FIFO 文件将继续保存在文件系统中以便以后使用。<br>
3、FIFO 有名字，不相关的进程可以通过打开命名管道进行通信。<br>
windows的文件系统不支持FIFO，所以在虚拟机中编译完成后，需要转移到linux目录下测试执行。<br>

## XSI IPC
        有三种称作XSI IPC的IPC：消息队列，信号量以及共享内存。<br>

### 标识符和键
        #include <sys/ipc.h>
        key_t ftok(const char *path,int id);
当成功执行的时候，一个key_t值将会被返回，否则 -1 被返回。在一般的UNIX实现中，是将文件的索引节点号取出，前面加上子序号得到key_t的返回值。如指定文件的索引节点号为65538，换算成16进制为 0x010002，而你指定的ID值为38，换算成16进制为0x26，则最后的key_t返回值为0x26010002。<br>
查询文件索引节点号的方法是： ls -i<br>

### 消息队列
消息队列是消息的链表，存放在内核中并由消息队列标识符表示。消息队列提供了一个从一个进程向另一个进程发送数据块的方法，每个数据块都可以被认为是有一个类型，接受者接受的数据块可以有不同的类型。但是同管道类似，它有一个不足就是每个消息的最大长度是有上限的(MSGMAX)，每个消息队列的总的字节数(MSGMNB)，系统上消息队列的总数上限(MSGMNI)。可以用cat /proc/sys/kernel/msgmax查看具体的数据。<br>
#### 消息队列的创建
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/msg.h>
        int msgget(key_t key, int msgflag);
key：某个消息队列的名字，用ftok()产生<br>
msgflag：有两个选项IPC_CREAT和IPC_EXCL，单独使用IPC_CREAT，如果消息队列不存在则创建之，如果存在则打开返回；单独使用IPC_EXCL是没有意义的；两个同时使用，如果消息队列不存在则创建之，如果存在则出错返回。
返回值：成功返回一个非负整数，即消息队列的标识码，失败返回-1<br>
#### 消息队列的发送
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/msg.h>
        int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
msgid：由msgget函数返回的消息队列标识码<br>
msgp：指针指向准备发送的消息<br>
msgze：msgp指向的消息的长度（不包括消息类型的long int长整型）<br>
msgflg：默认为0<br>
返回值：成功返回0，失败返回-1<br>
#### 消息队列的控制
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/msg.h>
        int msgctl(int msqid, int cmd, struct msqid_ds *buf);
msqid：由msgget函数返回的消息队列标识码<br>
cmd：有三个可选的值，在此我们使用IPC_RMID<br>
IPC_STAT 把msqid_ds结构中的数据设置为消息队列的当前关联值<br>
IPC_SET 在进程有足够权限的前提下，把消息队列的当前关联值设置为msqid_ds数据结构中给出的值<br>
IPC_RMID 删除消息队列<br>
#### 消息队列的接受
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/msg.h>
        ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
msgsz：缓冲区长度，如果返回的长度大于缓冲区长度，且在flag中设置了MSG_NOERROR，则消息会被截断。如果没有设置，出错返回E2BUG（消息还在队列中）<br>
msgtyp == 0；返回队列中的第一个消息；<br>
msgtyp > 0； 返回队列中类型为type的第一个消息；<br>
msgtyp < 0； 返回队列中消息类型值小于等于type绝对值的消息；如果有若干个，则取类型值最小的信息。<br>

### 信号量
#### 信号量的创建
        #include <sys/sem.h>
        int semget(key_t key,int nsems,int flags)；
key:为键，是信号量的一种标识符;<br>
nsems：是该集合种的信号量数。如果是创建新集合（一般在服务器进程种），则必定指定nsems。如果是引用现有集合（一个客户进程），则将nsems指定为0;<br>
flags:IPC_CREAT<br>
#### 信号量的控制
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/sem.h>
        int semctl(int semid, int semnum, int cmd, union semun arg)
semid：信号量集标识符<br>
semnum：信号量集数组上的下标，表示某一个信号量<br>
cmd：见下表<br>
arg：<br>
        union semun {<br>
        short val;          /*SETVAL用的值*/<br>
        struct semid_ds* buf; /*IPC_STAT、IPC_SET用的semid_ds结构*/<br>
        unsigned short* array; /*SETALL、GETALL用的数组值*/<br>
        struct seminfo *buf;   /*为控制IPC_INFO提供的缓存*/<br>
        } arg;<br>
命令                    解释<br>
IPC_STAT                从信号量集上检索semid_ds结构，并存到semun联合体参数的成员buf的地址中<br>
IPC_SET                 设置一个信号量集合的semid_ds结构中ipc_perm域的值，并从semun的buf中取出值<br>
IPC_RMID                从内核中删除信号量集合<br>
GETALL                  从信号量集合中获得所有信号量的值，并把其整数值存到semun联合体成员的一个指针数组中<br>
GETNCNT                 返回当前等待资源的进程个数<br>
GETPID                  返回最后一个执行系统调用semop()进程的PID<br>
GETVAL                  返回信号量集合内单个信号量的值<br>
GETZCNT                 返回当前等待100%资源利用的进程个数<br>
SETALL                  与GETALL正好相反<br>
SETVAL                  用联合体中val成员的值设置信号量集合中单个信号量的值<br>
#### 信号量的P操作/V操作
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/sem.h>
        int semop(int semid, struct sembuf *sops, unsigned nsops)
sops：指向进行操作的信号量集结构体数组的首地址，此结构的具体说明如下：<br>
struct sembuf {<br>
short semnum;   /*信号量集合中的信号量编号，0代表第1个信号量*/<br>
short val;      /*若val>0进行V操作信号量值加val，表示进程释放控制的资源 */<br>
                /*若val<0进行P操作信号量值减val，若(semval-val)<0（semval为该信号量值），则调用进程阻塞，直到资源可用；若设置IPC_NOWAIT不会睡眠，进程直接返回EAGAIN错误*/<br>
                /*若val==0时阻塞等待信号量为0，调用进程进入睡眠状态，直到信号值为0；若设置IPC_NOWAIT，进程不会睡眠，直接返回EAGAIN错误*/<br>
short flag;     /*0 设置信号量的默认操作*/<br>
                /*IPC_NOWAIT设置信号量操作不等待*/<br>
                /*SEM_UNDO 选项会让内核记录一个与调用进程相关的UNDO记录，如果该进程崩溃，则根据这个进程的UNDO记录自动恢复相应信号量的计数值*/<br>
};<br>
nsops：进行操作信号量的个数，即sops结构变量的个数，需大于或等于1。最常见设置此值等于1，只完成对一个信号量的操作<br>
