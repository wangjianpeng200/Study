#include<iostream>
#include<string>
using namespace std;

//成员属性设置为私有
//1、可以自己控制读写权限
//2、对于写可以检测数据的有效性
class person
{
private:
    string name;//可写可读
    int age;//只读
    string couple;//只能写
public:
    void setname(string name1)
    {
        name=name1;
    }

    void getname()
    {
        cout<<"名字为："<<name<<endl;
    }
//获取年龄可读可写，如果想要修改年龄的范围是0-100
    int getage()
    {
        return age;
    }

    void setage(int a)
   {
    if(a<0||a>100)
    {
        age=0;
        cout<<"您输入的年龄有误"<<endl;
        return;
    }
    age=a; 
   }

     void setcouple(string name1)
    {
        couple=name1;
    }
};

int main()
{
    person p1;
    p1.setname("王健棚");
    p1.getname();
    p1.setage(21);//在setname中设置检测数据输入的有效性
    cout<<"其年龄为："<<p1.getage()<<endl;
    p1.setcouple("杨玉鹏");
}