#include<iostream>
using namespace std;

class person
{
    public:
    string m_a;
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

int main()
{
    system("pause");
    return 0;
}