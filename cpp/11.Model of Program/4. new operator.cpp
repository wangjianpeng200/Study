//new在堆区中开辟数据
//可以利用操作符delete释放

#include<iostream>
using namespace std;

//1.new的基本语法
int* func()
{
    //在堆区创建整型数据
    //new返回的是该数据的地址，所以必须用指针接收
    int *p=new int(10);
    return p;
}


void func2()
{
    //创建10整型数据的数组，在堆区中
    int *arr=new int[10];//10代表数组里有10个元素

    for(int i=0;i<10;i++)
    {
        arr[i]=i+100;//给10个元素赋值100-109
    }
    for(int j=0;j<10;j++)
    {
        cout<<arr[j]<<endl;
    }
    //释放堆区数组
    delete[] arr;//加上中括号
}
int main()
{
    int *p=func();
    cout<<"创建的堆区为："<<*p<<endl;
    //如果想要释放堆区的数据可以用关键字delete
    delete p;
    cout<<*p<<endl;
    func2();
    system("pause");
    return 0;
}

//int *p=new int(10);
//int *arr=new int[10];