#include"SCList.h"

Node* BuyNode(ElemType x)
{
    Node *s=new(Node);
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    return s;
}

void Node::InitSCList(List &list)
{
    Node *s=new(Node);
    assert(s!=NULL);
    list.first=s;
    list.last=s;
    list.last->next=list.first;
    list.size=0;
}

void Node::Push_back(List &list,ElemType x)
{
    Node *s=BuyNode(x);
    list.last->next=s;
    list.last=s;
    s->next=list.first;
    list.size++;
}

void Node::ShowList(List &list,ElemType x)
{
    Node *s=list.first->next;
    while(s!=list.first)//判断条件不同
    {
        cout<<s->data<<"  ";
        s=s->next;
    }
}

void Node::Push_front(List &list,ElemType x)
{
    Node *s=BuyNode(x);
    if (list.size=0)
    {
        list.last=s;
    }
    s->next=list.first->next;
    list.first->next=s;
    list.size++;
}

void pop_back(List *list)
{
    
}

void Node::Insert(List &list,ElemType x)
{
    Node *s=BuyNode(x);
    Node *p=list.first;
    while(p->next!=list.first && p->next->data<x)
    {
        p=p->next;
    }
    if(p==NULL)
    {
        list.last=s;
        s->next=list.first;
        list.size++;
    }
    else
    {
        s=p->next;
        p->next=s;
        list.size++;
    }
}