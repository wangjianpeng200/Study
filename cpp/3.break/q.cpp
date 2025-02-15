/*
break的使用
1.在swtich语句中，中制case，并跳出swtich语句
#include<iostream>
using namespace std;

int main()
{
    int a=0;
    cout<<"请选择副本难度"<<endl;
    cout<<"1.简单   2.中等    3.困难"<<endl;
    cin>>a;
    switch (a)
    {
    case 1:cout<<"您选择的是简单难度"<<endl;break;
    case 2:cout<<"您选择的是中等难度"<<endl;break;
    case 3:cout<<"您选择的是苦难难度"<<endl;break;
    }
system("pause");
}

2.在循环语句中，作用是跳出当前循环
#include<iostream>
using namespace std;

int main()
{
   for(int i=0;i<10;i++)
   {
    cout<<i<<endl;
    if(i==5)
    {
        break;
    }
   }
system("pause");
}

3.出现在嵌套循环中，跳出最近的内层循环语句
*/

#include<iostream>
using namespace std;

int main()
{
	for(int j=0;j<10;j++)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "*  ";
		}
        cout << endl;
        if(j==5)
        {
            break;
        }
	}
	system("pause");
}





