#include<iostream>
using namespace std;

//参数常见分类
//1.无参无返
void test01()
{
    cout<<" this is test01"<<endl;
}
//2.有参无返
void test02(int a)
{
    cout<<"this is test02    "<<"a="<<a<<endl;
}
//3.无参有返
int test03()
{
    cout<<"this is test03"<<endl;
    return 1000;
}
//4.有参无返
int test04(int a)
{
    cout<<"this is teast04     "<<a<<"+4="<<a+4<<endl;
    return a+4;
}


int main()
{
    test01();
    int a=100;
    test02(a);
    int num1=test03();
    cout<<"返回的参数值"<<num1<<endl;
    int b=10;
    b=test04(b);
    cout<<b<<endl;
    system("pause");
    return 0;
}