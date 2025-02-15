#include<iostream>
using namespace std;
//析构代码中可以将指针释放
/*
深浅拷贝是面试经典问题，也是常见的一个坑:

浅拷贝: 简单的赋值拷贝操作
深拷贝: 在堆区重新申请空间，进行拷贝操作
*/
class person
{
    public:
    person()
    {
        cout<<"person构造函数的调用"<<endl;
    }
  
   person(int age,int hi)
    {
        m_hi=new int(hi);//用指针接收堆区的数据
        m_age=age;  
        cout<<"person有参函数的调用"<<endl;
    }

    person(const person &p)//深拷贝重新找一块堆区存放数据
    {
        m_age=p.m_age;
        int *s=new int(*p.m_hi);
        m_hi=s;
        cout<<"拷贝构造函数的调用"<<endl;
    }

   ~person()
    {
        //将堆区的数据释放
        if(m_hi!=NULL)
        {
            delete m_hi;
            m_hi=NULL;//防止出现野指针
        }
        cout<<"析构函数的调用"<<endl;
    }

    int m_age;//年龄
    int *m_hi;//身高,并且想把身高的数据开辟到堆区
};

void test01()
{
    person p1(18,180);
    cout<<"p1的年龄为:"<<p1.m_age<<"     "<<"p1的身高为:"<<*p1.m_hi<<endl;
    person p2(p1);//
    cout<<"p1的年龄为:"<<p2.m_age<<"     "<<"p1的身高为:"<<*p2.m_hi<<endl;
    //浅拷贝带来的问题是堆区重复释放
}

int main()
{
    test01();
    system("pause");
    return 0;
}
