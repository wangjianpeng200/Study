#include"seqqueue.h"

bool SeqQueue::IsEmpty(SeqQueue &q)
{
    if(q.front=q.tail)
    {
        return true;
    }
    return false;
}

bool SeqQueue::IsFull(SeqQueue &q)
{
    if(q.tail>=MAXSIZE)
    {
        return true;
    }
    return false;
}

void SeqQueue::Init(SeqQueue &q)
{
    q.base=new Elemtype(MAXSIZE);
    assert(base!=NULL);
    q.front=q.tail=0;
}

void SeqQueue::EnLink(SeqQueue &q,Elemtype x)
{
    if(IsFull)
    {
        cout<<"该顺序队列已满"<<endl;
        return;
    }
    q.base[q.tail++]=x;
}

void SeqQueue::Show(SeqQueue &q)
{
    for(int i=q.front;i<=q.tail;i++)
    {
        cout<<"栈底>"<<q.front<<" ";
    }
}

void SeqQueue::DeQueue(SeqQueue &q)
{
    //front++
}

void SeqQueue::GetHead(SeqQueue &q)
{
    if(IsEmpty(q))
    {
        cout<<"该队列为空，无法获取队头元素"<<endl;
        return;
    }

}