/*

函数调用运算符重载:
函数调用运算符
由于重载后使用的方式非常像函数的调用，因此称为仿函数
仿函数没有固定写法，非常灵活

*/

#include<iostream>
using namespace std;

class Myadd
{
    public:
    int operator()(int v1,int v2)
    {
        return v1+v2;
    }
};

void test01()
{
    Myadd myadd;
    int re=myadd(10,20);
    cout<<"ret="<<re<<endl;
    //匿名函数的调用
    cout<<"Myadd()(100,200)=    "<<Myadd()(100,200)<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
} 