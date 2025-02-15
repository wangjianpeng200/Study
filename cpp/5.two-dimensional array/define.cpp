#include<iostream>
using namespace std;

int main()
{
    int arr[][3]={{1,2,3},{4,5,6}};//外层打印行数，内层打印列数
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<arr[i][j]<<"    ";
        }
        cout<<endl;
    }
    system("pause");
}