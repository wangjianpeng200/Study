//占位参数
//返回值类型 函数名(数据类型 数据名，数据类型)
#include<iostream>
using namespace std;

//目前阶段的占位参数，我们还用不到，后面的课程中会用到
//占位参数 还可以有默认参数
void funca(int a,int=10)
{
    cout<<"this is placehoder parameter funcation"<<endl;
}

int main()
{
    int a=10;
    int b=20;
    funca(a,b);//b没有传递进去
}