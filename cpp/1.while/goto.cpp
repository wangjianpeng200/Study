//goto FLAG;      FALG:      


#include<iostream>
using namespace std;

int main()
{
    for(int i=0;i<100;i++)
    {
        if(i%2==0)
        {
            goto FLAG;
        }
        cout<<i<<"    ";
        FLAG:
        cout<<"输出为偶数"<<endl;
    }
}