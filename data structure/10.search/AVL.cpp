// 平衡二叉树
/*
平衡二叉树(Balanced Binary Tree 或Height-Balanced Tree)又称AVL树。它或者
是一棵空树,或者是具有下列性质的二叉树:它的左子树和右子树都是平衡二叉树，且左
子树和右子树的深度之差的绝对值不超过 1。
若将二叉树上结点的平衡因子 BF(Balance
Factor)定义为该结点的左子树的深度减去它的右子树的深度，则平衡二树上所有结点
的平衡因子只可能是-1.0和1。
只要二叉树上有一个结点的平衡因子的绝对值大于1
则该二叉树就是不平衡的。如图 9.11(a)所示为两棵平衡二叉树,而图911()所示为两
棵不平衡的二叉树,结点中的值为该结点的平衡因子。
*/

#include <iostream>
#include "string"
#include "cassert"
#include <stack>
using namespace std;

class AvlNode;
class Avl;
using ElemType = int;
std::stack<AvlNode *> s1;
std::stack<AvlNode *> s2;
void RotateR(AvlNode *&ptr);
void RotateL(AvlNode *&ptr);
void RotateLR(AvlNode *&ptr);
void RotateRL(AvlNode *&ptr);

class AvlNode // 只是一个树节点的定义
{
public:
    ElemType data;
    AvlNode *lchild; // 左子树
    AvlNode *rchild; // 右子树
    int score;       // 平衡因子
};
class Avl // 平衡二叉树
{
private:
    AvlNode *root;
    bool Insert1(AvlNode *&t, ElemType x);
    ElemType Min1(AvlNode *t);
    ElemType Max1(AvlNode *t);
    void Sort1(AvlNode *t);
    AvlNode *Search1(AvlNode *t, ElemType key);
    void MakeEmpty1(AvlNode **Avl);
    bool Remove1(AvlNode **t, ElemType key);
    bool RemoveAvl1(AvlNode *&t, ElemType key);

public:
    bool Insert(Avl &Avl, ElemType x);
    void InitTree(Avl &Avl);
    ElemType Min(Avl &Avl);
    ElemType Max(Avl &Avl);
    void Sort(Avl &Avl);
    bool Remove(Avl &Avl, ElemType key);
    AvlNode *Search(Avl &Avl, ElemType key);
    void MakeEmpty(Avl &Avl);
    bool RemoveAvl(Avl &avl, ElemType key);
};

void Avl::InitTree(Avl &Avl)
{
    Avl.root = NULL;
}
AvlNode *BuyNode(ElemType x)
{
    AvlNode *p = new (AvlNode);
    assert(p != NULL);
    p->data = x;
    p->lchild = p->rchild = NULL;
    p->score = 0;
    return p;
}
bool Avl::Insert1(AvlNode *&t, ElemType x)
{
    AvlNode *p = t;
    AvlNode *parent = NULL;
    while (p != NULL)
    {
        if (x == p->data)
        {
            return false;
        }
        parent = p;
        s1.push(parent);
        if (x < p->data)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }
    p = BuyNode(x);
    if (parent == NULL) // 如果是单独创建节点，将树的根节点链接上
    {
        t = p;
        return true;
    }
    if (x < parent->data)
        parent->lchild = p;
    else
        parent->rchild = p;
    while (!s1.empty()) // 判断栈是否为空
    {
        parent = s1.top(); // 栈底元素输出
        s1.pop();
        if (parent->lchild == p)
        {
            parent->score--;
        }
        else
        {
            parent->score++;
        }
        if (parent->score == 0)
        {
            break;
        }
        if (parent->score == 1 || parent->score == -1)
        {
            p = parent;
        }
        else // 平衡因子绝对值大于1
        {
            //////////////////平衡调整
            //////////////////旋转化
            int flag = (parent->score < 0) ? -1 : 1; // 判断父亲节点是的平衡因子
            if (p->score == flag)                    // 判断是否为同号
            {
                if (flag == -1) // 左高右低
                {
                    RotateR(parent); // 修改的是父母节点，修改完后，parent变为根节点
                }
                else
                {
                    RotateL(parent);
                }
            }
            else
            {
                if (flag == -1)
                {
                    RotateRL(parent);
                }
                else
                {
                    RotateLR(parent);
                }
                break;
            }
        }
    }
    if (s1.empty()) // parent是新的根节点
    {
        t = parent;
    }
    else // parent不是新的根节点,需要判断如何链接
    {
        AvlNode *q = s1.top();
        if (q->data > parent->data)
        {
            q->lchild = parent;
        }
        else
        {
            q->rchild = parent;
        }
    }
    return true;
}
bool Avl::Insert(Avl &Avl, ElemType x)
{
    return Insert1(Avl.root, x);
}
void RotateR(AvlNode *&ptr)
{
    // 旋转第一个不平衡的平衡因子
    // 先指向第一个不平衡的节点
    // 创建指针指向右
    AvlNode *subr = ptr;
    ptr = ptr->lchild;
    subr->lchild = ptr->rchild;
    ptr->rchild = subr;
    ptr->data = subr->score = 0;
}
void RotateL(AvlNode *&ptr)
{
    AvlNode *subL = ptr;
    ptr = subL->rchild;
    subL->rchild = ptr->lchild;
    ptr->lchild = subL;
    ptr->score = subL->score = 0;
}
void RotateLR(AvlNode *&ptr)
{
    // 双旋转，先左后右
    AvlNode *subr = ptr;
    AvlNode *subl;
    ptr = subr->lchild;
    subl = subr->lchild;
    subl->rchild = ptr->lchild;
    ptr->lchild = subl;
    if (ptr->score <= 0)
    {
        subl->score = 0;
    }
    else
    {
        subl->score = -1;
    }
    subr->lchild = ptr->rchild;
    ptr->rchild = subr;
    if (ptr->score == -1)
    {
        subr->score = 1;
    }
    else
    {
        ptr->score = 0;
    }
}
void RotateRL(AvlNode *&ptr)
{
    AvlNode *subr = ptr;
    AvlNode *subl = ptr->rchild;
    ptr = subr->lchild;

    subr->lchild = ptr->rchild;
    ptr->rchild = subr;
    if (ptr->score <= 0)
    {
        subl->score = 0;
    }
    else
    {
        subl->score = -1;
    }
    subl->rchild = ptr->lchild;
    ptr->lchild = subl;
}
void Avl::Sort(Avl &bst) // 排序，等于中序遍历
{
    Sort1(bst.root);
}
void Avl::Sort1(AvlNode *t)
{
    if (t != NULL)
    {
        Sort1(t->lchild);
        cout << t->data << " , ";
        Sort1(t->rchild);
    }
}
bool Avl::RemoveAvl(Avl &avl, ElemType key)
{
}
bool Avl::RemoveAvl1(AvlNode *&t, ElemType key)
{
    AvlNode *parent = NULL;
    AvlNode *p = t;
    while (p != NULL)
    {
        if (p->data == key)
            break;
        parent = p;
        s2.push(parent);
        if (key < p->data)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (p == NULL)
    {
        return false;
    }
    AvlNode *pparent;
    AvlNode *q; // 用于指向删除节点的子树
    int f;      // 区分左右的NULL
    // 此时的p已经指向了需要删除的节点
    //  将所有的情况分类为至少有一个子树是空和两个子树都为满的情况
    // 删除后还需要调整平衡因子
    if (p->lchild != NULL && p->rchild != NULL) // 都不为空
    {
        // 若需要删除的是中间节点
        // 找到该节点左子树最大的节点，替换
        // 然后删除该最大节点
        parent = p;
        q = p->lchild;
        while (q != NULL)
        {
            s2.push(parent);
            parent = q;
            q = q->rchild;
        }
        p->data = q->data;
        p = q; // 将p指向需要删除的末尾的节点
    }
    else
    {
        // q指向需要删除节点的子节点
        if (p->lchild != NULL) // 找一个临时的节点指向子树
        {
            q = p->lchild;
        }
        else
        {
            q = p->rchild;
        }
    }
    if (parent == NULL)
    {
        t = parent;
    }
    else
    {
        if (parent->lchild == p)
        {
            p->lchild = q;
            f = 0;
        }
        else
        {
            p->rchild = q;
            f = 1;
        }
        int link_flag=0;//-1链接左子树
                        //1链接右子树
        // 删除后调整平衡因子
        while (!s2.empty())
        {
            parent = s2.top();
            s2.pop();
            // 判断加减
            if (parent->lchild == q && f == 0)
            {
                parent->score--;
            }
            else
            {
                parent->score++;
            }
            if(!s2.empty())
            {
                pparent=s2.top();
                link_flag=(pparent->lchild==parent)?-1:1;
            }
            // 如果原本平衡因子为0，则不会印象平衡
            if (parent->score == -1 || parent->score == 1) // 说明原本的平衡因子为0，删除任意两边都不会影响，退出循环
            {
                break;
            }
            // 继续回溯
            if (parent->score == 0)
            {
                q = parent;
            }
            // 不平衡，则调整
            else
            {
                // 开始判断是左右两边。哪边不平衡
                int flag = 0; // 用于存储父节点的平衡因子符号
                if (parent->score < 0)
                {
                    int flag = -1;
                    q = parent->lchild;
                }
                else
                {
                    flag = 1;
                    q = parent->rchild;
                }
                // 判断分为单旋转和双旋转
                if (q->score == 0) // 单旋转
                {
                    if (flag == -1) // 右单旋转
                    {
                        RotateR(parent);
                        parent->score = 1;
                        parent->rchild->score = -1;
                    }
                    else
                    {
                        RotateL(parent);
                        parent->score = -1;
                        parent->lchild->score = 1;
                    }
                }
                // 如果父节点和子节点的平衡因子符号相同，则需要是单旋转
                if (q->score == flag)
                {
                    if (flag == -1) // 左高右低，右旋转
                    {
                        RotateR(parent);
                    }
                    else
                    {
                        RotateL(parent);
                    }
                }
                else
                {
                    if(flag==-1)
                    {
                        RotateLR(parent);
                    }
                    else
                    {
                        RotateRL(parent);
                    }
                    if(link_flag==1)
                    {
                        pparent->rchild=parent;
                    }
                    else
                    {
                        pparent->lchild=parent;
                    }
                }
            }
        }
        if (s2.empty())
        {
            t = parent;
        }
    }
    delete p;
    return true;
}

int main()
{
    Avl a1;
    a1.InitTree(a1);
    ElemType arry[] = {30, 20, 40, 10, 25};
    int num = sizeof(arry) / sizeof(arry[0]);
    for (int i = 0; i < num; i++)
    {
        a1.Insert(a1, arry[i]);
    }

    a1.Insert(a1, 5);
    a1.Sort(a1);
}