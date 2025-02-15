#include<iostream>
using namespace std;

int main()
{
    //在32位操作系统下：指针占用4个字节空间
    //在64位操作系统下：指针占用8个字节空间
    int a=10;
    int *p=&a;//创建指向a的指针
    cout<<"指针占用空间："<<sizeof(int *)<<endl;
    cout<<"指针占用空间："<<sizeof(float *)<<endl;
    cout<<"指针占用空间："<<sizeof(double *)<<endl;

}