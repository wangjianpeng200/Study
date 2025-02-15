#include<iostream>
using  namespace std;

//继承中的构造和析构顺序
class base
{
    public:
    int m_a;
    base()
    {
        m_a=100;
    }
    void funca()
    {
        cout<<"base的函数调用"<<endl;
    }
  
};

class son:public base
{
    public:
    son()
    {
        m_a=200;
    }
    void funca()
    {
        cout<<"son的函数调用"<<endl;
    }
    int m_a; //如果和父类出现重名，则调用的时子类
};

//同名的成员属性调用
void test01()
{
    son s;
    cout<<"son的m_a为:    "<<s.m_a<<endl;
    cout<<"base的m_a为:   "<<s.base::m_a<<endl;//用作用域调用
    s.funca();
    s.base::funca();
}

//同名的成员函数调用


int main()
{
    test01();
    system("pause");
    return 0;
}