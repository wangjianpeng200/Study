#include<iostream>
using namespace std;
//空指针调用成员函数
class person
{
    public:
    void showcalssname()
    {
        cout<<"this is person calss"<<endl;
    }
    void showpersonage()
    {
        //报错原因是因为传入的指针为空
        if(this==NULL)
        {
            return;
        }
        cout<<"m_age="<<this->m_age<<endl;
    }
    int m_age;
};
void test01()
{
    person *p=NULL;//使this指针为空，无法指向
    p->showcalssname();//可以被调用
    p->showpersonage();
}
int main()
{
    test01();
    system("pause");
    return 0;
}