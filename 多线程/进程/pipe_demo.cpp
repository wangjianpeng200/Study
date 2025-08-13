#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    // 创建子进程
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    
    if (pid > 0) {
        // 父进程：写入数据
        close(pipefd[0]); // 关闭读端
        
        const char* msg = "Hello from parent process!";
        write(pipefd[1], msg, strlen(msg)+1);
        
        close(pipefd[1]); // 关闭写端
        wait(NULL); // 等待子进程结束
    } else {
        // 子进程：读取数据
        close(pipefd[1]); // 关闭写端
        
        read(pipefd[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;
        
        close(pipefd[0]); // 关闭读端
    }
    
    return 0;
}