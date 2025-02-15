#include<iostream>
using namespace std;
//continue 执行到continue就结束该此循环开始下一次循环
int main()
{
    for(int i=0;i<100;i++)
    {
        if(i%2==0)
        {
            continue;//筛选条件，执行到此就不再向下执行，重新执行下一次循环
        }
        cout<<i<<endl;
    }
}