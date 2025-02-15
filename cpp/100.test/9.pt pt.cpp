#include<iostream>
#include<string>
using namespace std;

class base
{
    public:
    int number;
    int tele;
    //base(int a,int b)
    //{
        //this->number=a;
        //this->tele;
    //}
    virtual void show()=0;
};

class son:public base
{
    public:
    base** b1;
    son(int a,int b)
    {
       this->number=a;
    this->tele;
    }
    virtual void show()
    {
        cout<<"这里是一号儿子"<<endl;
    }
};

void test01()
{
    base** b=new base*[4];
    base *b0=new son(0,123);
    base *b1=new son(1,123);
    base *b2=new son(2,123);
    base *b3=new son(3,123);
    b[0]=b0;
    b[1]=b1;
    b[2]=b2;
    b[3]=b3;
    //cout<<sizeof(b)<<endl;//指向指针数组的指针占用的大小
    //cout<<sizeof(b[1])<<endl;//一个单位占用的大小
    //cout<<&b0<<endl;//第一个元素的堆区地址
    //cout<<&b1<<endl;//第二个元素的堆区地址
    //cout<< b[0]<<endl;
    cout<<b<<endl;//指针数组的指针的首地址
    cout<<&b[0]<<endl;//指针数组的指针的首地址
    cout<<&b[1]<<endl;//指针数组的指针的第二个元素地址
    cout<<&b[2]<<endl;
    cout<<b[0]<<endl;//指针数组内第一个元素的地址，b0的地址
    cout<<b[1]<<endl;//指针数组内第二个元素的地址，b1的地址
    cout<<b[2]<<endl;//指针数组内第三个元素的地址，b2的地址
    cout<<*b<<endl;//指针数组内第一个元素的地址，b0的地址
    cout<<&b<<endl;
    cout<<&b0<<endl;
    

    //cout<<b0<<endl;//指针数组内第一个元素存储的堆区数据，b0的地址
    //cout<<b[2]->number<<endl; 

}

int main()
{
    test01();
}