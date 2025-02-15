#include<iostream>
using namespace std;

/*
拷贝构造函数调用时机
C++中拷贝构造函数调用时机通常有三种情况：
1.使用一个已经创建完毕的对象来初始化一个新对象
2.值传递的方式给函数参数传值
3.以值方式返回局部对象
*/

class person
{
    public:
    person()
    {
        cout<<"默认函数"<<endl;
    }


    person(int a)
    {
        m_age=a;
        cout<<"有参函数"<<endl;
    }

    person(const person &p)
    {
        m_age=p.m_age;
        cout<<"拷贝函数"<<endl;
    }

    ~person()
    {
        cout<<"析构函数"<<endl;
    }

    int m_age;
};

void test01()
{
    person p1;
    person p2(10);
    person p3(p2);
    cout<<"该值为："<<p3.m_age<<endl;
}

void dowork(person p)
{

}

int main()
{
    person p2(10);
    dowork(p2);
    system("pause");
    return 0;
}