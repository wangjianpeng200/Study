//vector容器，可以理解为一个数组
#include<iostream>
#include<vector>
#include<algorithm>//标准算法的头文件
using namespace std;

void myprint(int val)
{
    cout<<val<<endl;
}

int main()
{
    //创建了一个vector的容器，数组
    vector<int>v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    //通过迭代器访问容器中的数据
    vector<int>::iterator itBegin =v.begin();//起始迭代器 指向容器中第一个元素
    vector<int>::iterator itEnd =v.end();//结束叠加器 指向容器中最后一个元素的下一个位置
    //第一种，通过while
     while(itBegin!=itEnd)
     {
         cout<<*itBegin<<endl;
         itBegin++;
     }
    return 0;
    //第二种，通过for
    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    {
        cout<<*itBegin<<endl;
    }

    //第三种，通过stl提供遍历算法
    for_each(v.begin(),v.end(),myprint);//algorithm中的便利算法，algrithm
}

