#include"linkqueue.h"

void LinkQueue::Init(LinkQueue &q)
{
    q.front=q.tail=new(Node);
    assert(q.front!=NULL);
    q.front->next=NULL;
}

void LinkQueue::EnLink(LinkQueue &q,Elemtype x)
{
    Node *s=new(Node);
    s->data=x;
    s->next=NULL;
    q.tail->next=s;
    q.tail=s;
}

void LinkQueue::Show(LinkQueue &q)
{
    Node *s=q.front->next;
    if(q.front=q.tail)
    {
        cout<<"该表为空,无法输出"<<endl;
        return;
    }
    cout<<"frnot>";
    while(s!=NULL)
    {
        cout<<s->data<<"   ";
        s=s->next;
    }
    cout<<"<tial";
}

void LinkQueue::DeQueue(LinkQueue &q)
{
    if(q.front=q.tail)
    {
        cout<<"该队列为空"<<endl;
        return;
    }
    Node *s=q.front->next;
    q.front->next=s->next;
    delete s;

//     while(s->next!=q.tail)
//     {
//         s=s->next;
//     }
//     delete q.tail;
//     q.tail=s;
// }