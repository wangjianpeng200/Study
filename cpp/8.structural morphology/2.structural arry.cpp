//struct 结构体名 数组名[元素个数]={{  } ，{   }，{   }......}
#include<iostream>
using namespace std;

struct student
{
    string name;
    int age;
    int score;
};

int main()
{
    struct student arr[]=
    {
        {"张三",18,100},
        {"李四",19,99},
        {"王五",20,98}
    };
    cout<<arr[2].name<<endl;
    //给结构体数组赋值：
    arr[2].name="wjp";
    arr[2].age=21;
    arr[2].score=100;
    //便利结构体数组
    for(int i=0;i<3;i++)
    {
        cout<<"姓名为："<<arr[i].name<<"    "<<endl;
        cout<<"姓名为："<<arr[i].name<<"   年龄为："<<arr[i].age<<"    分数为："<<arr[i].score<<"    "<<endl;
    }
}