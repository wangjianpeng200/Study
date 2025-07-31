#include<iostream>
using namespace std;
//一个变量的内存刚好是他数据长度的整数倍 就叫自然对其
struct example {
    char a;  
    int b;   
}; 

int main()
{
    example e;
    cout<<sizeof(e)<<endl;
}