#include"swap.h"

void swap(int a,int b)
{
    cout<<"交换前的值"<<endl<<"a="<<a<<"   b="<<b<<endl;
    int temp=a;
    a=b;
    b=temp;
    cout<<"交换后的值"<<endl<<"a="<<a<<"   b="<<b<<endl;
}
