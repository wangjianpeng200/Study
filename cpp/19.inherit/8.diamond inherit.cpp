/*

菱形继承概念
两个派生类继承同一个基类
又有某个类同时继承者两个派生类
这种继承被称为菱形继承，或者钻石继承

*/

#include<iostream>
using namespace std;
//动物
class animal
{
    public:
    int age;
};
//利用虚继承可以解决菱形继承的问题，在继承前加上关键字virtual变为虚继承
//羊
class sheep:virtual public animal
{
    
};
//骆驼
class tuo:virtual public animal
{

};
//羊驼
class sheeptuo:public sheep,public tuo
{

};

void test01()
{
    sheeptuo s;
    //当菱形继承，两个父类拥有相同的数据，需要加以作用域区分
    s.sheep::age=18;//age的数据在羊上有一份，在羊驼上也有一份
    s.tuo::age=21;
    //当发生虚继承后，两份数据共享，继承的是两份数据的指针，通过指针的偏移量找到数据
    cout<<"sheep的age=    "<<s.sheep::age<<endl;
    cout<<"tuo的age=    "<<s.tuo::age<<endl;

}

int main()
{
    test01();
}