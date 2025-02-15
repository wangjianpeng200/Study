//结构体做函数参数：将结构体作为参数向函数中传递
//值传递；地址传递

#include<iostream>
#include<string>
using namespace std;

/*
//1.值传递//定义学生结构体
struct student
{
    string name;
    int age;
    int score;
}s;


void printStu(struct student s)
{
    s.age=100;
    cout<<"学生名字："<<s.name<<"  学生年龄："<<s.age<<"   学生成绩："<<s.score<<endl;
}

int main()
{
    //将结构体做函数参数
    //将学生传入到一个参数中，打印学生身上的所有信息
    //创建结构体变量
    s.name="张三";
    s.age=18;
    s.score=100;
    printStu(s);
    cout<<"新的年龄："<<s.age<<endl;
}
*/

struct student
{
    string name;
    int age;
    int score;
}s;

void print2(student *p)
{
    p->age=100;
    cout<<"学生名字："<<p->name<<"  学生年龄："<<p->age<<"   学生成绩："<<p->score<<endl;
}

int main()
{
    s.name="张三";
    s.age=18;
    s.score=100;
    print2(&s);
    cout<<"新的年龄为:"<<s.age<<endl;
}