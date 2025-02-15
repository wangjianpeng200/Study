//案例描述：封装一个函数，利用冒泡排序，实现对整型数组的升序排序
#include"1.h"

void bubblesort(int arr[])
{
    int len=sizeof(arr)/sizeof(arr[0]);
    for(int s=0;s<len;s++)
    {
        cout<<"原数组元素为："<<arr[s]<<"   ";
    }
    int temp=0;
    for(int j=len;len>0;len--)
    {
    for(int i=0;i<j-1;i++)
    {
        if(arr[i]>arr[i+1])
        {
            temp=arr[i+1];
            arr[i+1]=arr[i];
            arr[i]=temp;
        }
    } 
   }
    for(int x=0;x<len;x++)
    {
        cout<<"排序后数组元素为："<<arr[x]<<"   ";
    }
}