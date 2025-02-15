//如果有数据在堆区，就需要自己创建深拷贝函数
#include<iostream>
using namespace std;

/*class person
{
    public:
    string m_name;
    int m_hi;
    //int *m_age;
    person()
    {
        cout<<"构造函数的调用"<<endl;
    }
    person(int hi,string name)
    {
        m_hi=hi;
        m_name=name;
        cout<<"有参构造函数的调用"<<endl;
    }
    ~person()
    {
        cout<<m_name<<"析构函数的调用"<<endl;
    }
//没有重新声明拷贝函数，所有默认浅拷贝
};
void test01()
{
    person p1(21,"张三");
    person p2(p1);
    p2.m_name="李四";
    cout<<"p2拷贝的值为:"<<p2.m_hi<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
//以上为浅拷贝
*/

class person
{
    public:
    int m_hi;
    int *m_age;
    person()
    {
        cout<<"构造函数的调用"<<endl;
    }

    person(int hi,int age)
    {
        m_hi=hi;
        m_age=new int(age);
        cout<<"有参构造函数的调用"<<endl;
    }

    person(person &p)//不能直接用p，因为在创建新p的时候，需要调用copy函数
    {
        m_hi=p.m_hi;
        int *s=new int(*p.m_age);
        m_age=s;
        cout<<"深拷贝函数的调用"<<endl;
    }

    ~person()
    {
        //将堆区的数据释放掉(堆区数据需要人为释放)
        if(m_age!=NULL)
        {
            delete m_age;
            m_age=NULL;
        }
        
        cout<<"析构函数的调用"<<endl;
    }

};
void test01()
{
   person p1(180,21);
   cout<<"p1为:"<<*p1.m_age<<"   "<<p1.m_hi<<endl;
   person p2(p1);
   cout<<"p2为:"<<*p2.m_age<<"   "<<p2.m_hi<<endl;
   *p2.m_age=10;
   cout<<"p1为:"<<*p1.m_age<<"   "<<p1.m_hi<<endl;
   cout<<"p2为:"<<*p2.m_age<<"   "<<p2.m_hi<<endl;
   system("pause");
}

int main()
{
    test01();
    system("pause");
    return 0;
}
