#include<iostream>
using namespace std;

//静态成员函数
//所有对象共享同一个函数
//静态成员函数只能访问静态成员变量

class person
{
    public:
    static void funca1()//静态成员函数
    {
        a=1000;//静态成员函数可以访问 静态函数变量
        //b=12;非静态成员变量不能被静态函数访问,无法区分到底是哪一个对象的a。
        cout<<"static的调用"<<endl;
    }

    void funca2()
    {
        b=100;
    }

    static int a;
    int b;
};

int person::a=100;
void test01()
{
    //1.通过对象调用
    person p;
    //p.funca();
    //2.通过类名调用
    person::funca1();
}

void test02()
{
    person p;
    p.funca2();
    cout<<p.b<<endl;

}
int main()
{
    //test01();
    test02();
    system("pause");
    return 0;
}