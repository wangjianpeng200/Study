#include<iostream>
using namespace std;

class phone
{
    public:
    string p_name;
    int p_number;
    phone(string name,int number)
    {
        p_name=name;
        p_number=number;
    }
};

class person
{
    public:
    string m_name;
    static int ID;
    phone m_phone;
    person(string name,string pname,int a):m_name(name),m_phone(pname,a)
    {

    }
};

int person::ID=51068;

void test01()
{
    person p("王健棚","华为",13550);
    cout<<p.m_name<<"   "<<p.m_phone.p_name<<"    "<<p.m_phone.p_number<<"    "<<p.ID<<endl;
}
int main()
{
    test01();
    cout<<person::ID<<endl;
    system("pause");
    return 0;
}