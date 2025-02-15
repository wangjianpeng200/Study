//运用嵌套循环完成惩罚口诀表
#include<iostream>
using namespace std;

int main()
{
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<=i;j++)
        {
            int c=i*j;
            cout<<i<<"*"<<j<<"="<<c<<" ";
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}