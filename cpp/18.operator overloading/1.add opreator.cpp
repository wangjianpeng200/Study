//运算符重载概念:对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型
#include<iostream>
using namespace std;

class person
{
    public:
    int m_a;
    int m_b;
    person(int a,int b):m_a(a),m_b(b)
    {
    }
};

/*
//1.全局函数重载+号
person operator+(person &p1,person &p2)
{
    person temp(p1.m_a+p2.m_a,p1.m_b+p2.m_b);
    return temp;
}
*/

//2.函数重载的版本
person operator+(person &p,int num)
{
    person temp(p.m_a+num,p.m_b+num);
    return temp;
}


int main()
{
    person p1(10,20);
    person p2(20,10);
    person p3=p1+3;
    cout<<"p3.m_a="<<p3.m_a<<"       "<<"p3.m_b"<<p3.m_b<<endl;
    system("pause");
    return 0;
}
//对于内置的数据类型的表达式的运算符是不可能改变的
//不要滥用运算符重载