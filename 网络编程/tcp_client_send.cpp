#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // 创建套接字
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        std::cerr << "创建套接字失败" << std::endl;
        return -1;
    }

    // 设置服务端地址信息
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);                   // 服务端端口
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务端IP地址

    // 连接服务端

    if (connect(client_fd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "连接服务端失败" << std::endl;
        close(client_fd);
        return -1;
    }

    // 发送数据
    const char *message = "Hello, Server!";
    if (send(client_fd, message, strlen(message), 0) == -1)
    {
        std::cerr << "发送数据失败" << std::endl;
    }
    else
    {
        std::cout << "发送成功: " << message << std::endl;
    }

    // 关闭套接字
    close(client_fd);
    return 0;
}