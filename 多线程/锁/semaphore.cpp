// 信号量主要用于进程和线程之间的同步和互斥,实际上是一个非负的证书计数器，当信号量大于0时可以访问
#include <semaphore.h>

sem_t sem;

int sem_init(sem_t *sem, int pshared, unsigned int value); //
// 参数:
// sem：信号量变量地址
// pshared：
// 0：线程同步
// 非0：进程同步
// value：初始化当前信号量拥有的资源数（>=0），如果资源数为0，线程就会被阻塞了
int sem_destroy(sem_t *sem);

// 信号量减一
int sem_wait(&sem);
int sem_trywait(&sem);
// 信号量加一
int sem_post(&sem);
// 获取信号量的值
sem_getvalue(&sem);




void semaphore_test()
{
    // 生产者线程
    sem_t psem;
    // 消费者线程
    sem_t csem;

    // 信号量初始化
    sem_init(&psem, 0, 5); // 5个生产者可以同时生产
    sem_init(&csem, 0, 0); // 消费者线程没有资源, 因此不能消费

    // 生产者线程
    // 在生产之前, 从信号量中取出一个资源
    sem_wait(&psem);
    // 生产者商品代码, 有商品了, 放到任务队列
    ..................
        // 通知消费者消费，给消费者信号量添加资源，让消费者解除阻塞
        sem_post(&csem);

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    // 消费者线程
    // 消费者需要等待生产, 默认启动之后应该阻塞
    sem_wait(&csem);
    // 开始消费
    ..................
        // 消费完成, 通过生产者生产，给生产者信号量添加资源
        sem_post(&psem)
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

// 链表的节点
struct Node
{
    int number;
    struct Node* next;
};

// 生产者线程信号量
sem_t psem;
// 消费者线程信号量
sem_t csem;

// 互斥锁变量
pthread_mutex_t mutex;
// 指向头结点的指针
struct Node * head = NULL;

// 生产者的回调函数
void* producer(void* arg)
{
    // 一直生产
    while(1)
    {
        // 生产者拿一个信号灯
        sem_wait(&psem);
        // 加锁, 这句代码放到 sem_wait()上边, 有可能会造成死锁
        pthread_mutex_lock(&mutex);
        // 创建一个链表的新节点
        struct Node* pnew = (struct Node*)malloc(sizeof(struct Node));
        // 节点初始化
        pnew->number = rand() % 1000;
        // 节点的连接, 添加到链表的头部, 新节点就新的头结点
        pnew->next = head;
        // head指针前移
        head = pnew;
        printf("+++producer, number = %d, tid = %ld\n", pnew->number, pthread_self());
        pthread_mutex_unlock(&mutex);

        // 通知消费者消费
        sem_post(&csem);
        
        // 生产慢一点
        sleep(rand() % 3);
    }
    return NULL;
}

// 消费者的回调函数
void* consumer(void* arg)
{
    while(1)
    {
        sem_wait(&csem);//
        pthread_mutex_lock(&mutex);
        struct Node* pnode = head;
        printf("--consumer: number: %d, tid = %ld\n", pnode->number, pthread_self());
        head  = pnode->next;
        // 取出链表的头结点, 将其删除
        free(pnode);
        pthread_mutex_unlock(&mutex);
        // 通知生产者生成, 给生产者加信号灯
        sem_post(&psem);

        sleep(rand() % 3);
    }
    return NULL;
}

int main()
{
    // 初始化信号量
    sem_init(&psem, 0, 5);  // 生成者线程一共有5个信号灯
    sem_init(&csem, 0, 0);  // 消费者线程一共有0个信号灯
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建5个生产者, 5个消费者
    pthread_t ptid[5];
    pthread_t ctid[5];
    for(int i=0; i<5; ++i)
    {
        pthread_create(&ptid[i], NULL, producer, NULL);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_create(&ctid[i], NULL, consumer, NULL);
    }

    // 释放资源
    for(int i=0; i<5; ++i)
    {
        pthread_join(ptid[i], NULL);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_join(ctid[i], NULL);
    }

    sem_destroy(&psem);
    sem_destroy(&csem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
