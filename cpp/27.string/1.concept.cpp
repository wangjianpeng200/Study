/*
本质:
1.string是C++风格的字符串，而string本质上是一个类
string和char*区别:
1.char*是一个指针
2.string是一个类，类内部封装了char*，管理这个字符串，是一个char*型的容器
特点:
1.string类内部封装了很多成员方法,例如: 查找find，拷贝copy，删除dElete 替换replace，插入insert
2.string管理char*所分配的内存，不用担心复制越界和取值越界等，由类内部进行负责
*/

#include<iostream>
#include<string>
using namespace std;

void test01()
{
    string s1;//实例化对象,默认构造
    const char* str="hello world";//常量指针不可以修改
    string s2(str);//参数构造

    cout<<"s2="<<s2<<endl;
    
    string s3(s2);//拷贝构造
    cout<<"s3="<<s3<<endl;

    string s4(10,'a');//使用n个字符a初始化
    cout<<"s4="<<s4<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}