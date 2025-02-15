//成员函数做友元
#include<iostream>
#include<string>
using namespace std;

class building;
class gay
{
    public:
    gay();
    void visit1();//命令visit1可以访问private
    void visit2();//命令visit2不可以访问private
    building *bu;   
};

class building
{
    friend void gay::visit1();//一定要声明所属的类
    public:
    string sittingroom;
    building();
    private:
    string bedroom;
};

building::building()
{
    sittingroom="客厅";
    bedroom="卧室";
}

gay::gay()
{
    bu=new building;
}

void gay::visit1()
{
    cout<<"好基友函数正在访问"<<bu->sittingroom<<endl;
    cout<<"好基友函数正在访问"<<bu->bedroom<<endl;
}

void gay::visit2()
{
    cout<<"好基友函数正在访问"<<bu->sittingroom<<endl;
    //cout<<"好基友函数正在访问"<<bu->bedroom<<endl;没有声明，不可访问
}

void test01()
{
    gay bb;
    bb.visit1();
    bb.visit2();
}

int main()
{
    system("pause");
    return 0;
}
