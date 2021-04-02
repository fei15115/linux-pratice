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

## 线程控制

### 线程属性

#### 初始化以及反初始化函数
__int pthread_attr_init(pthread_attr_t *attr);__<br>
__int pthread_attr_destory(pthread_attr_t *attr);__<br>

#### 基本操作1.线程分离状态
__int pthread_attr_setdetachstate(pthread_attr_t *tattr,int detachstate);__<br>
__int pthread_attr_getdetachstate(const pthread_attr_t *tattr,int *detachstate)__<br>
**PTHREAD_CREATE_DETACHED**<br>
分离线程没有被其他的线程所等待，自己运行结束了，线程也就终止了，马上释放系统资源。应该根据自己的需要，选择适当的分离状态<br>
**PTHREAD_CREATE_JOINABLE**<br>
线程的默认属性是非分离状态，这种情况下，原有的线程等待创建的线程结束。只有当pthread_join()函数返回时，创建的线程才算终止，才能释放自己占用的系统资源。<br>
如果设置一个线程为分离线程，而这个线程运行又非常快，它很可能在pthread_create函数返回之前就终止了，它终止以后就可能将线程号和系统资源移交给其他的线程使用，这样调用pthread_create的线程就得到了错误的线程号。要避免这种情况可以采取一定的同步措施，最简单的方法之一是可以在被创建的线程里调用pthread_cond_timewait函数，让这个线程等待一会儿，留出足够的时间让函数pthread_create返回。设置一段等待时间，是在多线程编程里常用的方法。但是注意不要使用诸如wait()之类的函数，它们是使整个进程睡眠，并不能解决线程同步的问题。<br>
__int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);__<br>
__int pthread_attr_getguardsize(const pthread_attr_t *attr, size_t *guardsize);__<br>

#### 基本操作2.设置栈溢出保护区大小
__int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);__<br>
__int pthread_attr_getguardsize(const pthread_attr_t *attr, size_t *guardsize);__<br>
出于以下两个原因，为应用程序提供了guardsize 属性：<br> 
■ 溢出保护可能会导致系统资源浪费。如果应用程序创建大量线程，并且已知这些线程永远不会溢出其栈，则可以关闭溢出保护区。通过关闭溢出保护区，可以节省统资源。 <br>
■ 线程在栈上分配大型数据结构时，可能需要较大的溢出保护区来检测栈溢出。guardsize 参数提供了对栈指针溢出的保护。如果创建线程的栈时使用了保护功能，则实现会在栈的溢出端分配额外内存。此额外内存的作用与缓冲区一样，可以防止栈指针的栈溢出。如果应用程序溢出到此缓冲区中，这个错误可能会导致SIGSEGV信号被发送给该线程。<br>
如果guardsize 为零，则不会为使用attr 创建的线程提供溢出保护区。如果guardsize 大于零，则会为每个使用attr 创建的线程提供大小至少为guardsize 字节的溢出保护区。缺省情况下，线程具有实现定义的非零溢出保护区。允许合乎惯例的实现，将guardsize 的值向上舍入为可配置的系统变量PAGESIZE 的倍数。请参见sys/mman.h 中的PAGESIZE。如果实现将guardsize 的值向上舍入为PAGESIZE的倍数，则以guardsize（先前调用pthread_attr_setguardsize()时指定的溢出保护区大小）为单位存储对指定attr pthread_attr_getguardsize()的调用。<br>


#### 基本操作3.设置线程竞争范围
__int pthread_attr_setscope(pthread_attr_t *tattr,int scope);__<br>
__int pthread_attr_getscope(pthread_attr_t *tattr, int *scope);__<br>

将scope配置为PTHREAD_SCOPE_SYSTEM时，此线程将与系统中的所有线程进行竞争。<br>
将scope配置为PTHREAD_SCOPE_PROCESS时，此线程将与该进程中的所有线程进行竞争。<br>

#### 基本操作4.设置线程并行等级
__int pthread_setconcurrency(int new_level);__<br>
__int pthread_getconcurrency(void);__<br>
pthread_setconcurrency 返回值 <br>
如果出现以下情况，pthread_setconcurrency()将失败： <br>
        EINVAL <br>
        描述: new_level 指定的值为负数。<br> 
        EAGAIN <br>
        描述: new_level 指定的值将导致系统资源不足。<br>
pthread_getconcurrency返回值 <br>
pthread_getconcurrency() 始终会返回先前调用pthread_setconcurrency() 时设置的并发级别。如果从未调用pthread_setconcurrency()，则pthread_getconcurrency()将返 
回零。<br>

#### 基本操作5.设置调度策略
__int pthread_attr_setschedpolicy(pthread_attr_t *tattr, int policy);__<br>
__int pthread_attr_getschedpolicy(pthread_attr_t *tattr, int *policy);__<br>
POSIX 标准指定SCHED_FIFO（先入先出）、SCHED_RR（循环）或SCHED_OTHER（实现定义的方法）的调度策略属性。 <br>
■ SCHED_FIFO <br>
如果调用进程具有有效的用户ID 0，则争用范围为系统(PTHREAD_SCOPE_SYSTEM) 的先入先出线程属于实时(RT) 调度类。如果这些线程未被优先级更高的线程抢占，则会继续处理该线程，直到该线程放弃或阻塞为止。对于具有进程争用范围(PTHREAD_SCOPE_PROCESS) 的线或其调用进程没有有效用户ID 0 的线程，请使用SCHED_FIFO。SCHED_FIFO基于TS 调度类。 <br>
■SCHED_RR <br>
如果调用进程具有有效的用户ID 0，则争用范围为系统(PTHREAD_SCOPE_SYSTEM) 的循环线程属于实时(RT) 调度类。如果这些线程未被优先级更高的线程抢占，并且这些线程没有放弃或阻塞，则在系统确定的时间段内将一直执行这些线程。对于具有进程争用范围(PTHREAD_SCOPE_PROCES) 的线程，请使用SCHED_RR（基于TS 调度类）。此外，这些线程的调用进程没有有效的用户ID 0。<br>

SCHED_FIFO 和SCHED_RR 在POSIX 标准中是可选的，而且仅用于实时线程。<br>

#### 基本操作6.设置继承的调度策略
__int pthread_attr_setinheritsched(pthread_attr_t *tattr, int inherit);__<br>
__int pthread_attr_getinheritsched(pthread_attr_t *tattr, int *inherit);__<br>
inherit 值PTHREAD_INHERIT_SCHED 表示新建的线程将继承创建者线程中定义的调度策略。将忽略在pthread_create() 调用中定义的所有调度属性。如果使用缺省值PTHREAD_EXPLICIT_SCHED，则将使用pthread_create() 调用中的属性。<br>


#### 基本操作7.设置调度参数
__int pthread_attr_setschedparam(pthread_attr_t *tattr,const struct sched_param *param);__<br>
__int pthread_attr_getschedparam(pthread_attr_t *tattr,const struct sched_param *param);__<br>
                pthread_attr_t tattr;<br>
                pthread_t tid;<br>
                int ret;<br>
                int newprio = 20;<br>
                sched_param param; <br>
                
                /* initialized with default attributes */
                ret = pthread_attr_init (&tattr);
                /* safe to get existing scheduling param */
                ret = pthread_attr_getschedparam (&tattr, &param);
                /* set the priority; others are unchanged */
                param.sched_priority = newprio;
                /* setting the new scheduling param */
                ret = pthread_attr_setschedparam (&tattr, &param);
                /* with new priority specified */
                ret = pthread_create (&tid, &tattr, func, arg);

#### 基本操作8.设置栈大小
__int pthread_attr_setstacksize(pthread_attr_t *tattr,size_t size);__<br>
__int pthread_attr_getstacksize(pthread_attr_t *tattr,size_t *size);__<br>
                #include <pthread.h>
                pthread_attr_t tattr;
                size_t size;
                int ret; 
                size = (PTHREAD_STACK_MIN + 0x4000); 
                
                /* setting a new size */
                ret = pthread_attr_setstacksize(&tattr, size);
要获取对栈大小的绝对最小限制，请调用宏PTHREAD_STACK_MIN。PTHREAD_STACK_MIN 宏将针对执行NULL 过程的线程返回所需的栈空间量。有用的线程所需的栈大小大于最小栈大小，因此缩小栈大小时应非常谨慎。<br>
#### 基本操作8.设置栈地址和大小
__int pthread_attr_setstack(pthread_attr_t *tattr,void *stackaddr,size_t stacksize);__<br>
__int pthread_attr_getstack(pthread_attr_t *tattr,void * *stackaddr,size_t *stacksize);__<br>
                #include <pthread.h>
                pthread_attr_t tattr;
                pthread_t tid;
                int ret;
                void *stackbase;
                size_t size; 
                
                /* initialized with default attributes */
                ret = pthread_attr_init(&tattr);
                /* setting the base address and size of the stack */
                ret = pthread_attr_setstack(&tattr, stackbase,size);
                /* address and size specified */  
                ret = pthread_create(&tid, &tattr, func, arg);
stackaddr 属性定义线程栈的基准（低位地址）。stacksize 属性指定栈的大小。如果将stackaddr 设置为非空值，而不是缺省的NULL，则系统将在该地址初始化栈，假设大小为stacksize。 <br>
base 包含新线程使用的栈的地址。如果base 为NULL，则pthread_create(3C)将为大小至少为stacksize 字节的新线程分配栈。<br>

### 互斥量属性

#### 互斥量属性的初始化和反初始化
__int pthread_mutexattr_init(pthread_mutexattr_t *attr);__
__int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);__

#### 设置互斥量共享属性
__int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr,int *pshared);__  
__int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,int pshared);__
pshared的取值可以是： **PTHREAD_PROCESS_SHARED**，**PTHREAD_PROCESS_PRIVATE**
说明：如果互斥锁属性对象的pshared属性被置**PTHREAD_PROCESS_SHARED**。那么由这个属性对象创建的互斥锁将被保存在共享内存中，可以被多个进程中的线程共享。<br>
如pshared属性被置为**PTHREAD_PROCESS_PRIVATE**，那么只有和创建这个互斥锁的线程在同一个进程中的线程才能访问这个互斥锁。<br>

#### 设置互斥量基本属性
__int pthread_mutexattr_settype(pthread_mutexattr_t *attr,int kind);__  
__int pthread_mutexattr_gettype(pthread_mutexattr_t *attr,int *kind);__
PTHREAD_MUTEX_DEFAULT(缺省的互斥锁类型属性)：这种类型的互斥锁不会自动检测死锁。如果一个线程试图对一个互斥锁重复锁定，将会引起不可预料的结果。如果试图解锁一个由别的线程锁定的互斥锁会引发不可预料的结果。如果一个线程试图解锁已经被解锁的互斥锁也会引发不可预料的结果。POSIX标准规定，对于某一具体的实现，可以把这种类型的互斥锁定义为其他类型的互斥锁。<br> 
PTHREAD_MUTEX_NORMAL：这种类型的互斥锁不会自动检测死锁。如果一个线程试图对一个互斥锁重复锁定，将会引起这个线程的死锁。如果试图解锁一个由别的线程锁定的互斥锁会引发不可预料的结果。如果一个线程试图解锁已经被解锁的互斥锁也会引发不可预料的结果。<br>
PTHREAD_MUTEX_ERRORCHECK：这种类型的互斥锁会自动检测死锁。 如果一个线程试图对一个互斥锁重复锁定，将会返回一个错误代码。 如果试图解锁一个由别的线程锁定的互斥锁将会返回一个错误代码。如果一个线程试图解锁已经被解锁的互斥锁也将会返回一个错误代码。<br>
PTHREAD_MUTEX_RECURSIVE：如果一个线程对这种类型的互斥锁重复上锁，不会引起死锁。一个线程对这类互斥锁的多次重复上锁必须由这个线程来重复相同数量的解锁，这样才能解开这个互斥锁，别的线程才能得到这个互斥锁。如果试图解锁一个由别的线程锁定的互斥锁将会返回一个错误代码。如果一个线程试图解锁已经被解锁的互斥锁也将会返回一个错误代码。这种类型的互斥锁只能是进程私有的（作用域属性为PTHREAD_PROCESS_PRIVATE）。<br>

#### 设置互斥锁协议
__int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol);__  
__int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol);__  
PTHREAD_PRIO_NONE：线程的优先级和调度不会受到互斥锁拥有权的影响。<br>
PTHREAD_PRIO_INHERIT：当高优先级的等待低优先级的线程锁定互斥量时，低优先级的线程以高优先级线程的优先级运行。这种方式将以继承的形式传递。当线程解锁互斥量时，线程的优先级自动被将到它原来的优先级。（“优先级继承”意味着，当一个线程在由另一个低优先级线程拥有的互斥量上等待时，后者的优先级将被增加到等待线程的优先级.) <br>
PTHREAD_PRIO_PROTECT：拥有该类型的互斥量的线程将以自己的优先级和它拥有的互斥量的线程将以自己的优先级和它拥有的互斥量的优先级较高者运行，其他等待该线程拥有的锁得线程对该线程的调度优先级没有影响。<br>
注意：PTHREAD_PRIO_INHERIT 和 PTHREAD_PRIO_PROTECT 只有在采用实时调度策略SCHED_FIFO 或SCHED_RR的优先级进程内可用。<br>
一个线程可以同时拥有多个混合使用PTHREAD_PRIO_INHERIT 和PTHREAD_PRIO_PROTECT协议属性初始化的互斥锁。在这种情况下,该线程将以通过其中任一协议获取的最高优先级执行。pthread_mutexattr_getprotocol可用来获取互斥锁属性对象的协议属性。<br>
#### 设置互斥锁属性对象的优先级上限属性
__int pthread_mutexattr_setprioceiling(pthread_mutexatt_t *attr, int prioceiling, int *oldceiling);__  
__int pthread_mutexattr_getprioceiling(const pthread_mutexatt_t *attr, int *prioceiling);__
prioceiling指定已初始化互斥锁的优先级上限。优先级上限定义执行互斥锁保护的临界段时的最低优先级。prioceiling 位于SCHED_FIFO 所定义的优先级的最大范围内。要避免优先级倒置,请将prioceiling 设置为高于或等于可能会锁定特定互斥锁的所有线程的最高优先级。oldceiling 用于返回以前的优先级上限值。<br>
    pthread_mutex_setprioceiling可更改互斥锁mutex的优先级上限prioceiling。<br>
    pthread_mutex_setprioceiling可锁定互斥锁(如果未锁定的话),或者一直处于阻塞状态,直到它成功锁定该互斥锁,更改该互斥锁的优先级上限并将该互斥锁释放为止。锁定互斥锁的过程无需遵循优先级保护协议。<br>
    如果 pthread_mutex_setprioceiling成功,则将在 old_ceiling 中返回以前的优先级上限值。如果pthread_mutex_setprioceiling失败,则互斥锁的优先级上限保持不变。pthread_mutex_getprioceiling会返回mutex 的优先级上限prioceiling。<br>
注意：“优先级上限”协议意味着当一个线程拥有互斥量时，它将以指定的优先级运行<br>

#### 设置互斥锁的强健属性
__int pthread_mutexattr_setrobust_np(pthread_mutexattr_t *attr, int *robustness);__<br>
__int pthread_mutexattr_getrobust_np(const pthread_mutexattr_t *attr, int *robustness);__ <br>
robustness 定义在互斥锁的持有者“死亡”时的行为。pthread.h 中定义的robustness 的值为PTHREAD_MUTEX_ROBUST_NP 或 PTHREAD_MUTEX_STALLED_NP。缺省值为PTHREAD_MUTEX_STALLED_NP。<br>

PTHREAD_MUTEX_STALLED_NP： 如果互斥锁的持有者死亡,则以后对pthread_mutex_lock() 的所有调用将以不确定的方式被阻塞。<br>
PTHREAD_MUTEX_ROBUST_NP： 如果互斥锁的持有者“死亡”了，或者持有这样的互斥锁的进程unmap了互斥锁所在的共享内存或者持有这样的互斥锁的进程执行了exec调用，则会解除锁定该互斥锁。互斥锁的下一个持有者将获取该互斥锁,并返回错误EOWNWERDEAD。<br>
如果互斥锁具有PTHREAD_MUTEX_ROBUST_NP的属性，则应用程序在获取该锁时必须检查pthread_mutex_lock 的返回代码看获取锁时是否返回了EOWNWERDEAD错误。如果是，则互斥锁的新的持有者应使该互斥锁所保护的状态保持一致。因为互斥锁的上一个持有者“死亡”时互斥锁所保护的状态可能出于不一致的状态。如果互斥锁的新的持有者能够使该状态保持一致,请针对该互斥锁调用pthread_mutex_consistent_np(),并解除锁定该互斥锁。如果互斥锁的新的持有者无法使该状态保持一致,请勿针对该互斥锁调用pthread_mutex_consistent_np(),而是解除锁定该互斥锁。所有等待的线程都将被唤醒,以后对pthread_mutex_lock() 的所有调用都将无法获取该互斥锁。返回错误为ENOTRECOVERABLE。如果一个线程获取了互斥锁，但是获取时得到了EOWNERDEAD的错误，然后它终止并且没有释放互斥锁 ,则下一个持有者获取该锁时将返回代码EOWNERDEAD。<br>

### 读写锁属性

#### 读写锁属性的初始化和反初始化
__int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);__
__int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);__
#### 设置互斥量共享属性
__int pthread_rwlockattr_setpshared(pthread_rwlockattr_t  *attr,int  pshared);__  
__int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t  *attr,int *pshared);__
__PTHREAD_PROCESS_SHARED__
    描述:允许可访问用于分配读写锁的内存的任何线程对读写锁进行处理。即使该锁是在由多个进程共享的内存中分配的，也允许对其进行处理。
__PTHREAD_PROCESS_PRIVATE__
    描述:读写锁只能由某些线程处理，这些线程与初始化该锁的线程在同一进程中创建。如果不同进程的线程尝试对此类读写锁进行处理，则其行为是不确定的。由进程共享的属性的缺省值为 __PTHREAD_PROCESS_PRIVATE__。

### 条件变量属性

#### 条件变量属性的初始化和反初始化
__int pthread_condattr_init(pthread_condattr_t  *attr);__
__int pthread_condattr_destroy(pthread_condattr_t  *attr);__
#### 设置互斥量共享属性
__int pthread_condattr_getpshared(const pthread_condattr_t *restrict attr,int *restrict pshared);__  
__int pthread_condattr_setpshared(pthread_condattr_t *attr,int pshared);__
__PTHREAD_PROCESS_SHARED__
    描述:允许可访问用于分配读写锁的内存的任何线程对读写锁进行处理。即使该锁是在由多个进程共享的内存中分配的，也允许对其进行处理。
__PTHREAD_PROCESS_PRIVATE__
    描述:读写锁只能由某些线程处理，这些线程与初始化该锁的线程在同一进程中创建。如果不同进程的线程尝试对此类读写锁进行处理，则其行为是不确定的。由进程共享的属性的缺省值为 __PTHREAD_PROCESS_PRIVATE__。