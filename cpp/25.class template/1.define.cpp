#include<iostream>
using namespace std;

template<class nametype,class agetype>
class person
{
    public:
    nametype m_name;
    agetype m_age;
    person(nametype name,agetype age)
    {
        this->m_name=name;
        this->m_age=age;
    }
};

void test01()
{
    person<string,int>p1("孙悟空",999);
    person<int,int>p2(21,18);
    cout<<"name="<<p1.m_name<<"   "<<"age="<<p1.m_age<<endl;
    cout<<"name="<<p2.m_name<<"   "<<"age="<<p2.m_age<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}

//类模板中成员函数创建时机
//类模板中成员函数在调用时才去创建

class person1
{
    public:
    void showperson1()
    {
        cout<<"person1 show"<<endl;
    }
};

class person2
{
    public:
    void showperson2()
    {
        cout<<"person2 show"<<endl;
    }
};

template<class T>
class Myclass
{
    public:
    T obj;//obj是将T的类实例化
    void func1()
    {
        obj.showperson1();
    }
    void func2()
    {
        obj.showperson2();
    }
};//类模板中的成员函数在调用时才创建
//在实例化时，并没有创建（构造）

void test02()
{
    Myclass<person1> m;//将类模板的数据类型
    m.func1();
}
