//const的使用场景
#include<iostream>
#include<string>
using namespace std;

struct student
{
    string name;
    int age;
    int score;
};
//将函数中的形参改为指针，可以减少内存空间，而且不会复制新的副本
//为了防止写的操作改变数据，可以在形参前加const防止原数据改变
void printStu(const student *s)
{
    //s->age=100;报错
    cout<<"学生名字："<<s->name<<"  学生年龄："<<s->age<<"   学生成绩："<<s->score<<endl;
}

int main()
{
    student s={"zhangsan",18,100};
    printStu(&s);//与形参中的s并不关联
    system("pause");
    return 0;
}