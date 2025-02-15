#include<iostream>
using namespace std;

class person
{
    public:
    int m_a;
    int *m_b;
    person(int a,int b)
    {
        m_a=10;
        m_b=new int(b);
    }
    person& operator=(person &p)
    {
        if(m_b!=NULL)
        {
            delete m_b;
            m_b=NULL;
        }
        m_b=new int(*p.m_b);
         return *this;
    } 
};
void test01()
{
    person p1(10,20);
    person p2(20,30);
    p2=p1;
    *p2.m_b=100;
    cout<<"p1的m_a为:"<<p1.m_a<<"     "<<"p1的m_b为:"<<*p1.m_b<<endl;
    cout<<"p2的m_a为:"<<p2.m_a<<"     "<<"p2的m_b为:"<<*p2.m_b<<endl;
}
int main()
{
    test01();
    system("pause");
    return 0;
}