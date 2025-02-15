//重载关系运算符，可以让两个自定义对象进行对比操作

#include<iostream>
using namespace std;

class person
{
    public:
    person(string name,int age)
    {
        m_name=name;
        m_age=age;
    }
    bool operator==(person &p)
    {
        if((this->m_age==p.m_age)&&(this->m_name==p.m_name));
        {
            return false;
        }
        return true;
    }
    int m_age;
    string m_name;
};

void test01()
{
    person p1("tom",18);
    person p2("jim",21);
    cout<<p1.m_age<<"    "<<p1.m_name<<endl;
    cout<<p2.m_age<<"    "<<p2.m_name<<endl;
    if(p2==p1)//相当于p1在调用成员函数
    {
        cout<<"p1和p2相等"<<endl;
    }
    else
    {
        cout<<"p1和p2是不相等的"<<endl;
    }
}

int main()
{
    test01();
    system("pause");
    return 0;
}
