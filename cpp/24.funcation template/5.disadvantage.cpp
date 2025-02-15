//模板的局限性,有一些特定数据类型，需要用具体化方式做特殊实现
//使用具体化的方式   template<>+具体化的函数
#include<iostream>
using namespace std;

class person
{
    public:
    string m_name;
    int m_age;
    person(string name,int age)
    {
        this->m_name=name;
        this->m_age=age;
    }
};

template<class T>
bool myCompare(T &a,T &b)
{
    if(a==b)
    {
        return true;
    }
    else{
        return false;
    }
}
//利用具体化的person版本实现代码，具体化优先调用
template<> bool myCompare(person &p1,person &p2)
{
    if(p1.m_name==p2.m_name&&p1.m_age==p2.m_age)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void test01()
{
    int a=10;
    int b=20;
    bool ret =myCompare(a,b);
    if(ret)
    {
        cout<<"a==b"<<endl;
    }
    else
    {
        cout<<"a!=b"<<endl;
    }
}

//自定义数据类型的区分
void test02()
{
   person p1("wjp",21);
   person p2("wjp",21); 
   bool ret=myCompare(p1,p2);//自定义数据类型无法实现
   if(ret)
    {
        cout<<"a==b"<<endl;
    }
    else
    {
        cout<<"a!=b"<<endl;
    }
}

int main()
{
    test02();
    system("pause");
    return 0;
}