#include<iostream>
using namespace std;

class person
{
    public:
    int m_a;
    int m_b;
    person()
    {
        cout<<"构造函数的调用"<<endl;
    }
    person(person &p)
    {
        m_a=p.m_a;
        m_b=p.m_b;
        cout<<"的拷贝函数的调用"<<endl;
    }
};

void test01(person p)
{
    cout<<"新创建的p.m_a="<<p.m_a<<endl;
    cout<<"新创建的p.m_a="<<p.m_b<<endl;
}

int main()
{
    person p;
    p.m_a=10;
    p.m_b=20;
    test01(p);
    system("pause");
    return 0;
}