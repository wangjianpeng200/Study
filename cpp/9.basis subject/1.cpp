/*

通讯录是一个可以记录亲人、好友信息的工具。
本教程主要利用C++来实现一个通讯录管理系统
系统中需要实现的功能如下:
添加联系人:向通讯录中添加新人，信息包括(姓名、性别、年龄、联系电话、家庭住址)最多记录1000人
显示联系人:显示通讯录中所有联系人信息
删除联系人:按照姓名进行删除指定联系人
查找联系人：按照姓名查看指定联系人信息
修改联系人: 按照姓名重新修改指定联系人
清空联系人:清空通讯录中所有信息
退出通讯录:退出当前使用的通讯录

*/
#include<iostream>
#include<string>
#define Max 1000;     //最大人数
using namespace std;

//定义结构体
struct txl
{
    string name;
    string gender;
    int age;
    string tele;
    string address;
};
//初始化显示
void display1()
{
    cout << "1.添加联系人" << endl;
    cout << "2.显示联系人" << endl;
    cout << "3.删除联系人" << endl;
    cout << "4.查找联系人" << endl;
    cout << "5.修改联系人" << endl;
    cout << "6.清空联系人" << endl;
    cout << "0.退出系统" << endl;
}
//向通讯录中添加新人
void add(txl* p, int* s, int len)
{
    cout << "请输入联系人姓名：" << endl;
    cin >> p[*s].name;
    cout << "请输入联系人性别：" << endl;
    cin >> p[*s].gender;
    cout << "请输入联系人年龄：" << endl;
    cin >> p[*s].age;
    cout << "请输入联系人电话：" << endl;
    cin >> p[*s].tele;
    cout << "请输入联系人地址：" << endl;
    cin >> p[*s].address;
    cout << "录入成功" << endl;
    *s=*s+1;
}
//显示联系人的函数
void display(txl* p, int* s, int len)
{
    for (int i = 0; i < *s; i++)
    {
        cout << "姓名：" << p[i].name << "   " << "性别："
            << p[i].gender << "   " << "年龄：" << p[i].age
            << "   " << "联系方式：" << p[i].tele << "   "
            << "地址：" << p[i].address << endl;
    }
}
//删除联系人的函数
void dele(txl* p, int* s, int len)
{
    string temp = "";
flag:
    cout << "请输入想要删除的联系人：" << endl;
    cin >> temp;
    for (int i = 0; i < *s; i++)
    {
        if (temp == p[i].name)
        {
            p[i] = p[*s - 1];
            cout << "删除成功" << endl;
            *s -= 1;
            goto next;
        }
    }
    cout << "未找到该联系人,请重新输入" << endl;
    goto flag;
next:
    int l;
}
//查找联系人函数
void search(const txl* p, const int* s, int len)
{
flag:
    string temp = "";
    cout << "请输入您想要查询的联系人：" << endl;
    cin >> temp;
    for (int i = 0; i < *s; i++)
    {
        if (temp == p[i].name)
        {
            cout << "找到该联系人:" << endl;
            cout << "姓名：" << p[i].name << "   " << "性别："
                << p[i].gender << "   " << "年龄：" << p[i].age
                << "   " << "联系方式：" << p[i].tele << "   "
                << "地址：" << p[i].address << endl;
            goto next;
        } 
    }
    cout << "未找到该联系人,请重新输入" << endl;
    goto flag;
next:
    int l;
}
//修改联系人函数
void modify(txl* p, int* s, int len)
{
flag:
    cout << "请输入需要修改的联系人名字：" << endl;
    string temp = "";
    cin >> temp;
    for (int i = 0; i < *s; i++)
    {
        if (temp == p[i].name)
        {
            cout << "找到该联系人:" << endl;
            cout << "姓名：" << p[i].name << "   " << "性别："
                << p[i].gender << "   " << "年龄：" << p[i].age
                << "   " << "联系方式：" << p[i].tele << "   "
                << "地址：" << p[i].address << endl;
            cout << "请修改该联系人信息：" << endl;
            cout << "请输入联系人姓名：" << endl;
            cin >> p[i].name;
            cout << "请输入联系人性别：" << endl;
            cin >> p[i].gender;
            cout << "请输入联系人年龄：" << endl;
            cin >> p[i].age;
            cout << "请输入联系人电话：" << endl;
            cin >> p[i].tele;
            cout << "请输入联系人地址：" << endl;
            cin >> p[i].address;
            cout << "录入成功" << endl;
            goto next;
        }
            
    }
    cout << "未找到该联系人,请重新输入" << endl;
    goto flag;
next:
    int l;
}
//清空联系人函数
void clean(txl* p, int* s, int len)
{
    cout << "您确定要清空联系人吗?" << endl << "1.清空      "
        << "2.返回" << endl;
    int a;
    cin >> a;
    if (a == 1)
    {
        for (int i = 0; i < *s; i++)
        {
            p[i] = { "","",0,"","" };

        }*s = 0;
        cout << "已清空" << endl;
    }
    else
    {
        cout << "已取消，再次回车将返回桌面" << endl;
    }
}


int main()
{
    int s = 0;//指向通讯录位置
    txl arr[1000];
    int len = sizeof(arr) / sizeof(arr[0]);
    while (1)
    {
        display1();
        int a;
        cout << "请选择需要的功能：" << endl;
        cin >> a;
        flag:
        switch (a)
        {
        case 1:add(arr, &s, len); break;
        case 2:display(arr, &s, len); break;
        case 3:dele(arr, &s, len); break;
        case 4:search(arr, &s, len); break;
        case 5:modify(arr, &s, len); break;
        case 6:clean(arr, &s, len); break;
        case 0:cout << "欢迎您下次使用！"; break;
        }system("pause");
    }
    return 0;
}