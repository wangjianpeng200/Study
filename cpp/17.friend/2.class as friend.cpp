#include<iostream>
#include<string>
using namespace std;

class building
{
    friend class gay;
public:
     string sittingroom;
     
private:
     string bedroom;
     building();
};

class gay
{
public:
     void visit();
     gay();
     private:
     building *bu;
};


    building::building()//成员函数，类内声明，类外实现
{
    sittingroom="客厅";
    bedroom="卧室";
    cout<<"building构造函数调用"<<endl;
}

gay::gay()
{
    bu=new building;//同时调building的构造函数
}

void gay::visit()
{
    cout<<"好基友函数正在访问"<<bu->sittingroom<<endl;
    cout<<"好基友函数正在访问"<<bu->bedroom<<endl;
}

void test01()
{
    gay bb;
    bb.visit();
}
 int main()
 {
    test01();
    system("pause");
    return 0;
 }