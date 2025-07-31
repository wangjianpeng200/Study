#include <iostream>
using namespace std;

// 在全局中只存在该类的一个实例化对象，并且提供一个全局访问点。
// 所以通常屏蔽调拷贝构造函数和运算符重载，使用静态成员变量和函数实现
//返回的实例是静态成员变量所以只有一个拷贝，共享
//双检+懒汉式实现单例模式，线程安全

class Singleton
{
public:
    Singleton(const Singleton &) = delete;
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