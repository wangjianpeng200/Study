//select
//poo
//epoll


/*
select 原理与实现流程
核心数据结构
    select 依赖内核中的 fd_set 位图结构（本质是固定长度的数组），用于标记监听的文件描述符（fd）状态：
    读集合（readfds）、写集合（writefds）、异常集合（exceptfds）：每个集合用一个位图表示，每一位对应一个 fd。
    最大文件描述符（maxfd）：用于确定遍历范围（从 0 到 maxfd）。
关键系统调用与流程
    select(nfds, readfds, writefds, exceptfds, timeout)
    参数：nfds 是最大 fd + 1，后三个参数是传入传出的位图指针，timeout 控制阻塞时间。
核心流程：
    用户态准备：用户将需要监听的 fd 按事件类型（读 / 写 / 异常）填入对应的 fd_set 位图。
内核态处理：.
    内核遍历位图中所有标记为 1 的 fd（从 0 到 maxfd），检查每个 fd 是否就绪（如是否有数据可读）。
    若有就绪 fd，内核修改位图（仅保留就绪的 fd），并返回就绪的 fd 数量。
    用户态处理：用户根据返回的位图，逐个检查哪些 fd 就绪，再进行数据读写。
select 的局限性
    fd 数量限制：受限于 fd_set 位图的大小（通常为 1024），无法处理高并发场景。
    效率低下：每次调用都需遍历所有监听的 fd（O (n) 时间复杂度），当 fd 数量大时性能急剧下降。
    内核与用户态拷贝开销：每次调用都需将 fd 集合从用户态拷贝到内核态，再将结果拷贝回用户态。
    位图修改问题：内核会修改传入的位图（仅保留就绪 fd），用户态需每次重新设置位图，增加编程复杂度。
*/


/*
    poll 改进了 select 的 fd 数量限制，使用 pollfd 数组存储监听的 fd 和事件：
    pollfd 结构体：
    c
    struct pollfd {
        int fd;                  // 文件描述符
        short events;            // 监听的事件（如 POLLIN）
        short revents;           // 就绪的事件（由内核填充）
    };
*/

/*
eventpoll 结构体
    内核中 epoll 的核心管理结构，包含：
    红黑树（rbr）：存储所有已注册的 socket 连接（文件描述符 fd），用于快速查找和管理。
    双向链表（rdlist）：存储已就绪（有数据可读 / 可写）的 socket，避免遍历所有连接。
    等待队列（wq）：当调用epoll_wait时，进程在此阻塞，直到有事件触发

epitem 结构体
    红黑树节点与双向链表节点的综合体，包含：
        指向 socket 的文件描述符 fd 和事件信息（如读 / 写事件）。
        双向链表指针，用于加入 rdlist。
        回调函数指针（ep_poll_callback），用于事件触发时将节点加入 rdlist。

1. epoll_create：创建 epoll 实例
    操作：调用epoll_create()时，内核分配一个eventpoll结构体，初始化空的红黑树和双向链表，并返回文件描述符epfd。
    本质：创建一个内核对象，用于管理后续注册的 socket 连接。
2. epoll_ctl：注册、修改或删除 socket 事件
    参数：epoll_ctl(epfd, op, fd, event)，其中op为操作类型（ADD/MOD/DEL），fd为目标 socket 的文件描述符，event为监听事件（如 EPOLLIN）。
    核心流程：
        ADD 操作：检查fd是否已注册，若未注册则创建epitem结构体,将epitem插入红黑树，并将ep_poll_callback回调函数绑定到fd对应的 socket。
        回调函数的作用： 当 socket 有数据到达时，内核自动调用该函数，将epitem加入eventpoll的rdlist链表，并唤醒等待队列中的进程。
        DEL/MOD 操作： 从红黑树中删除或修改节点。
3. epoll_wait：等待事件就绪
    操作：调用epoll_wait(epfd, events, maxevents, timeout)时，进程进入阻塞状态。
    核心流程：
        将当前进程加入eventpoll的等待队列wq。
        内核检查rdlist链表，若有就绪事件（如 socket 数据到达），则将事件从rdlist拷贝到用户空间的events数组中，并返回事件数量。
        若rdlist为空，则进程阻塞，直到：
            有 socket 事件触发（通过ep_poll_callback回调）；
            超时（timeout非零）；
            被信号中断。

1. epoll_create() → 创建eventpoll（含红黑树+rdlist+等待队列）
2. epoll_ctl(ADD) → 将socket fd插入红黑树，绑定回调函数
3. 数据到达socket → 内核调用回调函数，将epitem加入rdlist    ，就算没有调用epoll_wait也会一直更新。这是内核态的行为、

数据包 → 网卡DMA → 内核协议栈 → socket接收队列
         ↓
  唤醒等待队列（调用ep_poll_callback）
         ↓
  从socket等待队列项获取epitem
         ↓
  将epitem加入rdlist

4. epoll_wait() → 从rdlist获取就绪事件，返回给用户态     
5. 用户态处理数据 → 调用read/write操作
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
//水平触发 

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 10);
 
 
    int epoll_fd = epoll_create1(0);
    struct epoll_event event, events[10];
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);
 
 
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == listen_fd) {
                int client_fd = accept(listen_fd, NULL, NULL);
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
            } else {
                int client_fd = events[i].data.fd;
                char buffer[1024];
                int n = read(client_fd, buffer, sizeof(buffer));
                if (n > 0) {
                    // 处理数据，无需考虑是否读完，因为只要有数据可读，下次 epoll_wait 还会通知
                    write(1, buffer, n);
                } else if (n == 0) {
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                }
            }
        }
    }
 
 
    close(epoll_fd);
    close(listen_fd);
    return 0;
}



//边缘触发
int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 10);
 
 
    int epoll_fd = epoll_create1(0);
    struct epoll_event event, events[10];
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);
 
 
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == listen_fd) {
                int client_fd = accept(listen_fd, NULL, NULL);
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
            } else {
                int client_fd = events[i].data.fd;
                char buffer[1024];
                int n = read(client_fd, buffer, sizeof(buffer));
                if (n > 0) {
                    // 处理数据，无需考虑是否读完，因为只要有数据可读，下次 epoll_wait 还会通知
                    write(1, buffer, n);
                } else if (n == 0) {
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                }
            }
        }
    }
 
 
    close(epoll_fd);
    close(listen_fd);
    return 0;
}


