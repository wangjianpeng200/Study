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


bool Sever(char * sub,char *hsub)//括号分离和逗号分离,hsub用于存放头值，sub用于存放尾值
{
    if(*sub=='\0'||strcmp(sub,"()")==0)//空串或者与（）相等，是一个空表
    {
        hsub[0]='\0';
        return true;
    }
    int n=strlen(sub);
    int i=0;
    char ch=sub[0];
    int k=0;
    while(i<n&&(ch!=','||k!=0))
    //意思是，如果搜索到了括号，那么即使是括号也会继续检索，直到检索到‘)’
    //判断边界条件，搜索范围要小于字符串的长度，并且不能搜索到‘，’和‘（）’
    {
        if (ch=='(')
        {
             k++;
        }
        else if(ch==')')
        {
            k--;
        }
        i++;
        ch=sub[i];
    }
    if(i<n)
    {
        sub[i]='\0';
        strcpy(hsub,sub);//复制表头到hsub中
        strcpy(sub,sub+i+1);//复制表尾到sub中
    }
    else if(k!=0)
    {
        return false;
    }
    else//如果该串里面只有一个表
    {
        strcpy(hsub,sub);
        sub[0]='\0';

    }
    return true;
}

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

void GenList::Create(GenList &g,char* c)//重要！！！！！！！！！！！！！！！！！
{
    //会出现哪些形式的广义表，括中
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

    if(g.point==NULL)
    {
        g.point=new(GLNode);
        assert(g.point!=NULL);
        g.point->tag=HEAD;
        g.point->g_union.hp=g.point->tp=NULL;
    }
    GLNode *p=g.point;//定义一个指针始终指向这个头
    while(strlen(sub)!=0)
    {
        p=p->tp=new(GLNode);//创建下一个节点
        assert(p!=NULL);
        p->g_union.hp=p->tp=NULL;//将下一个节点初始化

        //sever的作用是分离表头，并存储在hsub中
        if(Sever(sub,hsub))
        {
            if(hsub[0]=='(')
            {
                //说明分离出来的元素是一个子表,则给联合体赋值
                p->tag=CHILDLIST;
                //重新创建一个对象，并且创建子表
                GenList g1;
                g1.point=p->g_union.hp;//在头创建
                g1.Create(g1,hsub);
            }
            else
            {
                p->tag=ATOM;
                p->g_union.atom=atoi(hsub);
            }
        }
    }
}

void test_creat()
{
    GenList g1;
    char *c="(1,2,3,4)";
    char *c1="((1,2,3))";
    char *c2="((1,2),3)";
    char *c3="(1,(1,2))";
    g1.Create(g1,c);
}

int main()
{
    
}