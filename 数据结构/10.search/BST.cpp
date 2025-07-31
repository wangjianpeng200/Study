#include<iostream>
#include"string"
#include"cassert"
using namespace std;

using ElemType=int;
class BstNode//只是一个树节点的定义
{
    public:
    ElemType data;
    BstNode *lchild;//左子树
    BstNode *rchild;//右子树
};
class BST//二叉排序树
{
    private:
    BstNode *root; 
    bool Insert1(BstNode **t,ElemType x);
    ElemType Min1(BstNode *t);
    ElemType Max1(BstNode *t);
    void Sort1(BstNode *t);
    BstNode* Search1(BstNode *t,ElemType key);
    void MakeEmpty1(BstNode **bst);
    bool Remove1(BstNode **t,ElemType key);

    public: 
    int Insert(BST &bst,ElemType x);
    void InitTree(BST &bst);
    ElemType Min(BST &bst);
    ElemType Max(BST &bst);
    void Sort(BST &bst);
    bool Remove(BST &bst,ElemType key);
    BstNode* Search(BST &bst,ElemType key);
    void MakeEmpty(BST &bst);
};

void BST::InitTree(BST &bst)//初始化，将根节点初始化为空树
{
    bst.root=NULL;
}
bool BST::Insert1(BstNode **t,ElemType x)
{
   //所有左指数都小于根节点
   //所有右指数都大于根节点
   if(*t==NULL)
   {
    *t=new(BstNode);
    assert(*t!=NULL);
    (*t)->data=x;
    (*t)->lchild=(*t)->rchild=NULL;
    return true;
   }
   else if(x<(*t)->data)//如果不空就需要比较
   {
    Insert1(&(*t)->lchild,x);//递归传递左指针的地址
    return true;
   }
   else if(x>(*t)->data)
   {
    Insert1(&(*t)->rchild,x);//递归
    return true;
   }
   return false;//不能有重复的关键字，如果有重复的，返回错误
}
int BST::Insert(BST &bst,ElemType x)//插入排序函数
{
   return Insert1(&bst.root,x);
}
ElemType BST::Min(BST &bst)//获取最小值
{
    assert(bst.root!=NULL);//不能为空
    return Min1(bst.root);
}
ElemType BST::Min1(BstNode *t)
{
    while (t->lchild != NULL)
    {
        t = t->lchild;
    }
    return t->data;
}
ElemType BST::Max(BST &bst)//获取最大值
{
    assert(bst.root!=NULL);//不能为空
    return Max1(bst.root);
}
ElemType BST::Max1(BstNode *t)
{
    while (t->rchild != NULL)
    {
        t = t->rchild;
    }
    return t->data;
}
void BST::Sort(BST &bst)//排序，等于中序遍历
{
    Sort1(bst.root);
}
void BST::Sort1(BstNode *t)
{
    if(t!=NULL)
    {
        Sort1(t->lchild);
        cout<<t->data<<" , ";
        Sort1(t->rchild);
    }
}
BstNode* BST::Search1(BstNode *t,ElemType key)
{
    //可以先和根节点比较大小，只用搜索一边的子树
    if(t==NULL)
    {
        return NULL;
    }
    if(t->data==key)
    {
        return t;
    }
    if(t->data>key)
    {
       return Search1(t->lchild,key);
    }
    else
    {
       return Search1(t->rchild,key);
    }
}
BstNode* BST::Search(BST &bst,ElemType key)//搜索存储值，返回地址
{
    return Search1(bst.root,key);
}
void BST::MakeEmpty1(BstNode **t)
//使用递归从左树开始，然后再释放右数
{
    if(*t!=NULL)
    {
        //左右子树删掉再删除自己
        MakeEmpty1(&(*t)->lchild);
        MakeEmpty1(&(*t)->rchild);
        delete (*t);
        *t=NULL;
    } 
    else
    {
        return;
    }
}
void BST::MakeEmpty(BST &bst)//释放二叉树
{
    MakeEmpty1(&(bst.root));
}
bool BST::Remove1(BstNode **t,ElemType key)
{
    if(*t==NULL)
    return false;
    if(key<(*t)->data)
    Remove1(&(*t)->lchild,key);
    else if(key>(*t)->data)
    Remove1(&(*t)->rchild,key);
    else
    {
        BstNode *p=NULL;//定义一个指针指向需要删除的节点
        //第一种情况是：删除的是末尾节点
        if((*t)->lchild==NULL && (*t)->rchild==NULL)
        {
            delete(*t);
            *t = NULL;
        }
        //第二种情况：删除的节点左边有树，右边为空
        else if((*t)->lchild!=NULL && (*t)->rchild==NULL)
        {
            //此时的t实际上指向的是父节点
            p=*t;
            (*t)=p->lchild;
            delete p;
        }
         //第三种情况：删除的节点左边没树，右边有树
        else if((*t)->lchild==NULL && (*t)->rchild!=NULL)
        {
            //此时的t实际上指向的是父节点
            p=*t;
            (*t)=p->rchild;
            delete p;
        }
        //第四种情况：删除节点的两边都有子树
        else
        {
            p=(*t)->rchild;
            while(p->lchild!=NULL)
            {
              p=p->lchild;
            }
            (*t)->data=p->data;
            Remove1(&(*t)->rchild,p->data);
        }
        
    }return true;
}
bool BST::Remove(BST &bst,ElemType key)
{
    return Remove1(&(bst.root),key);
}


int main()
{
    BST b1;
    b1.InitTree(b1);
    int arry[]={45,12,53,3,37,100,24,61,90,78};
    int size=sizeof(arry)/sizeof(arry[0]);
    //将数据插入到二叉树中
    for(int i=0;i<size;i++)
    {
        b1.Insert(b1,arry[i]);
    }
    ElemType min=b1.Min(b1);
    ElemType max=b1.Max(b1);
    cout<<"最小值为："<<min<<endl;
    cout<<"最大值为："<<max<<endl;
    b1.Sort(b1);
    cout<<endl;
    b1.Remove(b1,12);
    b1.Sort(b1);
    cout<<endl;
    BstNode* address=b1.Search(b1,90);
    cout<<"90的地址为:"<<address<<"    "<<"输出为:"<<(*address).data<<endl;
}
