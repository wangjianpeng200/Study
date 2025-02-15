/*
封装意义二:
类在设计时，可以把属性和行为放在不同的权限下，加以控制
访问权限有三种:
1.public 公共权限 :    成员 类内可以访问，类外可以访问
2.protected 保护权限 ：成员 类内可以访问，类外不可以访问。儿子可以访问父亲中的保护内容
3.private 私有权限 ：  成员 类内可以访问，类外不可以访问。儿子不可以访问私有权限内容
*/
#include<iostream>
#include<string>
using namespace std;

class person
{
public:
string m_name;
protected:
string m_car;
private:
int ID;
public:
void func()
{
    m_name="张三";
    m_car="拖拉机";
    ID=123456;
    //可以在类内访问
}
};

int main()
{
    person p1;
    p1.m_name="王五";
    p1.m_name="王五";
    //p1.ID=1213;对外不能访问
    //cout<<p1.ID<<endl;不能访问
    system("pause");
    return 0;
}