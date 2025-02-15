/*
类模板实例化的对象，向函数传参的方式
1.指定传入的类型:直接显示对象的数据类型
2.参数模板化:将对象中的参数变为模板进行传递
3.整个类模板化:将这个对象类型模板化进行传递
*/

#include<iostream>
using namespace std;

template<class T1,class T2>
class person
{
    public:
    person(T1 name,T2 age)
    {
        this->m_name=name;
        this->m_age=age;
    }
    T1 m_name;
    T2 m_age;
    void showperson()
    {
        cout<<"姓名："<<this->m_name<<"   "<<"年龄："<<this->m_age<<endl;
    }
};

void show1(person<string,int> &p)
{
    p.showperson();
}
//1.直接显示对象的数据类型，指定数据类型
void test01()
{
    person<string,int>p1("洋芋片",21);
    show1(p1);
}
//2.参数模板化
template<class T1,class T2>
void show2(person<T1,T2> &p)
{
    p.showperson();
}
void test02()
{
    person<string,int> p2("土豆片",27);
    show2(p2);
}
//3.将整个类模板化
template<class T>
void show3(T &p)
{
    p.showperson();
    cout<<"T的数据类型:"<<typeid(T).name()<<endl;
}
void test03()
{
    person<string,int>p3("马铃薯片",30);
    show3(p3);
}
int main()
{
    test01();
    test02();
    test03();
    system("pause");
    return 0;
}