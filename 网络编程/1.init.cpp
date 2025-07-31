#include <iostream>
#include <thread>
#include <unistd.h>     // close(), sleep()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>      // memset

void test()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);   //创建一个套接字
    /*
        domain：协议族，常用 AF_INET（IPv4）或 AF_INET6（IPv6）
        type：套接字类型，SOCK_STREAM（TCP）、SOCK_DGRAM（UDP）
        protocol：协议，通常设为 0，表示使用默认协议
    */

    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);  //将套接字和本地地址绑定
    /*
        sockfd：由 socket() 返回的套接字描述符
        addr：指向 sockaddr_in 或 sockaddr_in6 的指针
        addrlen：地址结构的长度
    */
    int listen(int sockfd, int backlog);   //将套接字设置为监听状态（TCPTCP）
    /*
        sockfd：由 socket() 返回的套接字描述符
        backlog：连接请求队列的最大长度
    */

    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); //接受客户端的连接请求
    /*
        sockfd：由 socket() 返回的套接字描述符
        addr：指向 sockaddr_in 或 sockaddr_in6 的指针,用于接收客户端的地址
        addrlen：地址结构的长度
    */

    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); //客户端连接服务器
    /*
        sockfd：由 socket() 返回的套接字描述符
        addr：指向 sockaddr_in 或 sockaddr_in6 的指针,用于接收客户端的地址
        addrlen：地址结构的长度
    */
    
}



void serverFunction() {
    // - server_fd 仅用于监听连接请求
    // - new_socket 专门处理当前客户端通信
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 创建 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return;
    }

    // 设置地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  //允许服务器接收所有网卡的连接请求
    address.sin_port = htons(8080);

    // 绑定
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        close(server_fd);
        return;
    }

    // 监听
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        close(server_fd);
        return;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // 接受连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {    //接收连接，返回的是soket描述符
        std::cerr << "Accept failed!" << std::endl;
        close(server_fd);
        return;
    }

    // 接收数据
    read(new_socket, buffer, 1024);
    std::cout << "Received from client: " << buffer << std::endl;

    // 发送响应
    const char* response = "Hello from server";
    send(new_socket, response, strlen(response), 0);

    // 清理资源
    close(new_socket);
    close(server_fd);
}

void clientFunction() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // 创建 socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    // 设置服务器地址
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // 将 IPv4 地址从字符串转换为网络字节序
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        close(sock);
        return;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        close(sock);
        return;
    }

    // 发送数据
    const char* message = "Hello from client";
    send(sock, message, strlen(message), 0);

    // 接收响应
    read(sock, buffer, 1024);
    std::cout << "Received from server: " << buffer << std::endl;

    // 清理资源
    close(sock);
}
