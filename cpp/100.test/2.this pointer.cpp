#include<iostream>
using namespace std;

class person
{
    public:
    int age;
    person(int age)
    {
        this->age=age;
    }
    person& funca1(person *p)
    {
        p->age+=10;
        this->age+=p->age;
        return *this;
    }
};

int main()
{
    person p1(10);
    person p2(20);
    cout<<"p1的年龄为:"<<p1.age<<endl;
    p1.funca1(&p2).funca1(&p2);
    cout<<"p1的年龄为:"<<p1.age<<endl;
    cout<<"p2的年龄为:"<<p2.age<<endl;
    system("pause");
    return 0;
}