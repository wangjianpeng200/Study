#include<iostream>
using namespace std;

struct person
{
    int number;
    int tele;
    int m_num;
};

int main()
{
    /*
    int a=sizeof(person);
    person *p;
    int b=sizeof(p);
    cout<<a<<"   "<<b<<endl;
    */
   person *arry[5];
   person a[5];
   cout<<"结构体数组的占用空间为："<<sizeof(a)<<endl;
   cout<<"结构体数组指针占用的空间为："<<sizeof(arry)<<endl;
}
