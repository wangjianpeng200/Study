//空指针：指针变量指向内存中编号为0的空间
//用途：初始化指针变量
//空指针指向的内存是不可以访问的
/*
int main()
{
    int *p=null;
    访问空指针报错，内存编号0-255为系统所用，不允许用户访问
}
*/

#include<iostream>
using namespace std;

int main()
{
    int *p=NULL;
    //*p=100;空指针不能进行访问
    system("pause");
    return 0;
}