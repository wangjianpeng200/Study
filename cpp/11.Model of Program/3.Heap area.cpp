//由程序员分配释放，若程序员不释放，程序结束时由操作系统回收
//c++中利用new在堆区开辟内存

#include<iostream>
using namespace std;

int* func()
{
    int *p=new int(10);//利用new关键字，可以将数据开辟到堆区  new int(10)  new int(10)
    //指针，本质也是局部变量，放在栈上，指针保存的数据放在推上
    return p;
}

int main()
{
    //在堆区开辟数据
    int *p=func();
    cout<<"返回值为："<<*p<<endl;
    cout<<"返回值为："<<*p<<endl;
    system("pause");
    return 0;

}