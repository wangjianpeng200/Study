//设计一个英雄的结构体，包括英雄的姓名、年龄、性别；
//创建结构体数组存放五个英雄;
//通过冒泡排序，将数组中的英雄按照年龄升序排序，并打印最终结果
#include<iostream>
#include<string>
using namespace std;
struct hero//定义结构体变量
{
    string name;
    int age;
    string gender;
};
void bul(hero *p,int len)//冒泡排序函数，地址传递
{
    for(int i=len;i>0;i--)
    {
        for(int j=0;j<i-1;j++)
        {
            if(p[j].age>p[j+1].age)
            {
               struct hero temp=p[j];//创建结构体变量
               p[j]=p[j+1];
               p[j+1]=temp;
            }
        }
    }
}
void print(hero *p,int len)//输出显示函数
{
    for(int i=0;i<len;i++)
    {
        cout<<"\t"<<p[i].name<<"   "<<p[i].age<<"    "<<p[i].gender<<endl;
    }
}
int main()
{   
    hero arr[]=
    {
        {"刘备",23,"男"}, {"关羽",22,"男"},
        {"张飞",20,"男"},{"赵云",21,"男"},{"貂蝉",19,"女"}
    };//创建结构体变量
    int len=sizeof(arr)/sizeof(arr[0]);
    cout<<"排序前的英雄:"<<endl;
    print(arr,len);
    bul(arr,len);
    cout<<"排序后的英雄:"<<endl;
    print(arr,len);
    system("pause");
    return 0;
}
