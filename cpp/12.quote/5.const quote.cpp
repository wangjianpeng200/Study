//常量引用主要用来修饰形参，防止误操作
//在函数形参列表中，可以加const修饰形参，防止形参改变实参

#include<iostream>
using namespace std;
//打印数据
void print(const int &val)//加入const后形参不能被修改
{
    //val=1000不能被修改
    cout<<"val="<<val<<endl;
}

int main()
{
    //常量引用
    //使用场景：用来修饰形参，防止误操作

    int a=10;
    print(a);
    //int &b=10;不合法
    //const int &b=10;//加上const后，编译器将代码修改为 int temp=10;int &ref=temp;
    //ref=20;加了const以后只读不能输入
    system("pause");
    return 0;
}