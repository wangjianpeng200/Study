#include <iostream>
using namespace std;

// 在全局中只存在该类的一个实例化对象，并且提供一个全局访问点。
// 所以通常屏蔽调拷贝构造函数和运算符重载，使用静态成员变量和函数实现
//返回的实例是静态成员变量所以只有一个拷贝，共享
//双检+懒汉式实现单例模式，线程安全

class Singleton
{
public:
    Singleton(const Singleton &) = delete;  //删除拷贝构造函数和赋值运算符重载，防止复制实例
    Singleton &operator=(const Singleton &) = delete;
    static Singleton *GetInstance()
    {
        return instance;
    }

private:
    Singleton() = default; // 默认构造函数
    static Singleton *instance; // 静态成员变量，在类外初始化
    static int count;           // 计数器，记录实例化次数
};

// 在类外初始化静态成员变量
Singleton *Singleton::instance = new Singleton();
int Singleton::count = 0;

int main()
{
    Singleton *s1 = Singleton::GetInstance(); // 得到唯一的单例对象
}




// 饿汉模式：在类加载的时候立刻进行实例化，这样就得到了一个唯一的可用对象。关于这个饿汉模式的类的定义如下
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        return m_taskQ;
    }
private:
    TaskQueue() = default;
    static TaskQueue* m_taskQ;
};
// 静态成员初始化放到类外部处理
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;

int main()
{
    TaskQueue* obj = TaskQueue::getInstance();
}



// 懒汉模式
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        if(m_taskQ == nullptr)
        {
            m_taskQ = new TaskQueue;
        }
        return m_taskQ;
    }
private:
    TaskQueue() = default;
    static TaskQueue* m_taskQ;
};
TaskQueue* TaskQueue::m_taskQ = nullptr;

