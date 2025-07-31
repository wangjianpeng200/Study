//线程同步

#include <iostream>
#include<pthread.h>
using namespace std;

int mutex()   //互斥锁
{
    pthread_mutex_t mutex;  //定义互斥锁
    int pthread_mutex_init(&mutex, NULL);  //初始化互斥锁
    int pthread_mutex_destroy(pthread_mutex_t *mutex); //摧毁
    int pthread_mutex_lock(pthread_mutex_t *mutex); //加锁 ，如果锁已经被锁定了，那么后面的线程将会阻塞在这里等待锁被释放
    int pthread_mutex_trylock(pthread_mutex_t *mutex); //尝试加锁，如果锁已经被锁定了，那么后面的线程将会立即返回错误码
    int pthread_mutex_unlock(pthread_mutex_t *mutex);
}

int rwlock()  //读写锁
{
    pthread_rwlock_t rwlock;  //定义读写锁
    // 锁的状态: 锁定/打开
    // 锁定的是什么操作: 读操作/写操作，使用读写锁锁定了读操作，需要先解锁才能去锁定写操作，反之亦然。
    // 哪个线程将这把锁锁上了
    int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
           const pthread_rwlockattr_t *restrict attr);   //读写锁初始化
    int pthread_rwlock_destroy(pthread_rwlock_t *rwlock); //摧毁
}



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define MAX 100
// 全局变量
int number;

// 创建一把互斥锁
// 全局变量, 多个线程共享
pthread_mutex_t mutex;
pthread_rwlock_t rwlock;  


// 线程处理函数
void* funcA_num(void* arg)
{
    for(int i=0; i<MAX; ++i)
    {
        // 如果线程A加锁成功, 不阻塞
        // 如果B加锁成功, 线程A阻塞
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        usleep(10);
        number = cur;
        pthread_mutex_unlock(&mutex);
        printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
    }

    return NULL;
}

void* funcB_num(void* arg)
{
    for(int i=0; i<MAX; ++i)
    {
        // a加锁成功, b线程访问这把锁的时候是锁定的
        // 线程B先阻塞, a线程解锁之后阻塞解除
        // 线程B加锁成功了
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        pthread_mutex_unlock(&mutex);
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
        usleep(5);
    }

    return NULL;
}

int main(int argc, const char* argv[])
{
    pthread_t p1, p2;

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建两个子线程
    pthread_create(&p1, NULL, funcA_num, NULL);
    pthread_create(&p2, NULL, funcB_num, NULL);

    // 阻塞，资源回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    // 销毁互斥锁
    // 线程销毁之后, 再去释放互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}



void cond()  //条件变量
{
    pthread_cond_t cond;   //定义条件变量
    pthread_mutex_t mutex;  //定义互斥锁
    pthread_cond_init(&cond, NULL);  //初始化条件变量
    pthread_cond_wait(&cond, &mutex);  //等待条件变量，阻塞在这里，直到被唤醒，会自动把拥有的
    //互斥锁解开，防止死锁
    pthread_cond_timewait(&cond, &mutex);  //等待条件变量，阻塞在这里，但是有时间限制
    // 唤醒阻塞在条件变量上的线程, 至少有一个被解除阻塞
    int pthread_cond_signal(pthread_cond_t *cond);
    // 唤醒阻塞在条件变量上的线程, 被阻塞的线程全部解除阻塞
    int pthread_cond_broadcast(pthread_cond_t *cond);














    pthread_cond_destroy(&cond);  //摧毁条件变量


}


