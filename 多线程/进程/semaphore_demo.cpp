#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// 信号量操作函数
void semaphore_operation(int semid, int op) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

int main() {
    key_t key;
    int semid;
    pid_t pid;
    union semun arg;
    
    // 生成唯一的key
    key = ftok("semfile", 65);
    
    // 创建信号量
    semid = semget(key, 1, 0666 | IPC_CREAT);
    
    // 初始化信号量值为1
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    
    pid = fork();
    
    if (pid > 0) {
        // 父进程
        cout << "Parent process waiting for semaphore..." << endl;
        semaphore_operation(semid, -1); // P操作
        cout << "Parent process entered critical section" << endl;
        
        sleep(2); // 模拟临界区操作
        
        cout << "Parent process leaving critical section" << endl;
        semaphore_operation(semid, 1); // V操作
        
        // 等待子进程结束
        wait(NULL);
        
        // 删除信号量
        semctl(semid, 0, IPC_RMID);
    } else {
        // 子进程
        sleep(1); // 等待父进程先执行
        cout << "Child process waiting for semaphore..." << endl;
        semaphore_operation(semid, -1); // P操作
        cout << "Child process entered critical section" << endl;
        
        sleep(2); // 模拟临界区操作
        
        cout << "Child process leaving critical section" << endl;
        semaphore_operation(semid, 1); // V操作
    }
    
    return 0;
}