/*
数据类型 数组名[数组长度]；
数据类型 数组名[数组长度]={值1，值2，值3}
数据类型 数组名[]={值1.值2......}
*/
/*
int main()
{
    int ary[5]={1,3,4,5,6};
    //利用循环的方式来输出数组中的元素
    for(int i=0;i<5;i++)
    {
        cout<<ary[i] <<endl;//如果数据没有填写完，则用0来填补
    }
    system("pause");
}
*/
/*
#include<iostream>
using namespace std;

int main()
{
    int ary[]={1,3,5,7,9};
    cout<<"该数组的占用空间为："<<sizeof(ary)<<endl;
    cout<<"该数组一个数所占用空间"<<sizeof(ary[0])<<endl;
    cout<<"数组元素数量："<<sizeof(ary)/sizeof(ary[2])<<endl;
    cout<<"数组首地址："<<ary<<endl;
}
*/
/*
#include<iostream>
using namespace std;

int main()
{
    int wei[]={200,350,200,400,250};
    int max=0;
    for(int i=0;i<5;i++)
    {
        if(max<wei[i])
        {
            max=wei[i];
        }
    }
    cout<<"最重的小猪重量为："<<max<<endl;
    system("pause");
}
*/
#include<iostream>
using namespace std;

int main()
{
   int arr[]={1,2,3,4,5,32,534,77,9};
   cout<<"元素数组逆置前："<<endl;
   int a=sizeof(arr)/sizeof(arr[0]);
   for(int i=0;i<a;i++)
   {
    cout<<arr[i]<<"   ";
   }
   cout<<endl;
   int temp=arr[0];
   int j=a-1;
   for(int i=0;i<j;i++)
   {
    temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
    j--;
   }
   cout<<"逆置后的数组为："<<endl;
   for(int s=0;s<a;s++)
   {
    cout<<arr[s]<<"   ";
   }
   system("pause");
}