/*
const修饰成员函数

常函数:
1.成员函数后加const后我们称为这个函数为常函数
2.常函数内不可以修改成员属性
3.成员属性声明时加关键字 mutable 后，在常函数中依然可以修改

常对象:
1.声明对象前加const称该对象为常对象
2.常对象只能调用常函数，因为常对象不能被修改，常函数不能修改成员属性。
*/

#include<iostream>
using namespace std;

class person
{
    public:
    //this的本质是指针常量，指针的指向不可以改变
    //person * const this
    //如果加上const person * const this
    void showperson() const//后面加const，让指针指向的值也不可以修改
    {
        m_b=10;
        //this->m_a=100;
        //this=NULL;//this指针不可以修改指向
    }
    int m_a;
    mutable int m_b;
};

void test01()
{
    const person p;//常对象
    //但是加了mutable的变量可以修改
}

int main()
{
    
}