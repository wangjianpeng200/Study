/*
函数定义的五个步骤
1.返回值的类型
2.函数名
3.参数列表
4.函数体语句
5.return表达式

返回值类型 函数名（参数列表）、
{
    函数体语句

    return 表达式
}
*/

//实现一个加法函数，功能：传入两个整型数据,计算数据相加的结果，并且返回

#include<iostream>
using namespace std;

int add(int num1,int num2)
{
    int sum=num1+num2;
    return sum;
}

int main()
{
    //a,b有实际的值为实参，num1,num2为形参
    int a=0;
    int b=0;
    cout<<"请输入需要求和的值："<<endl;
    cin>>a>>b;
    //调用add函数
    //函数调用语法：函数名称（参数）
    //调用函数时，实参的值会传递给形参
    int c=add(a,b);//调用函数2
    cout<<"求和的值为："<<c<<endl;
    system("pause");
    return 0;
}



