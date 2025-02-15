//从父类继承过来的成员，哪些属于子类对象？
#include<iostream>
using  namespace std;

class person
{
    public:
    int m_a;
    protected:
    int m_b;
    private:
    int m_c;
};

class person1:public person
{
    public:
    
};

class person2:protected person
{

};

class person3:private person
{

};

void test01()
{
    cout<<"size of public p1=   "<<sizeof(person1)<<endl;
    cout<<"size of protected p2=   "<<sizeof(person2)<<endl;
    cout<<"size of private p2=   "<<sizeof(person3)<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}