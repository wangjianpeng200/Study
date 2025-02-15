//通过重载递增运算符，实现自己的整型数据
//后置递增是先进行表达式运算


#include<iostream>
using namespace std;

class person
{
friend ostream& operator<<(ostream &cout,person &p);
    private:
    int m_a;
public:
    person()
    {
        m_a=0;
    }
    person(person &p)
    {
        m_a=p.m_a;
    }
    //重载前置++运算符
person& operator++()//返回引用是为了一直对一个数据进行递增操作
{
    //先进行++运算
    m_a++;
    //返回其本身
    return *this;
}
//重载后置++运算符
person operator++(int)//返回值不能作为区分函数重载的依据,int代表占位参数，可以用于区分前置后后置递增
{
    //先 记录当时的结果
    person temp=*this;//将原有的对象拷贝
    //后 递增
    m_a++;
    //最后将记录结果做返回
    return temp;//返回的是值，不是引用
}

};

ostream& operator<<(ostream &cout,person &p)
{
    cout<<p.m_a;
    return cout;
}

void test01()
{
    person p1;
    cout<<p1<<endl;
    cout<<++(++p1)<<endl;
    cout<<p1<<endl;
}

void test02()
{
    person p3;
    //cout<<p3++<<endl;
    cout<<p3<<endl;
}
int main()
{
    //test01();
    test02();
    system("pause");
    return 0;
}