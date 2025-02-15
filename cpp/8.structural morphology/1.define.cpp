//结构体，结构体属于用户自定义的数据类型，允许用户存储不同的数据类型
//struct 结构名

#include<iostream>
#include<string>
using namespace std;

struct student
{
    //成员列表
    //姓名
    string name;
    //年龄
    int age;
    //分数
    int score;
}s3;
int main()
{
//2.通过学生类型创建具体学生
//1.struct student s1
struct student s1;//c++中结构体创建时struct关键字可以省略
s1.name="张三";
s1.age=18;
s1.score=100;
cout<<"姓名："<<s1.name<<"    年龄:"<<s1.age<<"    分数："<<s1.score<<endl;//通过一个点来访问结构体变量中的属性
//2.struct student s2={......}
struct student s2={"李四",19,80};
cout<<"姓名："<<s2.name<<"    年龄:"<<s2.age<<"    分数："<<s2.score;
//3.在定义结构体时顺便创建结构体变量
s3.name="王五";
s3.age=19;
s3.score=200;
system("pause");
return 0;
}

