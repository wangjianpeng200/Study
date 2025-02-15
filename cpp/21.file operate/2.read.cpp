#include<iostream>
using namespace std;
#include<fstream>

void test01()
{
    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open())//判断是否打开成功，如果打开成功返回1；没有打开成功返回0
    {
        cout<<"该文件打开失败"<<endl;
        return;
    }
    //读数据
    //第一种
    char buf[1024]={0};
    while(ifs>>buf)//读完后返回一个假的标志
    {
        cout<<buf<<endl;
    }
    //5.关闭文件
    ifs.close();
}

int main()
{
    test01();
    system("pause");
    return 0;
}