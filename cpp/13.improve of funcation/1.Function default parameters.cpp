//在函数中，形参列表中的形参是可以有默认值的
//语法：返回值类型 函数名（参数名=默认值）{}
#include<iostream>
using namespace std;

int func(int a,int b=20,int c=30)
{
    return a+b+c;
}
//注意事项
//1.如果某个位置已经有了默认参数，那么从这个位置从左到右都必须有默认值int main()
//2.如果函数声明中有默认参数，函数实现就不能有默认参数
/*
int funca (int a=10;int b=20);//声明

int funca(int a=10;int b=20)//实现
{

}

*/
