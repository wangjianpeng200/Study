#include<iostream>
#include<string>
using namespace std;
//如果想要拓展功能，需要修改源码

class calculator
{
public:
    int m_num1;
    int m_num2;
    calculator(int a, int b) :m_num1(a), m_num2(b)
    {

    }
    int result(string oper)
    {
        if (oper == "+")
        {
            int a = m_num1 + m_num2;
            return a;
        }
        else if (oper == "-")
        {
            int b = m_num1 - m_num2;
            return b;
        }
        else if (oper == "*")
        {
            int c = m_num1 * m_num2;
            return c;
        }
        else
        {
            cout << "该功能暂不支持" << endl;
        }
    }
};

class abstractca
{
public:
    int m_num3;
    int m_num4;
    virtual int get()
    {
        return 0;
    }
};

class addca :public abstractca//加法计算器的类
{
    int get()
    {
        return m_num3 + m_num4;
    }
};

class subca :public abstractca//加法计算器的类
{
    int get()
    {
        return m_num3 - m_num4;
    }
};

class mulca :public abstractca//加法计算器的类
{
    int get()
    {
        return m_num3 * m_num4;
    }
};


void test01()
{
    calculator c1(20, 10);
    cout << c1.m_num1 << "  +  " << c1.m_num2 << "  =  " << c1.result("+") << endl;
    cout << c1.m_num1 << "  -  " << c1.m_num2 << "  =  " << c1.result("-") << endl;
    cout << c1.m_num1 << "  *  " << c1.m_num2 << "  =  " << c1.result("*") << endl;
}

void test02()
{
    //多态的使用条件是父类的指针或引用指向子类的对象
    abstractca *abc=new addca;
    abc->m_num3=20;
    abc->m_num4=10;
    cout<<abc->get()<<endl;
    delete abc;

    abc=new subca;
    abc->m_num3=20;
    abc->m_num4=10;
    cout<<abc->get()<<endl;
    delete abc;
    
    abc=new mulca;
    abc->m_num3=20;
    abc->m_num4=10;
    cout<<abc->get()<<endl;
    delete abc;
}

int main()
{
    test01();
    return 0;
}