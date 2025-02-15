#include<iostream>
using namespace std;

class student1
{
    public:
    int m_st;//什么都不写，默认权限是私有private

};

struct student2
{
    int st;
};

int main()
{
    student1 s1;
    student2 s2;
    //s1.m_st=10;报错，因为class默认为私有权限
    s2.st=10;

    //struct和class的区别
    //struct的默认权限是public
    //class默认权限是私有private
}