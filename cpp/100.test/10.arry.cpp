#include<iostream>
using namespace std;


int main()
{
    int arry[4]={1,2,3,4};
    int *p=arry;
    cout<<p<<endl;
    cout<<arry<<endl;
    cout<<&p<<endl;
    cout<<&p[0]<<endl;
    cout<<p[1]<<endl;
    cout<<&p[1]<<endl;
    cout<<*p<<endl;
}