#include<iostream>
using namespace std;

//值传递
//定义函数，实现两个数字交换
//如果一个函数不需要返回值，声明的时候可以写void
void swap(int num1,int num2) 
{
    cout<<"在交换前的数字为："<<endl;
    cout<<"num1="<<num1<<"    "<<"num2="<<num2<<endl;
    int temp=num1;
    num1=num2;
    num2=temp;
    cout<<"在交换后的数字为："<<endl;
    cout<<"num1="<<num1<<"    "<<"num2="<<num2<<endl;
    cout<<"num1的地址为:"<<&num1<<endl;
}
int main()
{
    int a=10;
    int b=14;
    swap(a,b);
    cout<<"a的地址为:"<<&a<<endl;
    //当我们做值传递时，函数的形参发生改变，并不会影响实参
    //num1,num2;a,b是分别占用内存空间
    cout<<"实参未改变"<<endl<<"num1="<<a<<"    "<<"num2="<<b<<endl;
    system("pause");
    return 0;
}