/*
1.this指针概念
在C++中成员变量和成员函数是分开存储的
每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

那么问题是:这一块代码是如何区分那个对象调用自己的呢?
c++通过提供特殊的对象指针，this指针，解决上述问题。
this指针指向被调用的成员函数所属的对象
this指针是隐含每一个非静态成员函数内的一种指针
this指针不需要定义，直接使用即可

this指针的用途:
当形参和成员变量同名时，可用this指针来区分
在类的非静态成员函数中返回对象本身，可使用return *this
*/

#include<iostream>
using namespace std;

class person
{
    public:
    person(int age)
    {
        this->age=age;//this指针指向的是被调用的成员函数所属的对象
    }

     person& personadd(person &p)
    {
        this->age+=p.age;
        return *this;//用引用的方式返回，返回的才是原来的p2，不会创建新的p
    }
    int age;
};
//解名称冲突
void test01()
{
    person p(10);
    cout<<"年龄为:"<<p.age<<endl;
}

void test02()
{
    person p1(10);
    person p2(20);
    //p2.personadd(p1);
    p2.personadd(p1).personadd(p1).personadd(p1);
    cout<<"p2的年龄为:"<<p2.age<<endl;//链式编程思想
}

 int main()
 {
    test02();
    system("pause");
    return 0;
 }