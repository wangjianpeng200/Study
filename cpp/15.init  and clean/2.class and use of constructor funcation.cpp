/*
1.构造函数的分类及调用
两种分类方式:

按参数分为:有参构造和无参构造

按类型分为:
普通构造和拷贝构造

三种调用方式:
括号法
显示法
隐式转换法
示例
*/

#include<iostream>
using namespace std;

//构造一个类
class person
{
    public:
    person()
    {
        cout<<"person无参构造函数(默认构造)的调用"<<endl;

    }

     person(int a)
    {
        age=a;
        cout<<"person有参构造函数的调用"<<endl;
    }

    //拷贝构造函数
    person(const person &p)
    {
        age=p.age;//将传入的这个人身长所有的属性拷贝到我的身上
        cout<<"person拷贝构造函数的调用"<<endl;
    }//不能改变拷贝的数据，所以加const

    ~person()
    {
        cout<<"person析构函数的调用"<<endl;
    }
    int age;
};

//调用
int main()
{
    //1.括号法
    //在调用默认函数是不要加（）
   //person p1;//默认构造函数的调用
   // person p2(10);//调用有参构造函数
   //person p3(p2);//调用拷贝构造函数
   // cout<<"拷贝函数的值"<<p3.age<<endl;//p2中的数据已经传递到了p2中


    //2.显示法
    person p1;//默认构造调用
    person p2=person(10);//调用有参构造，将匿名对象取名为p2，类似于重载函数的区别person（int）
    person p3=person(p2);
    //person(10);匿名对象 特点：当前行执行结束后，系统会立即回收掉匿名对象
    //不要利用拷贝函数，初始化匿名对象
    //person(p3);  错误，编译器会认为person（p3）==person p3;对象声明



    //3.隐式转换法
    person p4=10;//相当于写了person p4=person(10)  有参构造
    person p5=p4;//拷贝构造
    system("pause");
    return 0;

}