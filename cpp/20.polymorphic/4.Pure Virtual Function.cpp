/*
在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容
因此可以将虚函数改为纯虚函数:
纯虚函数语法: virtual 返回值类型 函数名(参数列表) = 0;

当类中有了纯虚函数，这个类也称为抽象类
抽象类特点:
1.无法实例化对象
2.子类必须重写抽象类中的纯虚函数，否则也属于抽象类
*/

#include<iostream>
using namespace std;

class base
{
    public:
    virtual void funca()=0;//纯虚函数，这个类称为抽象类：1.无法实例化对象，不能用构造函数构建 
    //2.抽象类的子类必须重写父类中的纯虚函数，否则也是抽象类
};

class son:public base
{
    //子类必须重写父类中的虚函数
};

void test01()
{
    //base b;//无法实例化的对象
    //new base
}

int main()
{

}