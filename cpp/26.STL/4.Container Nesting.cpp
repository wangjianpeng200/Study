//vector容器嵌套
#include<iostream>
#include<vector>
#include<string>
using namespace std;

void test01()
{
    vector<vector<int>>v;
    //创建小容器，vector中嵌套的vector容器
    vector<int>v1;
    vector<int>v2;
    vector<int>v3;
    vector<int>v4;
    //向小容器中添加数据
    for(int i=0;i<4;i++)
    {
        v1.push_back(i+1);//1-4
        v2.push_back(i+2);
        v3.push_back(i+3);
        v4.push_back(i+4);
    }
    //将小容器插入到大的容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    for (vector<vector<int>>::iterator it =v.begin();it!=v.end();it++)
    {
        //(*it)中是一个小容器，还需要继续遍历
        for(vector<int>::iterator vit=(*it).begin();vit!=(*it).end();vit++)//注意指针的指向
        {
            cout<<*vit<<"   ";
        }
        cout<<endl;
    }
}


int main()
{
    test01();
    system("pause");
    return 0;
}
