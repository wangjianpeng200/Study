#include<iostream>
#include<cassert>
#include<cstring>
#include<queue>
using namespace std;

int i=0;
using ElemType=char;

class TreeNode//树节点的定义
{
    public:
    ElemType data;
    TreeNode* lchild;
    TreeNode* rchild; 
};

class BinTree//操作树的类
{
    public:
    TreeNode* root;
    ElemType refvalue='#';//停止的标志
};
//ABC##DEFG#H

void InitTree(BinTree &b);//初始化操作
//---二叉树的创建
void CreatTree(BinTree *b,char *c);
void CreatTree1(BinTree *b,TreeNode* &t,char *c);
//---二叉树的遍历
void PreOrder(BinTree *b);
void PreOrder(TreeNode *t);
void InOrder(BinTree &b);
void InOrder(TreeNode *t);
void PostOrder(BinTree &b);
void PostOrder(TreeNode *t);
void LevelOrder(BinTree *b);
void LevelOrder(TreeNode *t);
//---二叉树的操作
int size(BinTree *b);//求节点的个数
int size(TreeNode *t);
int Height(BinTree *b);//求树的层数
int Height(TreeNode *t);
TreeNode* Search(BinTree *b,ElemType key);//查找节点，如果有该节点则返回地址
TreeNode* Search(TreeNode *t,ElemType key);
TreeNode* Parent(BinTree *b);//查找父节点
TreeNode* lchild(BinTree *b);//查找左子树
TreeNode* rchild(BinTree *b);//查找右子树
bool Empty(BinTree *b);//判断子树是否为空
void Copy(BinTree *b1,BinTree *b2);//拷贝一颗树
void Clear(BinTree *b);//清除一颗树

void InitTree(BinTree &b)
{
    b.root=NULL;
}

void CreatTree(BinTree *b,char *c)
{
    CreatTree1(b,b->root,c);
}

void CreatTree1(BinTree *b,TreeNode* &t,char *c)
{
    if(c[i]=='\0')
    {
        return;
    }
        if(c[i]=='#')
        {
            t=NULL;
        }
        else
        {
            t=new(TreeNode);
            assert(t!=NULL);
            char temp=c[i];
            t->data=temp;
            i++;
            CreatTree1(b,t->lchild,c);
            i++;
            CreatTree1(b,t->rchild,c);
        }
}

//-------------------先序遍历
void PreOrder(BinTree *b)
{
    cout<<"先序遍历结果为>";
    PreOrder(b->root);
}

void PreOrder(TreeNode *t)
{
    if(t!=NULL)
    {
        cout<<t->data<<"  ";
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    }
}

//--------------------中序遍历
void InOrder(BinTree &b)
{
    cout<<"先序遍历结果为>";
    PreOrder(b.root);
}

void InOrder(TreeNode *t)
{
    if(t!=NULL)
    {
        PreOrder(t->lchild);
        cout<<t->data<<"  ";
        PreOrder(t->rchild);
    }
}
//---------------------后序遍历
void PostOrder(BinTree &b)
{
    cout<<"先序遍历结果为>";
    PreOrder(b.root);
}

void PostOrder(TreeNode *t)
{
    if(t!=NULL)
    {
        PreOrder(t->lchild);
        PreOrder(t->rchild);
        cout<<t->data<<"  ";
    }
}

//------------------------------------层次遍历
void LevelOrder(BinTree *b)
{
    LevelOrder(b->root);
}

void LevelOrder(TreeNode *t)
{
    if(t!=NULL)
    {
        TreeNode *v;
        queue<TreeNode*>q;
        q.push(t);
        while(!q.empty())
        {
            v=q.front();
            q.pop();
            cout<<v->data<<"  ";
            if(v->lchild!=NULL)
            {
                q.push(v->lchild);
            }
            if(v->rchild!=NULL)
            {
                q.push(v->rchild);
            }
        }  
    }
}

//---------------------------------------------------------------------------------
//求节点个数
int size(BinTree *b)
{
    return size(b->root);
}

int size(TreeNode *t)//求节点的个数
{
    if(t==NULL)
    {
        return 0;
    }
    else
    {
        return size(t->lchild)+size(t->rchild)+1;//左子树节点个数加右节点个数加根节点
    }
}


//求层数
int Height(BinTree *b)
{
    return Height(b->root);
}
int Height(TreeNode *t)
{
    if(t==NULL)
    {
        return 0;
    }
    else
    {
        int left=Height(t->lchild);
        int right=Height(t->rchild);
        return (left>right?left:right)+1;
    }
}

TreeNode* Search(BinTree *b,ElemType key)
{
    Search(b->root,key);
}
TreeNode* Search(TreeNode *t,ElemType key)
{

}


TreeNode* Parent(BinTree *b);//查找父节点
TreeNode* lchild(BinTree *b);//查找左子树
TreeNode* rchild(BinTree *b);//查找右子树
bool Empty(BinTree *b);//判断子树是否为空
void Copy(BinTree *b1,BinTree *b2);//拷贝一颗树
void Clear(BinTree *b);//清除一颗树



void test01()
{
    BinTree b1;
    InitTree(b1);
    CreatTree(&b1,"ABC##D##EF##");
    //PreOrder(&b1);
    //LevelOrder(&b1);
    //cout<<"节点个数为："<<size(&b1)<<endl;
    cout<<"层数为："<<Height(&b1)<<endl;
}


// void BinTree::CreatTree1(BinTree &b)
// {
//     ElemType Item;
//     cin>>Item;
//     if(Item==b.refvalue)
//     {
//         b.root=NULL;
//     }
//     else
//     {
//         b.root=new(TreeNode);
//         assert(b.root!=NULL);
//         b.root->data=Item;
//         BinTree b1;BinTree b2;
//         b1.root=b.root->lchild;
//         b1.CreatTree1(b1);
//         b2.root=b.root->rchild;
//         b2.CreatTree1(b2);
//    }
// }

int main()
{
    test01();
    system("pause");
    return 0;
}

