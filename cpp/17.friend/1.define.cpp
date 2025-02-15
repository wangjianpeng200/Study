/*
友元
生活中你的家有客厅(Public)，有你的卧室(Private)
客厅所有来的客人都可以进去，但是你的卧室是私有的，也就是说只有你能进去
但是呢，你也可以允许你的好闺蜜好基友进去。

在程序里，有些私有属性 也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术
友元的目的就是让一个函数或者类 访问另一个类中私有成员

友元的关键字为 friend
友元的三种实现
1.全局函数做友元
2.类做友元
3.成员函数做友元
*/

#include<iostream>
#include<string>
using namespace std;

class building
{
    friend void goodgay(building *p);
    public:
    string sittingroom;
    building()
    {
        sittingroom="客厅";
        bedroom="卧室";
    }

    void show()
    {
        cout<<"当前的private成员值为:"<<bedroom<<endl;
    }
    private:
    string bedroom;
};
/*
void gay()
{
    building p1("饭桌","床");
    p1.sittingroom="ss";
    cout<<"好基友函数正在访问："<<p1.sittingroom<<endl;
    //cout<<"好基友函数正在访问："<<p1.bedroom<<endl;
    p1.show();
}
int main()
{
    gay();
    system("pause");
    return 0;
}
*/
void goodgay(building *p)
{
    cout<<"好基友函数正在访问："<<p->sittingroom<<endl;
    cout<<"好基友函数正在访问："<<p->bedroom<<endl;
}

int main()
{
    building p;
    goodgay(&p);
    system("pause");
    return 0;
}