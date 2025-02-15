/*

问题:继承中同名的静态成员在子类对象上如何进行访问?
静态成员和非静态成员出现同名，处理方式一致
1.访问子类同名成员 直接访问即可
2.访问父类同名成员 需要加作用域

*/

#include<iostream>
using namespace std;

class person
{
    public:
    static int m_a;
};

int person::m_a=100;

class son:public person
{
    public:
    int static m_a;
};

int son::m_a=200;

//同名的静态成员属性
void test01()
{
    //1.通过对象的方式访问
    cout<<"通过对象的方式访问"<<endl;
    son s;
    cout<<"son下的m_a"<<s.m_a<<endl;
    cout<<"person下的m_a"<<s.person::m_a<<endl;
    //2.通过类名的方式访问
    cout<<"通过类名的方式访问"<<endl;
    cout<<"son类下的m_a"<<son::m_a<<endl;
    cout<<"通过son类访问person下的m_a"<<son::person::m_a<<endl;

}

int main()
{
    test01();
    system("pause");
    return 0;

}