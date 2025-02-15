/*
int a
cout<<a<<endl;

person p;
m_a=10;
m_b=20
cout<<p<<endl;
*/


#include<iostream>
using namespace std;

class person
{
    friend ostream& operator<<(ostream& cout,person p);
    public:
    person(int a,int b):m_a(a),m_b(b)
    {

    }
    private:
    int m_a;
    int m_b;
    //通常不使用成员函数来进行左移运算符的重载
};

ostream& operator<<(ostream& cout,person p)//链式法，引用ostream
{
    cout<<"m_a="<<p.m_a<<"      "<<"m_b="<<p.m_b;
    return cout;
}

void test01()
{
    person p(10,20);
    cout<<p<<"      "<<"hello word"<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}