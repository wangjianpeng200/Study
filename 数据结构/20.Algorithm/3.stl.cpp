#include<vector>
#include<set>//基于中序遍历的平衡二叉搜索树，存储不重复的元素，是有顺序的
#include<iostream>
#include<algorithm>
#include<random>
using namespace std;

class Person
{
    public:
    int age;
    Person(int a)
    {
        age=a;
    }
    
    bool operator > (const Person& p1)
    {
        return this->age>p1.age;
    }
};

void test02()
{
    set<Person> s1;
    for(int i=1;i<5;i++)
    {
        int p=i*i;
        Person p1(p);
        s1.insert(p1);
    }
    set<Person>::iterator it;
    it=s1.begin();
    for(;it!=s1.end();it++)
    {
        cout<<it->age;
    }
}


void test01()
{
    vector<int> v1;
    vector<int> v4(10,1);
    vector<vector<int>> v2(10,vector<int>(10,5));//vector的嵌套
    vector<int>::iterator it;//迭代器，相当于一个指针

    for(int i=1;i<11;i++)
    {
        v1.push_back(i*i);
    }
    for(it=v1.begin();it!=v1.end();it++)
    {
        cout<<*it<<"  ";
    }
}
   
   

   int main()
   {
    //test01();
    test02();
    return 0;
   }