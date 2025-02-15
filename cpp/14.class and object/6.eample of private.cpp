//设计一个立方体类
//求出立方体的面积和体积
//分别用全局函数和成员函数判断两个立方体是否相等

#include<iostream>
#include<string>
using namespace std;

//立方体类的设计
//1.创建立方体类
//2.设计属性
//3.设计行为 获取立方体面积和体积
//4.分别利用全局函数和成员函数 判断两个立方体是否相等
class cube
{
private:
    int h;
    int l;
    int w;
public:
//获取长
    int aref()
    {
        return l*h;
    }

};

int main()
{
    system("pause");
    return 0;
}

