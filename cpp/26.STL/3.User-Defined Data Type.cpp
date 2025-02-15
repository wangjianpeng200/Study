#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

//在vector容器中存放自定义数据类型
class person
{
    public:
    person(string name,int age)
    {
        this->m_name=name;
        this->m_age=age;
    }
    string m_name;
    int m_age;
};

void test01()
{
    vector<person>v;//创建person类型的vector容器
    person p1("wjp",10);
    person p2("yyp",20);
    person p3("ss",30);
    person p4("hh",40);
    //向容器中添加数据
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    //遍历容器
    for(vector<person>::iterator it = v.begin();it!=v.end();it++)
    {
        cout<<"姓名："<<(*it).m_name<<"   "<<"年龄："<<(*it).m_age<<endl;
    }
}

//存放自定义数据类型 指针
void test02()
{
    vector<person*>v;
    person p1("aaa",10);
    person p2("bbb",20);
    person p3("ccc",30);
    person p4("ddd",40);
    //向容器中添加数据
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    //遍历容器
    for(vector<person *>::iterator it=v.begin();it!=v.end();it++)
    {
        cout<<"姓名："<<(*it)->m_name<<"   "<<"年龄："<<(*it)->m_age<<endl;
    }
}

int main()
{
    test01();
    cout<<endl;
    test02();
    system("pause");
    return 0;
}
