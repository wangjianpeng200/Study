#include <iostream>
#include <pthread.h>
using namespace std;

//pthread_t pthread_self(void);
//pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//pthread_joint     //线程回收，子线程退出时资源被回收，防止资源占用，当主线程调用pthread_join()函数后，它会被阻塞，直到指定的子线程执行完毕。
//pthread_detach(pthread_t thread);     //线程分离，子线程退出时资源不被回收，防止资源占用
//pthread_exit()   //退出线程，不影响其他线程的使用






void test_function()
{
    pthread_t pthread_self();
    for (int i = 0; i < 10; i++)
    {
        cout << "test_function" << i << endl;
    }
    return;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, test_function, NULL);
    pthread_join(tid, NULL);
    return 0;
}