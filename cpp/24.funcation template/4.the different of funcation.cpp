#include<iostream>
using namespace std;
//普通函数与函数模板区别
//1、普通函数调用可以发生隐式类型转换
//2、函数模板 用自动类型推导，不可以发生隐式类型转换
//3、函数模板 用显示指定类型，可以发生隐式类型转换

//普通函数
int myAdd01(int a,int b)
{
    return a+b;
}

//模板函数
template<typename T>
T myAdd(T a,T b)
{
    return a+b;
}

void test01()
{
    int a=10;
    int b=20;
    char c='c';
    cout<<"a+b="<<myAdd01(a,b)<<endl;
    cout<<"a+b="<<myAdd01(a,c)<<endl;//将c隐式类型转换为int的数据类型
    ///cout<<"a+b="<<myAdd(a,c)<<endl;报错，因为模板函数不能进行隐式类型转换
    cout<<myAdd<int>(a,c)<<endl;//可以使用显示指定类型
}

int main()
{

}