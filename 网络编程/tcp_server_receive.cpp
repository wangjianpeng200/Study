#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // 创建套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "创建套接字失败" << std::endl;
        return -1;
    }

    // 设置服务器地址信息
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // 端口号
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有可用IP地址

    // 绑定地址信息
    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "绑定地址失败" << std::endl;
        close(server_fd);
        return -1;
    }

    // 监听连接
    if (listen(server_fd, 3) == -1) {
        std::cerr << "监听连接失败" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "服务端已启动，等待客户端连接..." << std::endl;

    // 接受客户端连接
    sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_size);
    if (client_fd == -1) {
        std::cerr << "接受连接失败" << std::endl;
        close(server_fd);
        return -1;
    }

    // 接收数据
    char buffer[1024] = {0};
    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        std::cout << "接收到客户端数据: " << buffer << std::endl;
    } else {
        std::cerr << "接收数据失败" << std::endl;
    }

    // 关闭套接字
    close(client_fd);
    close(server_fd);
    return 0;
}