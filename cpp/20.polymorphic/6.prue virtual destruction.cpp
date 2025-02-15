/*
多态是C++面向对象三大特性之一
多态分为两类
静态多态:函数重载和 运算符重属于静态多态，复用函数名
动态多态: 派生类和虚函数实现运行时多态
静态多态和动态多态区别:
1.静态多态的函数地址早绑定 - 编译阶段确定函数地址
2.动态多态的函数地址晚绑定 - 运行阶段确定函数地址
*/

/*
动态动态需要满足的条件：
1.有继承关系
2.子类要重写父类中的虚函数（重写是函数返回类型 函数名 参数列表等完全相同）

动态多态的使用：
1.用父类的指针或引用指向子类对象
*/

#include<iostream>
using namespace std;

class animal
{
    public:
    virtual void speak()=0;//加了virtueal后变为虚函数

};

class cat:public animal
{
public:
  virtual void speak()
  {
  cout<<"小猫在说话"<<endl;
  }
};

void Dospeak(animal &animal)
{
    animal.speak();
}


int main()
{
    cat a1;//创建的是子类，但是将父类的引用指向了子类
    Dospeak(a1);
    a1.animal::speak();//添加作用域
    return 0;
}