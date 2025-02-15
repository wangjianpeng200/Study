//结构体嵌套：结构体中的成员可以是另一个结构体
//每个老师辅导一个学员，一个老师的结构体中，记录一个学生的结构体
#include<iostream>
#include<string>
using namespace std;

struct student
{
    string name;
    int age;
    int score;
};
struct teacher
{
    int id;
    string name;
    int age;
    struct student s1;//辅导的学生,同时创建学生结构体变量
}s2;

int main()
{
    s2.id=1904300419;
    s2.name="杨玉鹏";
    s2.age=27;
    s2.s1.name="王健棚";
    s2.s1.age=21;
    s2.s1.score=100;
    cout<<"老师名字："<<s2.name<<"    老师id号:"<<s2.id<<"    老师年龄："<<s2.age<<endl
    <<"学生名字："<<s2.s1.name<<"    学生年龄："<<s2.s1.age<<"           学生成绩："
    <<s2.s1.score<<endl;
    system("pause");
    return 0;
}