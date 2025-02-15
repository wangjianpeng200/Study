#include<iostream>
using namespace std;

int main()
{
    int arr[2][3]={{1,2,3},{4,5,6}};
    cout<<"数组占用内存为："<<sizeof(arr)<<endl;
    cout<<"数组一行占用的内存为："<<sizeof(arr[0])<<endl;//后面的标号代表行
    cout<<"一个元素占用的空间："<<sizeof(arr[0][0])<<endl;
    cout<<"该数组的行数为："<<sizeof(arr)/sizeof(arr[0])<<endl;
    cout<<"该数组的列数为："<<sizeof(arr[0])/sizeof(arr[0][0])<<endl;
    cout<<"数组首地址："<<arr<<endl;
    cout<<"第一行，第一列的元素地址："<<&arr[0][0]<<endl;
    cout<<"第一行的首地址："<<arr[0]<<endl;//第一行的首地址
    cout<<"第二行的首地址："<<arr[1]<<endl;//第二行的首地址,与第一行相差三个元素，所以间隔为3*4=12
    system("pause");
}