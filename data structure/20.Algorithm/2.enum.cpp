// 枚举枚举法一般比较直观，容易理解，但由于要检查所有的可能解，因此运行效率较低
// 能够用枚举法解决的题目往往是最简单的一类题目。这种题目具有以下特点:
// 解枚举范围是有穷的
// 检验条件是确定的
#include <iostream>
#include <algorithm>
#include <cstdlib> //执行随机生成
#include <ctime>   //时间相关函数
using namespace std;

// int n;
// int digit[6]
// bool judge(int x);

// bool judge(int x)
// {
//     int m, sum;
//     while (x)
//     {
//         digit[m++] = x % 10;
//         sum += x % 10;
//         x /= 10; // 删除个位
//     }
//     if (sum != n)
//     {
//         return false;
//     }

//     for (int j = 0; j < m; j++) // m此时已经存储了位数
//     {
//         if (digit[j] != digit[m - 1 - j])
//         {
//             return false;
//         }
//     }
//     return true;
// }

void test01() // 寻找一个区间内的质数
{
    int n, m;
    cin >> n >> m;
    if (n > m)
    {
        int tem = m;
        m = n;
        n = tem;
    }
    for (int j = n; j <= m; j++)
    {

        bool is_prime = true;
        if (j == 1)
        {
            continue;
        }
        for (int i = 2; i < j; i++)
        {
            if (j % i == 0)
            {
                is_prime = false;
                cout << j << "   NOt PRIME" << endl;
                break;
            }
        }
        if (is_prime)
        {
            cout << j << "   PRIME" << endl;
        }
    }
    return;
}

void test02() // 随机生成大写字母字符串，枚举猜
{
    srand(time(NULL));
    char s[10];
    for (int i = 0; i < 10; i++)
    {
        s[i] = (char)(65 + rand() % 26); // 随机生成大写字母
    }
}

// void test03() // 回文数，各个位数之间的和为n
// {

//     for (int i = 10000; i <= 999999; i++)
//     {
//         if(judge(i))
//         {
//             cout<<i<<endl;
//         }
//     }
// }

void test04() // 吹蜡烛,从i岁开始，才能累计236
{
    for (int i = 1; i <= 200; i++)
    {
        int sum = 0;
        for (int j = i; j <= 200; j++)
        {
            sum += j;
            if (sum == 236)
            {
                cout << i << endl;
                return;
            }
        }
    }
    cout << "无" << endl;
}


void test05()
{
    int num=0;
    //bool flag=0;
    // int n,m;
    // cin>>n;
    // cin>>m;
    for(int i=100;i<=114;i++)
    {
        bool flag=0;
        int x=i;
        while(x)
        {
            if(x%10==4)
            {
                flag=1;
                break;
            }
            x/=10;
        }
        if(flag!=1)
        {
            num++;
        }
    }
    cout<<num<<endl;
}

void test06()
{
    int n;
    cin>>n;
    int a,b,c;
    for(c=3;a*a+b*b+c*c<=n;c++)
    {
        for(b=c-1;a*a+b*b+c*c<=n||b<c;b++)
        {
            for(a=b-1;a*a+b*b+c*c<=n||a<b;a++)
            {

            }
            if(a*a+b*b+c*c==n)
            {
                cout<<a<<" "<<b<<"  "<<"  "<<c;
            }
        }
         if(a*a+b*b+c*c==n)
            {
                cout<<a<<" "<<b<<"  "<<"  "<<c;
            }
    }
     if(a*a+b*b+c*c==n)
            {
                cout<<a<<" "<<b<<"  "<<"  "<<c;
            }
}

int main()
{
    // test01();
    // cin >> n;
    // test03();
    //test04();
    test06();
    return 0;
}
