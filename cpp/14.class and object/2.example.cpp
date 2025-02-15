//设计一个学生类，里面有姓名和学号
//可以给姓名和学号赋值，可以显示学生的姓名和学号
#include<iostream>
#include<string>
using namespace std;

//类中的属性和行为都叫为成员
//属性   成员属性，成员变量
//行为   成员函数，成员方法
class student
{
    public:
    string sname;
    int sid;
    void show()
    {
        cout<<"学生的姓名为："<<sname<<endl<<"学生的学号为："<<sid<<endl;
    }
    void nameinput(string name)
    {
        sname=name;
    }
    void idinput(int id)
    {
        sid=id;
    }
};

int main()
{
    student s1;
    student s2;
    s1.nameinput("王健棚");
    s1.idinput(1904300419);
    s1.show();
    cout<<endl;
    s2.nameinput("杨玉鹏");
    s2.idinput(1231234);
    s2.show();
}