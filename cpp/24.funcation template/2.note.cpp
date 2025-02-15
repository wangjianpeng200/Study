#include<iostream>
using namespace std;

//1.自动类型推导，必须推导出一致的数据类型T
//2.模板必须要确定出T的数据类型，才能使用
template<typename T>
void myswap(T &a,T &b)
{
    T temp=a;
    a=b;
    b=temp;
}

//1.自动类型推导，必须推导出一致的数据类型T
void test01()
{
    int a=10;
    int b=20;
    char c='ac';
    myswap(a,b);
    //func(); T的类型没有被确定
    //myswap(a,c);  a,c数据类型不一致，所以推导出的T的类型不同
}

//2.模板必须要确定出T的数据类型，才能使用
template<class T>
void func()
{
    cout<<"func调用"<<endl;
}

int main()
{

}