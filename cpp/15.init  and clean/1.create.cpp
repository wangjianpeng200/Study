#include<iostream>
using namespace std;

//对象的初始化和清理
//1.构造函数进行初始化操作

class person
{
    public:
    //1构造函数
    //没有返回值 不用写void
    //函数名和类相同
    //构造函数可以有参数，可以发生重载
    //创建对象的时候，构造函数会自动调用，而且只调用一次
    person()
    {
        cout<<"person构造函数的调用"<<endl;
    }
    //2.析构函数 进行清理的操作
    //没有返回值 不写void
    //函数名和类名相同 在名称前面加~
    //析构函数不可以有参数的，不可以发生重载
    //对象在销毁前 会自动调用析构函数，而且只会调用一次

~person()
{
    cout<<"析构函数的调用"<<endl;
}
};

void test01()//在栈区上，所以执行一次后会被销毁
{
    person p;
}

int main()
{
    //test01();
    person p;
    system("pause");//在按任意键之前程序执行都还没有结束，所以析构函数不会执行
    return 0;
}
