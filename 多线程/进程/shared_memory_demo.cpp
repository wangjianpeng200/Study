#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    key_t key;
    int shmid;
    char *shm_ptr;
    pid_t pid;
    
    // 生成唯一的key
    key = ftok("shmfile", 65);
    
    // 创建共享内存
    shmid = shmget(key, 1024, 0666|IPC_CREAT);
    
    pid = fork();
    
    if (pid > 0) {
        // 父进程：写入数据
        // 连接共享内存
        shm_ptr = (char*) shmat(shmid, (void*)0, 0);
        
        // 写入数据
        strcpy(shm_ptr, "Hello from parent process!");
        cout << "Parent wrote to shared memory: Hello from parent process!" << endl;
        
        // 分离共享内存
        shmdt(shm_ptr);
        
        // 等待子进程读取
        sleep(1);
        
        // 删除共享内存
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        // 子进程：读取数据
        sleep(1); // 等待父进程写入
        
        // 连接共享内存
        shm_ptr = (char*) shmat(shmid, (void*)0, 0);
        
        // 读取数据
        cout << "Child read from shared memory: " << shm_ptr << endl;
        
        // 分离共享内存
        shmdt(shm_ptr);
    }
    
    return 0;
}