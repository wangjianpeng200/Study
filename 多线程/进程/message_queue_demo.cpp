#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// 消息结构体
struct message_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;  //用于生成消息队列的唯一标识符
    int msgid;  //消息队列的标识符
    pid_t pid;  //进程ID
    
    // 生成唯一的key
    key = ftok("progfile", 65);
    
    // 创建消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    pid = fork(); //创建子进程
    
    if (pid > 0) {
        // 父进程：发送消息
        // 设置消息类型
        message.msg_type = 1;
        // 复制消息内容
        strcpy(message.msg_text, "Hello from parent process!");
        
        // 发送消息
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        
        cout << "Parent sent message: " << message.msg_text << endl;
        
        // 等待子进程读取
        sleep(1);
        
        // 删除消息队列
        msgctl(msgid, IPC_RMID, NULL);
    } else {
        // 子进程：接收消息
        // 接收消息
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        cout << "Child received message: " << message.msg_text << endl;
    }
    
    return 0;
}





//posix发送消息队列
#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

const char* QUEUE_NAME = "/my_message_queue";
const int QUEUE_SIZE = 10;      // 最大消息数
const int MAX_MSG_SIZE = 256;   // 消息最大长度

int main() {
    // 设置消息队列属性
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = QUEUE_SIZE;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // 创建消息队列（如果不存在则创建）
    mqd_t queue = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (queue == (mqd_t)-1) {
        std::cerr << "Failed to create/open queue: " << strerror(errno) << std::endl;
        return 1;
    }

    // 发送消息
    char message[] = "Hello from sender process!";
    if (mq_send(queue, message, strlen(message) + 1, 0) == -1) {
        std::cerr << "Failed to send message: " << strerror(errno) << std::endl;
        return 1;
    }
    
    std::cout << "Message sent: " << message << std::endl;

    // 关闭消息队列
    if (mq_close(queue) == -1) {
        std::cerr << "Failed to close queue: " << strerror(errno) << std::endl;
        return 1;
    }

    return 0;
}


//posix接收消息队列
#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

const char* QUEUE_NAME = "/my_message_queue";
const int MAX_MSG_SIZE = 256;

int main() {
    // 尝试打开消息队列（等待队列创建）
    mqd_t queue = -1;
    int attempts = 0;
    const int MAX_ATTEMPTS = 10;
    
    while (queue == -1 && attempts < MAX_ATTEMPTS) {
        queue = mq_open(QUEUE_NAME, O_RDONLY);
        if (queue == (mqd_t)-1) {
            std::cerr << "Queue not found, retrying... (" << attempts + 1 << "/" << MAX_ATTEMPTS << ")" << std::endl;
            sleep(1);  // 等待1秒后重试
            attempts++;
        }
    }

    if (queue == (mqd_t)-1) {
        std::cerr << "Failed to open queue after " << MAX_ATTEMPTS << " attempts" << std::endl;
        return 1;
    }

    // 接收消息
    char buffer[MAX_MSG_SIZE];
    unsigned int priority;
    ssize_t msg_size = mq_receive(queue, buffer, MAX_MSG_SIZE, &priority);
    
    if (msg_size == -1) {
        std::cerr << "Failed to receive message: " << strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "Message received: " << buffer << std::endl;

    // 关闭消息队列
    if (mq_close(queue) == -1) {
        std::cerr << "Failed to close queue: " << strerror(errno) << std::endl;
        return 1;
    }

    // 删除消息队列（可选，确保清理）
    if (mq_unlink(QUEUE_NAME) == -1) {
        std::cerr << "Failed to unlink queue: " << strerror(errno) << std::endl;
        return 1;
    }

    return 0;
}