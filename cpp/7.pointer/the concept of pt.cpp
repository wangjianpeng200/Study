//创建一个变量，保存另一个变量的地址
//通过一个指针来保存一个地址

#include<iostream>
using namespace std;

int main()
{
    int  a=10;
    //定义指针的语法： 数据类型*指针变量名；
    int *p;
    //让指针记录变量a的地址
    p=&a;
    cout<<"a的地址为:"<<&a<<endl;
    cout<<p<<endl;//指针记录的就是地址
    //使用指针可以通过解引用的方式来找到指针指向的内存
    //指针前加一个*等于解引用，指向指针所指向的内容
    *p=1000;
    cout<<"*p:"<<*p<<endl;
    cout<<"a:"<<a<<endl;

    cout<<endl;

    int b=10;
    int *s=&a;
    cout<<"b的地址为:"<<s<<endl;
    cout<<"b的地址为:"<<&b<<endl;
    cout<<"b的值为:"<<*s<<endl;
    cout<<"指针的地址为："<<&s<<endl;
}