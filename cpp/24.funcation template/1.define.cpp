/*
C++另一种编程思想称为泛型编程，主要利用的技术就是模板
C++提供两种模板机制:函数模板和类模板
template<typename T>
template 声明创建模板
typename 表示后面是一种数据类型
*/

#include<iostream>
using namespace std;

//函数模板
//两个整型交换函数
void swapint(int &a,int &b)
{
    int temple=a;
    a=b;
    b=temple;
}
//交换浮点型函数

void swapdouble(double &a,double &b)
{
    double temple=a;
    a=b;
    b=temple;
}

//函数模板
template<typename T>//声明一个模板,T是通用数据类型
void myswap(T &a,T&b)
{
    T temple =a;
    a=b;
    b=temple;
}

void test01()
{
    int a=10;
    int b=20;
    //swapint(a,b);
    //利用函数模板交换
    //1.自动类型推导
    //myswap(a,b)
    //2.显示指定类型
    //myswap<int>(a,b)
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;

    double c=1.23;
    double d=8.88;
    swapdouble(c,d);
    cout<<"c="<<c<<endl;
    cout<<"d="<<d<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}