#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<cassert>
using namespace std;

using AtomType=int;
class GenList;
class GLNode;
enum ElemTag;
union gentlist;

enum ElemTag
{
    //0    1      2
    HEAD,ATOM,CHILDLIST
};

union gentlist
{
    AtomType atom;
    GLNode* hp;
};

class GLNode//广义表的一个节点
{
    private:
    ElemTag tag;
    GLNode *tp;
    gentlist g_union;
    public:
    friend class GenList;
};

typedef GLNode* Point_GenList;//节点的指针

class GenList
{
    public:
    Point_GenList point;
    void Init(GenList &g);
    void Create(GenList &g,char* c);//关键！！！！！

};

void GenList::Init(GenList &g)
{
    point=NULL;
}

bool Sever(char *sub,char *hsub)
{

}

void GenList::Create(GenList &g,char* c)
{
    //创建两个存放头和尾的堆区数组
    int n=strlen(c);
    char *sub=new char(n-2);//存放全部字串
    assert(sub!=NULL);
    char *hsub=new char(n-2);//只存放头
    assert(hsub!=NULL);
    //将处理后的字符串放在堆区中
    strncpy(sub,c+1,n-1);//截至符也存入了
    //创建头节点
    if(g.point=NULL)
    {
        g.point=new(GLNode);//创建
        assert(g.point!=NULL);
        g.point->tag=HEAD;//添加tag
        g.point->g_union.hp=g.point->tp=NULL;//表头表尾指针指向为空
        //创建一个指针指向该表的头
        GLNode *p=g.point;
        while(strlen(sub)!=0)
        {
            p=p->tp=new(GLNode);//p已经指向了新的节点
            p->g_union.hp=p->tp=NULL;//初始化
            //调用分离函数
            if (Sever(sub,hsub))
            {
                if(hsub[0]=='(')
               {
                   GenList g1;
                   g1.point=p;
                   g1.Create(g1,hsub);
               }
        }
        }
    }
    else
    {
        cout<<"已创建表"<<endl;
    }



}