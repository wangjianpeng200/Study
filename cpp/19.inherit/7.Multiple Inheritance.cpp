/*
C++允许一个类继承多个类
语法:
继承方式 父类2...
class 子类 : 继承方式 父类1 ，
多继承可能会引发父类中有同名成员出现，需要加作用域区分

在c++的实际开发中一般不使用多继承
*/
#include<iostream>
using namespace std;

class base1
{
    public:
    int m_a=100;
};

class base2
{
    public:
    int m_a=200;
};

class son:public base1,public base2
{
    public:
    son()
    {
        m_c=300;
        m_d=400;
    }
    int m_c;
    int m_d;
};

void test01()
{
    son s;
    cout<<"占用的内存空间"<<sizeof(s)<<endl;
    //当父类中出现了同名成员，需要加做用域区分
    cout<<"m_a="<<s.base2::m_a<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}