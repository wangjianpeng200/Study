//赋值运算符重载

/*
c++编译器至少给一个类添加4个函数
1.默认构造函数(无参，函数体为空)
2.默认析构函数(无参，函数体为空)
3.默认拷贝构造函数，对属性进行值拷贝
4.赋值运算符 operator=,对属性进行值拷贝
如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝问题
*/

#include<iostream>
using namespace std;

//赋值运算符重载

class person
{
    public:
    person(int age)
    {
        m_age=new int(age);
    }
    person& operator=(person &p)//如果返回的是值，就是按照自身调用拷贝构造函数再创造一个*this
    {
        //编译器提供的是浅拷贝

        //判断是否有属性在堆区，如果有先释放干净
        if(m_age!=NULL)
        {
            delete m_age;
            m_age=NULL;
        }
        m_age=new int(*p.m_age);//深拷贝的操作
        return *this;
    }
    int *m_age;
    ~person()
    {
        if(m_age!=NULL)
        {
            delete m_age;
            m_age-NULL;
        } 
    }
};

void test01()
{
    person p1(21);
    person p2(20);
    person p3(30);
    //赋值运算的操作，类似于隐式转换法,浅拷贝，简单的值copy
    p2=p1=p3;//p1=p3后不能返回void
    cout<<"p1的年龄为:"<<*p1.m_age<<endl;
    cout<<"p2的年龄为:"<<*p2.m_age<<endl;
}


int main()
{
    test01();






    int a=10;
    int b=20;
    int c=30;
    c=b=a;//运算符赋值是从右到左
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
    cout<<"c="<<c<<endl;
}