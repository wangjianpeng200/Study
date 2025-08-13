#include <iostream>
using namespace std;
//要点
//1.继承可以继承public，protected中的成员对象、成员函数、类型定义
//2.基类构造 → 派生类构造 → 派生类析构 → 基类析构
//3.含有虚函数类型的对象，每一个对象初始化的时候，就会附带一个虚函数列表，指向实际类型的虚函数（vptr），虚函数表（虚函数指针）。
//可以观察在类中加了虚函数以后，类的sizeof会变大

//补充：虚函数表是在编译的时候生成的，存储了所有虚函数的执政（存储在静态存储区中）;派生类会对基类的虚函数表进行覆盖
//补充：会在构造时，会将虚函数表指针（vptr）指向当前类的虚函数表

//4.如果一个类型有子类，那么析构函数一定要用虚函数（否则会造成内存泄漏）
//为什么不用虚构造：在构造对象时，对象的类型是确定的，不需要运行时多态，不用动态的选择构造函数
//5.用final标记的类型不能被再次继承
//6.多重继承，可能会造成菱形问题，解决方法是使用虚继承，在继承的时候，使用virtual关键字。用来避免在派生类中生成多个基类的实例
//7.纯虚函数没有函数实体，只有函数声明，没有默认的实现  virtual void func()=0;派生类必须实现纯虚函数。通过存虚函数统一接口。
//8.包含纯虚函数的类不能被实例化，只能派生给其他类（至少包含一个存虚函数的类叫做抽象类，无法被实例化）

class Animal {
public:
    int age;
    int weight;
    virtual void walk()  //虚函数
    {
        cout<<"动物会走路"<<endl;
    }
    Animal()
    {
        cout<<"基类构造"<<endl;
    }
    ~Animal()
    {
        cout<<"基类析构"<<endl;
    }
protected:
    int height=5;
private:
    int a;
};

class dog:public Animal //继承public 和 protected中的数据  1.成员变量  2.成员函数 3.类型自定义
{
public:
    int b;
    void func()
    {
        cout<<height<<endl;
    }
    dog()
    {
        cout<<"派生类构造"<<endl;
    }
    ~dog()
    {
        cout<<"派生类析构"<<endl;
    }
    void walk() override
    {
        cout<<"dog is walking"<<endl;
    }
};

class cat:public Animal
{
    void walk() override
    {
        cout<<"cat is walking"<<endl;
    }
};

void  letwalk(Animal &an)  //传入基类，但是也可以传入派生类
{
    an.walk();
}


class person
{
    public:
        int age;
        virtual void func()
        {
            cout<<"person"<<endl;
        }
};

class student : public person{
    public:
    void func() override
    {
        cout<<"student "<<endl;
    }

};

void vptr()
{
   person p;
   student s;
   cout<<sizeof(s)<<endl;
}

void func()
{
    
    dog d;
    // Animal a;

    // cat c;
    letwalk(d);
    // letwalk(c);
}

int main()
{
    vptr();
    // func();
    return 0;
}