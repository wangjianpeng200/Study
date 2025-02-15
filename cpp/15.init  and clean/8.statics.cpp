/*
静态成员：
静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为:
静态成员变量
    1.所有对象共享同一份数据
    2.在编译阶段分配内存（程序还没有生前就分配内存）
    3.类内声明，类外初始化
静态成员函数
    1.所有对象共享同一个函数
    2.静态成员函数只能访问静态成员变量
*/

#include<iostream>
#include<string>
using namespace std;

class person
{
    public:
    static int m_a;//类内声明，类外初始化
};

int person::m_a=100;//类外声明

void test01()
{
    person p;
    cout<<p.m_a<<endl;

    person p2;
    p2.m_a=200;
    cout<<p.m_a<<endl;
};

void test02()
{
    person p;
    //静态对象不属于某一个对象，所有对象都共享一份数据
    //因此有两种不同的访问方式

    //1.通过对象进行访问
    cout<<p.m_a<<endl;

    //2.通过类名进行访问
    cout<<person::m_a<<endl;//因为共用一份数据
}

int main()
{
    //test01();
}