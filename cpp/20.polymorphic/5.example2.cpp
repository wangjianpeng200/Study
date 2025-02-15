//利用多态制作饮料
#include<iostream>
using namespace std;

class abstract
{
    public:
    virtual void boil()=0;//煮水
    virtual void brew()=0;//冲泡
    virtual void pour()=0;//倒入杯中
    virtual void add()=0;//添加佐料
    void makedrink()
    {
    boil();//煮水
    brew();//冲泡
    pour();//倒入杯中
    add();//添加佐料
    }
};

class coffee:public abstract
{
    virtual void boil()
    {
        cout<<"煮农夫山泉"<<endl; 
    }
    virtual void brew()
    {
        cout<<"冲泡咖啡"<<endl;
    }
    virtual void pour()
    {
        cout<<"导入杯中"<<endl;
    }
    virtual void add()
    {
        cout<<"加入牛奶"<<endl;
    }
};

class tea:public abstract
{
    virtual void boil()
    {
        cout<<"煮井水"<<endl; 
    }
    virtual void brew()
    {
        cout<<"冲泡茶叶"<<endl;
    }
    virtual void pour()
    {
        cout<<"导入杯中"<<endl;
    }
    virtual void add()
    {
        cout<<"加入花瓣"<<endl;
    }
};

void dowork(abstract *abc)
{
    abc->makedrink();
    delete abc;
}

int main()
{
    dowork(new coffee);
    system("pause");
    return 0;
}