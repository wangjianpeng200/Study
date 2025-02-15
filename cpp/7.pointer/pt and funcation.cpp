//当为值传递，形参不影响实参
//当为地址传递时，可以改变实参
#include<iostream>
using namespace std;
/*
void swap(int *p,int *p1)
{
    int temp=*p;
    *p=*p1;
    *p1=temp;
}

int main()//d当使用指针时，地址传递可以修饰实参
{
    int a=10;
    int b=20;
    swap(&a,&b);
    cout<<a<<"    "<<b<<endl;
    system("pause");
}
*/

int main()
{
    int a=10;
    int *p=&a;
    cout<<"a的地址为:"<<p<<endl;
    cout<<"a的地址为:"<<&a<<endl;
    cout<<"a的值为:"<<*p<<endl;
    cout<<"指针的地址为："<<&p<<endl;

}