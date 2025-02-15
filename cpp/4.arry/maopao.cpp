/*
冒泡排序是最常见的排序方式
1.比较相邻的元素，如果第一个比第二个大就交换他们
2.对每一对相邻的元素做同样的工作，执行完毕以后找到第一个最大值
3.重复以上步骤每一次比较次数-1，直至结束
*/

#include<iostream>
using namespace std;

int main()
{
   int arr[]={458,56,222,59,44,9,213,7};
   int Long=sizeof(arr)/sizeof(arr[0]);//元素个数
   cout<<"排序前的数组为："<<endl;
   for(int q=0;q<Long;q++)
   {
    cout<<arr[q]<<"    ";
   }
   cout<<endl;//原数组输出
   int temp=0;
   for (int s=Long;s>0;s--)//外循环
   {
   for(int i=0;i<s-1;i++)//内循环
   {
    temp=arr[i];//临时变量
    if(arr[i]>arr[i+1])
    {
        arr[i]=arr[i+1];
        arr[i+1]=temp;//相邻元素交换
    }
   }
   }
   cout<<"排序后的数组为："<<endl;
   for(int j=0;j<Long;j++)
   {
    cout<<arr[j]<<"    ";//排序后数组输出
   }
}