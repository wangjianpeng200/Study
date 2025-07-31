#include<unistd.h>
using namespace std;

//匿名管道：用完即销毁
//命名管道：提前创建的管道文件，可以不相关的进程间通信



int pipe(int pipefd[2]);  //创建无名管道

