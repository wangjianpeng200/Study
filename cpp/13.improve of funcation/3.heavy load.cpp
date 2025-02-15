//函数名可以想用，提高复用性
/*
函数重载满足条件
1.同一个作用域下；
2.函数名称相同
3.函数参数类型不同或者个数不同，或者顺序不同
注：函数的返回值不可以作为函数重载的条件
*/
#include<iostream>
using namespace std;

//函数重载的满足条件

void funca(double a)
{
    cout<<"funca"<<endl;
}

void funca(int a)
{
    cout<<"funca(int a)!"<<endl;
}

int main()
{
    double a=10;
    funca(10.000);
    system("pause");
    return 0;
}