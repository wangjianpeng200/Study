#include<iostream>
using namespace std;

//引用做函数的返回值
//1.不要返回局部变量的引用

/*
int& test1()//用引用的方式进行返回
{
    int a=10;//局部变量存放在四区中的栈区
    return a;//返回的是a的别名
}*/

int& test2()//用引用的方式进行返回
{
    static int a=10;//静态变量存放在堆区中
    return a;//返回的是a的别名
}

int main()
{
   // int &ref=test1();
    //cout<<ref<<endl;//第一次结果正确，因为编译器做了保留
    //cout<<ref<<endl;//第二次结果错误，因为a的内存空间已经释放
    int &ref2=test2();
    cout<<ref2<<endl;
    cout<<ref2<<endl;
    test2()=1000;//返回的是a的引用，ref是a的别名，所以对返回值进行赋值，修改的是int a=1000；ref是a的别名 所以ref=1000
    //如果函数的返回值是引用，这个函数调用可以作为左值
    cout<<ref2<<endl;//因为此时
    cout<<ref2<<endl;
}