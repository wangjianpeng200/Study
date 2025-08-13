# 进程间通信(IPC)方式详解

## 1. 管道(Pipe)

### 特点
- 最简单的IPC方式
- 半双工通信(数据只能在一个方向上流动)
- 只能用于具有亲缘关系的进程间通信
- 基于文件描述符

### 使用场景
- 父子进程间通信
- shell命令中的管道(|)

## 2. 消息队列(Message Queue)

### 特点
- 面向记录的通信方式
- 消息按顺序发送，但可以按类型读取
- 消息独立存在，不受进程调度影响
- 容量受限

### 使用场景
- 需要按优先级处理的消息
- 不同类型的进程间通信

## 3. 共享内存(Shared Memory)

### 特点
- 最快的IPC方式
- 多个进程共享同一块内存空间
- 需要同步机制防止竞争
- 生命周期随内核

### 使用场景
- 大量数据传输
- 高性能要求的应用

## 4. 信号量(Semaphore)

### 特点
- 用于进程间同步
- 原子操作
- 可以实现进程互斥和同步

### 使用场景
- 控制对共享资源的访问
- 进程同步

## 编译和运行

```bash
# 管道示例
g++ pipe_demo.cpp -o pipe_demo
./pipe_demo

# 消息队列示例
g++ message_queue_demo.cpp -o message_queue_demo
./message_queue_demo

# 共享内存示例
g++ shared_memory_demo.cpp -o shared_memory_demo
./shared_memory_demo

# 信号量示例
g++ semaphore_demo.cpp -o semaphore_demo
./semaphore_demo
```