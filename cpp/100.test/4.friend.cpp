#include<iostream>
#include<string>
using namespace std;

class building
{
    friend class gay;
public:
     string sittingroom;
     building();
private:
     string bedroom;
};

class gay
{
public:
     building *bu;
     void visit();
     gay();
};
building::building()
{
    sittingroom="客厅";
    bedroom="卧室";
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