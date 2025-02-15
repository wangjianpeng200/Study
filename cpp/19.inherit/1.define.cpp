//继承是面向对象的三大特性之一
//我们发现，定义这些类时，下级别的成员除了拥有上一级的共性，还有自己的特性
//可以用继承来减少代码的重复
//class 子类：继承方式 父类（子类也成为派生类，父类也成为基类）


#include<iostream>
using namespace std;
//普通实现页面
/*
class java
{
    public:
    void head()
    {
        cout<<"首页，公开课，登录，注册.....(公共头部)"<<endl;
    }
    void footer()
    {
        cout<<"帮助中心，交流合作，站内地图....(公共底部)"<<endl;
    }
    void left()
    {
        cout<<"java,python,c++.....(公共分类列表)"<<endl;
    }
    void content()
    {
        cout<<"java学科的视频"<<endl;
    }
};

class cpp
{
    public:
    void head()
    {
        cout<<"首页，公开课，登录，注册.....(公共头部)"<<endl;
    }
    void footer()
    {
        cout<<"帮助中心，交流合作，站内地图....(公共底部)"<<endl;
    }
    void left()
    {
        cout<<"java,python,c++.....(公共分类列表)"<<endl;
    }
    void content()
    {
        cout<<"cpp学科的视频"<<endl;
    }
};

class python
{
    public:
    void head()
    {
        cout<<"首页，公开课，登录，注册.....(公共头部)"<<endl;
    }
    void footer()
    {
        cout<<"帮助中心，交流合作，站内地图....(公共底部)"<<endl;
    }
    void left()
    {
        cout<<"java,python,c++.....(公共分类列表)"<<endl;
    }
    void content()
    {
        cout<<"python学科的视频"<<endl;
    }
};

void test01()
{
    java ja;
    ja.head();
    ja.left();
    ja.content();
    ja.footer();

cout<<"-------------------------------------------------------------"<<endl;
    cpp c;
    c.head();
    c.left();
    c.content();
    c.footer();

cout<<"-------------------------------------------------------------"<<endl;
    python py;
    py.head();
    py.left();
    py.content();
    py.footer();
}
*/

//继承实现页面

class basepage//公共页面的类
{
    public:
    void head()
    {
        cout<<"首页，公开课，登录，注册.....(公共头部)"<<endl;
    }
    void footer()
    {
        cout<<"帮助中心，交流合作，站内地图....(公共底部)"<<endl;
    }
    void left()
    {
        cout<<"java,python,c++.....(公共分类列表)"<<endl;
    }
};
//java页面
class java:public basepage
{
    public:
   void content()
    {
        cout<<"java学科的视频"<<endl;
    }
};
//python页面
class python:public basepage
{
    public:
   void content()
    {
        cout<<"python学科的视频"<<endl;
    }
};
//cpp页面
class cpp:public basepage
{
    public:
   void content()
    {
        cout<<"cpp学科的视频"<<endl;
    }
};
//调用函数
void test01()
{
    java ja;
    ja.head();
    ja.left();
    ja.content();
    ja.footer();

cout<<"-------------------------------------------------------------"<<endl;
    cpp c;
    c.head();
    c.left();
    c.content();
    c.footer();

cout<<"-------------------------------------------------------------"<<endl;
    python py;
    py.head();
    py.left();
    py.content();
    py.footer();
}

int main()
{
    test01();
    system("pause");
    return 0;
}