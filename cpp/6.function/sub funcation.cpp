/* 
1.创建后缀名为.h 的头文件
2.创建后缀名为.cpp的源文件
3.在头文件中写函数的声明
4.在源文件中写函数的定义
*/
/*

#include<iostream>
using namespace std;

//函数的分文件，实现两个数字进行交换的函数

void swap(int a,int b);//函数的声明
void swap(int a,int b)
{
    cout<<"交换前的值"<<endl<<"a="<<a<<"   b="<<b<<endl;
    int temp=a;
    a=b;
    b=temp;
    cout<<"交换后的值"<<endl<<"a="<<a<<"   b="<<b<<endl;
}

int main()
{
    cout<<"请输入a和b的值:"<<endl;
    int a=0;
    int b=0;
    cin>>a>>b;
    swap(a,b);
}
*/
#include<iostream>
#include"swap.h"
using namespace std;

int main()
{
    cout<<"请输入a和b的值:"<<endl;
    int a=0;
    int b=0;
    cin>>a>>b;
    swap(a,b);
    system("pause");
}