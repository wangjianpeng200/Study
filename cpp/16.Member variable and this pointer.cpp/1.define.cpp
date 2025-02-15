/*
成员变量和成员函数分开存储:
1.在C++中，类内的成员变量和成员函数分开存储
2.只有非静态成员变量才属于类的对象上
*/

#include<iostream>
using namespace std;

class person
{
    public:
    int m_a;
    static int m_b;//不属于类的对象上，所以不占用类的空间
    void funca()//非静态成员函数不属于类的对象
    {

    }
    static void funca1()//静态成员函数也不属于类的对象
    {

    }
};
int person::m_b=100;

void test01()
{
    //空对象占用空间为1个字节
    //C++编译器会给每一个空对象也分配一个空间，是为了区分空对象占内存的位置
    //每一个空对象也应该有一个独一无二的地址
    person p;
    cout<<"p占用的空间为:"<<sizeof(p)<<endl;
}

int main()
{
   test01();
   system("pause");
   return 0;
}