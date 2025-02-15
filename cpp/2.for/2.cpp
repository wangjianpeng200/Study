//嵌套循环打印*图
//外层执行一次，内层执行一周
#include<iostream>
using namespace std;

int main()
{
    for(int a=0;a<10;a++)
    {
     for(int i=0;i<10;i++)
     {
        cout<<"*  ";
     }
     cout<<endl;
     }
}