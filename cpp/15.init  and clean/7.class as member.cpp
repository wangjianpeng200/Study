//C++类中的成员可以是另一个类的对象，我们称该成员为对象成员
#include<iostream>
#include<string>
using namespace std;


class phone
{
    public:
    string m_pname;
    phone(string name)
    {
        cout<<"phone 构造函数调用"<<endl;
        m_pname=name;
    }
    ~phone()
    {
        cout<<"phone析构函数的调用"<<endl;
    }
};

class person
{
    public:
    string m_name;
    phone m_phone;
    //phone m_phone=pname隐式转换法
    person(string name,string pname):m_name(name),m_phone(pname)
    {
        cout<<"person构造函数调用"<<endl;
    }
    ~person()
    {
        cout<<"person析构函数的调用"<<endl;
    }
};
//当其他类对象作为本类的成员，先构造类的对象，再构造自身
//析构的顺序与构造相反
void test01()
{
    person p("张三","iphone14pro");
    cout<<p.m_name<<"拿着"<<p.m_phone.m_pname<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}