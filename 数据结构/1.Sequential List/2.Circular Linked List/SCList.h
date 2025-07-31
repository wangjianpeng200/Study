#ifndef _SCLIST_H_
#define _SCLIST_H_

#include<iostream>
#include<stdio.h>
#include<cassert>
using namespace std;

#define ElemType int
class Node;
typedef Node *PNode;
class List
{
    private:
    PNode first;
    PNode last;
    int size;
    public:
    friend Node;
};
Node* BuyNode(ElemType x);

class Node
{
    public:
    ElemType data;
    Node *next;
    void InitSCList(List &list);//初始化
    void Push_back(List &list,ElemType x);//尾插
    void Node::ShowList(List &list,ElemType x);//显示
    void Push_front(List &list,ElemType x);//头插
    void Insert(List &list,ElemType x);//插入
};

#endif
