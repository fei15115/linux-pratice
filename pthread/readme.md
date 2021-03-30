# Just do some pratice with the pthread.

# 线程函数的一些简单应用
## 注意事项
    <br>在进行编译的时候记得链接库 “-lpthread”<br>
    <br>使用的是<pthread.h><br>

## 线程的创建和退出
###    线程ID pthread_t 
类似于进程的pid_t一样，用一个不同于整形的数据类型来表示一个线程。<br>
可以通过 __int pthread_equal(pthread_t a,pthread_t b);__ 来进行比较<br>
可以通过 __pthread_t pthread_self(void);__ 来获取<br>


###    线程创建 pthread_create 
__int pthread_create(pthread_t *tidp, const pthread_attr_t *attr,void *(*start_rtn)(void *),void *arg);__<br>
###    线程的终止 
__pthread_exit((void *)1);__                        线程结束并且返回相关的状态码<br>
__pthread_join(pthread_t tid,void **rval_ptr);__    等待指定的线程结束并且获取终止状态<br>
__int pthread_cancel(pthread_t tid);__              通过调用来取消同一进程中的其他线程<br>


## 线程同步
### 互斥锁
#### 初始化和清理函数
__int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexattr_t *attr)__ 或者 __pthread_t mutex=PTHREAD_MUTEX_INITIALIZER__ (只适用于静态分配的互斥量)<br>
__int pthread_mutex_destory(pthread_mutex_t *mutex)__
#### 基本操作
__int pthread_mutex_lock(pthread_mutex_t *mutex)__          对互斥量进行加锁，如果已经加锁，线程会阻塞到解锁为止。阻塞！<br>
__int pthread_mutex_trylock(pthread_mutex_t *mutex)__       尝试对互斥量加锁，如果没有加锁，则上锁。如果已经上锁，返回EBUSY。<br>
__int pthread_mutex_unlock(pthread_mutex_t *mutex)__        互斥量解锁。<br>
__int pthread_mutex_timeslock(pthread_mutex_t *mutex)__     几乎等价于lock，多了一个超时的时间，超时后返回ETIMEOUT。避免永久阻塞<br>

