#include"DList.h"

Node* Node::BuyNode(ElemType x)
{
    Node *s=new(Node);
    assert(s!=NULL);
    s->data=x;
    s->prio=s->next=NULL;
    return s;
}

void Node::InitDList(List &list)
{
    Node *s=new(Node);
    assert(s!=NULL);
    list.first=list.last=s;
    list.last->next=NULL;
    list.first->prio=NULL;//前指针域也要初始化
}

void Node::Push_back(List &list,ElemType x)//不用分情况
{
    Node *s=BuyNode(x);
    s->prio=list.last->next;
    list.last->next=s;
    list.last=s;
    list.size++;
}

void Node::Push_front(List &list,ElemType x)
{
    Node *s=BuyNode(x);
    s->next=list.first->next;
    if(list.size==0)
    {
    list.last=s;
    }
    else
    {
    s->next->prio=s;//在size为空，会出现问题
    }
    s->prio=list.first;
    list.first->next=s;
    list.size++;
}

void Node::Pop_bcak(List &list)
{
    if(list.size==0)
    {
        cout<<"链表为空，不能直接删除"<<endl;
        return;
    }
    Node *s=list.last;
    list.last=list.last->prio;
    list.last->next=NULL;
    delete s;
    list.size--;
}

void Node::Pop_front(List &list)
{
    if(list.size==0)
    {
        cout<<"链表为空，不能直接删除"<<endl;
        return;
    }
    Node *s=list.first->next;
    if(list.first->next=list.last)
    {
        list.last=list.first;
        list.last->next=NULL;
    }
    else
    {
        list.first->next=s->next;
        s->next->prio=s->prio;
    }
    delete s;
    list.size--;
}

void Node::Insert(List &list,ElemType x)
{
    
    Node *s=list.first;
    while(s->next!=NULL && x>s->next->data)
    {
        s=s->next;
    }
    if(s->next==NULL)
    {
        Push_back(list,x);
    }
    else
    {
        Node *p=BuyNode(x);
        p->next=s->next;
        p->next->prio=s;
        p->next=s;
        s->prio=p;
        list.size++;
    }
}

Node* Node::Find(List &list,ElemType key)
{
    if(list.size==0)
    {
        cout<<"链表为空，查找失败"<<endl;
        return;
    }
    Node *s=list.first;
    while(s!=NULL && key!=s->data)
    {
        s=s->next;
    }
    if(s=NULL)
    {
        cout<<"未查找到该数"<<endl;
        return;
    }
    return s;
}

void Node::Delete_val(List &list,ElemType key)
{
    if (list.size==0)
    {
        cout<<"链表为空，不能按值删除"<<endl;
        return;
    }
    Node *s=Find(list,key);
    if(s=list.last)
    {
        Pop_bcak(list);
    }
    else
    {
    s->next->prio=s->prio;
    s->prio=s->next;
    delete s;
    list.size--;
    }
}

void Node::Sort(List &list)
{
    if(list.size==0 || list.size==1)
    {
        return;
    }
    Node *p=list.first->next;
    Node *q=p->next;
    list.last=p;
    p->next=NULL;
    q->prio=NULL;
    while(q!=NULL)
    {
        p=q;
        q=q->next;
        Node *s=list.first;
        while(s->next!=NULL && p->data>s->next->data)
        {
            s=s->next;
        }
        if(s=NULL)
        {
            p->prio=list.last;
            list.last->next=p;
            list.last=p;
        }
        else
        {
            p->next=s->next;
            p->next->prio=s;
            p->next=s;
            s->prio=p;
        }
    }
}

void Node::Resver(List &list)
{
     if(list.size==0 || list.size==1)
    {
        return;
    }
    Node *p=list.first->next;
    Node *q=p->next;
    list.last=p;
    p->next=NULL;
    q->prio=NULL;
    while(q!=NULL)
    {
        p=q;
        q=q->next;
        p->next=list.first->next;
        p->next->prio=p;
        list.first->next=p;
        p->prio=list.first;
    }
}

void Node::Clear(List &list)//18.11
{
    if(list.size==0)
    {
        return;
    }
    Node *s=list.first->next;
    while(s->next!=NULL)
    {
        s->next->prio=list.first;
        list.first->next=s->next;
        delete s;
        s=list.first->next;
    }
    delete s;
    list.last=list.first;
    list.first=NULL;
    list.size=0;
}

void Node::Destory(List &list)
{
    Clear(list);
    delete list.first;
    list.first=list.last=NULL;
}

int Node::Length(List &list)
{
    return list.size;
}

void Node::ShowList(List &list)
{
    if(list.size==0)
    {
        cout<<"该双链表为空"<<endl;
        return;
    }
    Node *s=list.first->next;
    while(s!=NULL)
    {
        cout<<s->data<<"  ";
        s=s->next;
    }
}

// void Select(List &list)
// {
//     while(1)
//     {
//         int x=0;
//         cout<<"请输入编号，选择功能"<<endl;
//         cin>>x;
//         switch (x)
//         {
//         case 1: list.
//             break;
        
//         default:
//             break;
//         }
//     }
// }