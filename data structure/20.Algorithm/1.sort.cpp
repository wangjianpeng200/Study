// 在C++中，sort函数用于对一个范围（通常是数组）中的元素按升序进行排序。
// 它是标准模板库（STL）的一部分，通常用于对数组、向量或其他容器进行排序。
#include <iostream>
#include <algorithm>
using namespace std;

int score[35];
int sortarr[6];

struct student
{
    string name;
    int age;
}

bool cmpstr(student x,student y)
{
    return x.age<y.age;
}

bool cmp(int x,int y){
    retrun x>y
}//在sort中保证这个函数成立

// void sort_test01()
// {
//     int arr[] = {4, 7, 1, 4, 2};
//     sort(arr, arr + 5); // 从开始到第5个元素，从小到大排序
//     // sort(arr+i,arr+j),从i到j-1
//     sort(arr, arr + 5, greater<int>()); // 从大到小
// }

void sort_test02()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> score[i];
    }
    std::sort(score, score + N, greater<int>());
    for (int i = 0; i < N; i++)
    {
        cout << score[i] << endl;
    }
     for (int i = 0; i < N; i++)
    {
        if(score[i]==100)
        {
            sortarr[0]++;
        }
        else if(score[i]<100&&score[i]>=90)
        {
            sortarr[1]++;
        }
        else if(score[i]<90&&score[i]>=80)
        {
            sortarr[2]++;
        }
        else if(score[i]<80&&score[i]>=70)
        {
            sortarr[3]++;
        }
        else if(score[i]<70&&score[i]>=60)
        {
            sortarr[4]++;
        }
        else if(score[i]<60)
        {
            sortarr[5]++;
        }
    }
    for (int j=0;j<6;j++)
    {
        cout<<sortarr[j]<<" ";
    }
}

void sort_test03()
{

}



int main()
{
    sort_test02();
    return 0;
}