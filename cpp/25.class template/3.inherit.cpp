/*
类模板碰到继承时:
1.当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型。如果不指定，编译器无法给子类分配内存
3.如果想灵活指定出父类中T的类型，子类也需变为类模板
*/
#include<iostream>
using namespace std;

template<class T>
class base
{
    public:
    T m;
};

//class son:public base报错，必须要知道父类中的T类型，才能继承给子类
//指定数据类型<数据类型>
class son1:public base<int>
{
    public:
    int age;
};
//灵活指定父类T类型，子类也创建模板
template<class T1,class T2>//此时T2为char，被传入父类也为char
class son2:public base<T2>
{
    public:
    T1 obj;
};

void test01()
{
    son1 s1;
    son2<son1,char>s2;
    s2.m='w';
    s2.obj.age=21;
    cout<<"son2中的成员"<<s2.m<<" "<<s2.obj.age<<endl;

}

int main()
{
    test01();
    system("pause");
    return 0;
}