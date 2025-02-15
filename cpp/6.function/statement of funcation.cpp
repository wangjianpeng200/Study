#include<iostream>
using namespace std;

//函数声明
//比较函数，实现两个整型数字的比较，返回较大的值
//可以提前告诉编译器函数的存在，可以利用函数的声明
int compare(int a,int b);//提前声明函数
int main()
{
    int a=10;
    int b=20;
    cout<<compare(a,b)<<endl;
}

int compare(int a,int b)
{
    int num1=a>b?a:b;//  （表达式）？值：值
    return num1;
}
