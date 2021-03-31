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

### 读写锁
#### 初始化以及清理函数
__int pthread_rwlock_init(pthread_rwlock_t * rwlock, const pthread_rwlockattr_t *  attr);__<br>
__int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);__<br>

#### 基本操作
__int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);__    读锁上锁，如果已经上锁会导致写锁阻塞，读锁不会有影响<br>
__int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);__    写锁上锁，会导致读锁和写锁都阻塞，保证了原子操作<br>
__int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);__    读写锁解锁<br>

### 自旋锁
#### 初始化以及清理函数
__int pthread_spin_destroy(pthread_spinlock_t *lock);__<br>
__int pthread_spin_init(pthread_spinlock_t *lock, int pshared);__<br>
如果想要使用自旋锁同步多进程，那么设置pshared=PTHREAD_PROCESS_SHARED，然后在进程共享内存中分配pthread_spinlock_t 对象即可（pthread_mutex_t亦如此）。<br>
两种锁适用于不同场景：<br>
如果是多核处理器，如果预计线程等待锁的时间很短，短到比线程两次上下文切换时间要少的情况下，使用自旋锁是划算的。<br>
如果是多核处理器，如果预计线程等待锁的时间较长，至少比两次线程上下文切换的时间要长，建议使用互斥量。<br>
如果是单核处理器，一般建议不要使用自旋锁。因为，在同一时间只有一个线程是处在运行状态，那如果运行线程发现无法获取锁，只能等待解锁，但因为自身不挂起，所以那个获取到锁的线程没有办法进入运行状态，只能等到运行线程把操作系统分给它的时间片用完，才能有机会被调度。这种情况下使用自旋锁的代价很高。<br>
如果加锁的代码经常被调用，但竞争情况很少发生时，应该优先考虑使用自旋锁，自旋锁的开销比较小，互斥量的开销较大。<br>

#### 基本操作
__int pthread_spin_lock(pthread_spinlock_t *lock);__<br>
__int pthread_spin_trylock(pthread_spinlock_t *lock);__<br>
__int pthread_spin_unlock(pthread_spinlock_t *lock);__<br>

### 屏障 线程间的同步机制

#### 初始化以及清理函数
__int pthread_barrier_init(pthread_barrier_t *restrict barrier,const pthread_barrierattr_t *restrict attr, unsigned count);__<br>
__int pthread_barrier_destroy(pthread_barrier_t *barrier);__<br>
在初始化时配置相应的count数，当有相应数目的线程调用wait时，阻塞接触，可以使多个线程并行。<br>
#### 基本操作
__int pthread_barrier_wait(pthread_barrier_t *barrier);__<br>




