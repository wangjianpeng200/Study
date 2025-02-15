//do   while
//do{执行语句}while(执行条件)

/*
#include<iostream>
using namespace std;

int main()
{
    int a=0;
    do
    {
       cout<<++a<<endl;
    } while (a<=10);
    system("pause");
}
*/

//水仙花数是指一个三位数的各个位数的三次方之和等于这个数
//1.将所有的三位数进行输出
//2.在所有的三位数中找到水仙花数（获取个位，十位，百位）
//3.输出水仙花数

#include<iostream>
using namespace std;

int main()
{
    int num=100;
    while(num<1000)
    {
        int a=num/100;
        int b=(num/10)%10;
        int c=num%10;
        int num1=a*a*a;
        int num2=b*b*b;
        int num3=c*c*c;
        if(num==num1+num2+num3)
        {
          cout<<"水仙数有"<<num<<endl;  
        }
        num++;
    }
system("pause");
return 0;
}