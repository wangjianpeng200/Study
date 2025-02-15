//实现一个通用的，对数组进行排序的函数
//规则：从小到大
//测试：char 和 int
#include<iostream>
using namespace std;

template<typename T>
void mysort(T a[],int size)
{
    for(int i=size;i>0;i--)
    {
        for(int j=0;j<i-1;j++)
        {
            if(a[i]>a[i+1])
            {
                T temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    cout<<"排序后的数组顺序为："<<endl;
    for(int l=0;l<size;l++)
    {
        cout<<a[l]<<"  ";
    }
    cout<<endl;
}


void test01()
{
    //测试char数组
    char charArr[]="aldjkd";
    int charsize=sizeof(charArr)/sizeof(charArr[0]);
    //测试整数
    int intArr[]={23,2,34,545,3,6,9};
    int intsize=sizeof(intArr)/sizeof(intArr[0]);
    mysort(charArr,charsize);
    mysort(intArr,intsize);
}

int main()
{
    test01();
    system("pause");
    return 0;
}