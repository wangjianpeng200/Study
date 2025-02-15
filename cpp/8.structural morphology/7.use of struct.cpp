/*
案例描述：
每名老师带领五个学生，总共有三名老师
设计学生和老师的结构体，有老师姓名和一个存放五名学生的数组作为成员的学生，学生有姓名，考试成绩。
创建数组存放三名老师，通过函数给每位老师以及所带的学生赋值，最终打印出老师以及老师所带学生的数据
*/

#include<iostream>
#include<string>
#include<Ctime>

using namespace std;

struct student
{
    string name;
    int score;
};

struct teacher
{
    string name;
    struct student st[5];
};

void writeth(teacher *p,int len1,int len2)
{
    for(int i=0;i<len1;i++)
    {
        string nameSeed="ABCDE";
        p[i].name="teacher-";
        p[i].name+=nameSeed[i];
        string name=" ";
        //p[i].name+=name;
        cout<<"老师的名字为："<<p[i].name<<endl
        <<"\t该老师的学生列表如下:"<<endl;
        for(int j=0;j<len2;j++)
        {
            
            int random= rand() % 61;//0-60再加40
            p[i].st[j].score=random;
            p[i].st[j].name="student-";
            p[i].st[j].name+=nameSeed[j];
            cout<<"\t学生的名字为:"<< p[i].st[j].name
            <<"     其成绩为："<<p[i].st[j].score<<endl;
        }
    }
}

int main()
{
    //创建3名老师的数组
    srand((unsigned int)time(NULL));
    struct teacher th[3];
    struct student st[5];
    int len1=sizeof(th)/sizeof(th[0]);
    int len2=sizeof(st)/sizeof(st[0]);
    writeth(th,len1,len2);
}
