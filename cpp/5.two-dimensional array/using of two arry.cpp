//创建二维数组，三行三列
//统计考试成绩。，让每一行相加得到总成绩
#include<iostream>
#include<string>
using namespace std;

int main()
{
    int socre[][3]={{100,100,100},{90,50,100},{60,70,80}};
    int L=sizeof(socre[0])/sizeof(socre[0][0]);
    int H=sizeof(socre)/sizeof(socre[0]);
    int socre2[]={0,0,0};
    string names[]={"张三","李四","王五"};
    for(int i=0;i<H;i++)
    {
        //可以在这里用sum=0代替数组输入，每执行一次外循环就可以清0
        for(int j=0;j<L;j++)
        {
            socre2[i]+=socre[i][j];
        }
    }
    cout<<"张三，李四，王五的成绩分别为："<<endl;
    for(int s=0;s<3;s++)
    {
        cout<<names[s]<<"的总成绩为"<<socre2[s]<<endl;;
    }
}