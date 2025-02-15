#include<iostream>
using namespace std;
//函数重载的注意事项

//1.引用作为重载的条件
void func(int &a)
{
    cout<<"func(int &a)调用"<<endl;
}

void func(const int &a)
{
    cout<<"func(const int &a)调用"<<endl;
}


//2.函数重载碰到默认参数
void func2(int a,int b=10)
{
    cout<<"func(int a,int b)调用"<<endl;
}

void func2(int a)
{
    cout<<"func(int a)调用"<<endl;
}



int main()
{
    //int a=20;
    //func(a);//调用没有const的函数，因为int &a可读可写
    //func(10);//调用const函数，因为&a=10不合法；但const &a=10，被转化为：int tem0=10;&a=temp
    func2(10,20);//当函数重载，碰到默认参数会容易出现二义性
    system("pause");
    return 0;
}