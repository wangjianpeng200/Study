#include<iostream>
using namespace std;
//类模板成员函数类外实现

/*
//类内实现
template<class T1,class T2>
class person
{
    public:
    T1 m_name;
    T2 m_age;
    person(T1 name,T2 age)
    {
        this->m_name=name;
        this->m_age=age;
    }
    void show
    {
        cout<<"姓名："<<this->m_name<<"   年龄："<<this->m_age<<endl;
    }
};
*/

//类外实现
template<class T1,class T2>
class student
{
    public:
    T1 s_name;
    T2 s_id;
    student(T1 name,T2 id);
    void show();
};
template<class T1,class T2>
student<T1,T2>::student(T1 name,T2 id)
{
    this->s_name=name;
    this->s_id=id;
}
template<class T1,class T2>
void student<T1,T2>::show()
{
    cout<<"姓名："<<this->s_name<<"   学号："<<this->s_id<<endl;
}

void test01()
{
    student<string,int> s1("wjp",3121415);
    s1.show();
}

int main()
{
    test01();
    system("psuse");
    return 0;
}