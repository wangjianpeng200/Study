//作用：给变量起别名
//语法：数据类型 &别名=原名
//引用必须初始化
//引用一旦初始化后就不能该改变
#include<iostream>
using namespace std;

int main()
{
    int a=10;
    int &b=a;//操作语法
    int c=20;
    b=c;
    cout<<"a:"<<a<<endl;
    cout<<"b:"<<b<<endl;
    cout<<"c:"<<c<<endl;
    system("pause");
}