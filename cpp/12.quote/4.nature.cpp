//引用的本质是在c++中实现是一个常量指针

#include<iostream>
using namespace std;

void func(int& ref)
{
    ref=100;
}

int main()
{
    int a=10;
    int &ref=a;//自动化转化为 int * const ref=&a;指针常量，
    //所以指针指向不能修改，只有指针内的值可以修改（也说明了为什么引用不能修改）
    ref=20;//内存发现ref是引用，自动帮我们转化为：*ref=20；
    cout<<"a:"<<a;
    cout<<"ref:"<<ref;
    func(a);
    return 0;
}