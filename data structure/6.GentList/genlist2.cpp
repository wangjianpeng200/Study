#include<stdio.h>
#include<iostream>
#include<string>
#include<cassert>
using namespace std;

using AtomType=int;
enum ElemTag
{
    HEAD,ATOM,CHILDLIST
};

class GenList;
class GLNode;

class GLNode//广义表的一个节点
{
    public:
    ElemTag tag;
    GLNode *tp;
     union gentlist//联合体，只能使用一个成员
    {
        AtomType atom;
        GLNode* hp;
    };
};

typedef GLNode* Point_GenList;//节点的指针

// class GenList
// {
//     public:
//     Point_GenList point;
//     void Init(GenList &g);
//     void Create(GenList &g,char* c);//关键！！！！！

// };

void Init(Point_GenList &g)
{
    g=NULL;
}

void Create(Point_GenList &g,char* c)//重要！！！！！！！！！！！！！！！！！
{
    //会出现哪些形式的广义表，括号不算在广义表中
    //全部看作表头和表位

    //先去掉括号
    int n=strlen(c);
    char *sub=new char(n-2);//去掉括号的空间
    char *hsub=new char(n-2);//用于分离表头
    assert(sub!=NULL && hsub!=NULL);

    //全是原子的结构
    //"1,2,3"
    strncpy(sub,c+1,n-2);//将除掉括号的串存储中sub中
    sub[n-2]='\0'; 

    if(g==NULL)
    {
        g=new(GLNode);
        assert(g!=NULL);
        g->tag=HEAD;
    }

}

int main()
{

}