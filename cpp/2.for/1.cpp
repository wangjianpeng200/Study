/*

#include<iostream>
using namespace std;

int main()
{
    //for循环
    //
    for(int i=0;i<10;++i)
    {
        cout<<i<<endl;
    //先执行int，再判断条件，再执行语句，i++是最后执行的
    }
    
    system("pause");
}
*/
//敲桌子练习
#include<iostream>
using namespace std;

int main()
{
    for(int i=0;i<=100;i++)
    {
        int a=i%10;
        int b=i/10;
        int c=i%7;
        if(a!=7)
        {
            if(b!=7)
            {
                if(c!=0)
                {
                    cout<<i<<endl;
                }
                else 
                {
                cout<<i<<"敲桌子3"<<endl;
                }
            }
            else
            {
                cout<<i<<"敲桌子2"<<endl;
            }   
        }
        else
        {
            cout<<i<<"敲桌子1"<<endl;
        }
    }
}