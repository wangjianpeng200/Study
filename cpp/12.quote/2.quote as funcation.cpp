/*
2.3 引用做函数参数
作用:函数传参时，可以利用引用的技术让形参修饰实参
优点:可以简化指针修改实参
*/

#include<iostream>
using namespace std;

//交换函数

//值传递
void swap1(int a,int b)
{
    int temp=a;
    a=b;
    b=temp;
}

//地址传递
void swap2(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

//引用传递
void swap3(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}
int main()
{
    int a=10;
    int b=20;
    swap1(a,b);
    cout<<"a:"<<a<<"b:"<<b<<endl;
    swap2(&a,&b);
    cout<<"a:"<<a<<"b:"<<b<<endl;
    swap3(a,b);
    cout<<"a:"<<a<<"b:"<<b<<endl;
    system("pause");
    return 0;
}

void swap4(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}