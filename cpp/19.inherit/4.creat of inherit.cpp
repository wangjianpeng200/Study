#include<iostream>
using  namespace std;

//继承中的构造和析构顺序
class base
{
    public:
    base()
    {
        cout<<"base构造函数的调用"<<endl;
    }
    ~base()
    {
        cout<<"base析构函数的调用"<<endl;
    }
};

class son:public base
{
    public:
    son()
    {
        cout<<"son构造函数的调用"<<endl;
    }
    ~son()
    {
        cout<<"son析构函数的调用"<<endl;
    }
};

void test01()//在子类的调用中，先构造父类，再构造子类；在析构时，先析构子类，再析构父类
{
    son s;
}

int main()
{
    test01();
    system("pause");
    return 0;
}