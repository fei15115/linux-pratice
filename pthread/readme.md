# Just do some pratice with the pthread.

# 线程函数的一些简单应用
## 注意事项
    在进行编译的时候记得链接库 “-lpthread”
    使用的是<pthread.h>
    
## 线程的创建和退出
###    pthread_t 线程ID
        类似于进程的pid_t一样，用一个不同于整形的数据类型来表示一个线程。
        可以通过 **int pthread_equal(pthread_t a,pthread_t b)；** 来进行比较
        可以通过 **pthread_t pthread_self(void);** 来获取

###    pthread_create 线程创建
        **int pthread_create(pthread_t *tidp, const pthread_attr_t *attr,void *(*start_rtn)(void *),void *arg);**

###    pthread_exit(void *ptr); 线程的终止
        ex. **pthread_exit((void *)1);

