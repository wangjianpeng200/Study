#include<iostream>
using namespace std;

class person
{
    public:
    static int a;
    static void out()
    {
        cout<<"person"<<endl;
    }
};

int person::a=10;

void test()
{
    person::out();  //静态成员函数
    person p1;
    p1.a=20;
    person p2;
    p2.a=30;
    cout<<p1.a<<endl;
    cout<<p2.a<<endl;
    cout<<person::a<<endl;

}

int main() 
{
    test();
    return 0;
}