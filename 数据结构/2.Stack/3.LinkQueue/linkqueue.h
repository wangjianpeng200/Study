#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

//队列先进先出
//链队列相当于尾进头出的线性表
#include<iostream>
#include<stdio.h>
#include<cassert>
#include<algorithm>
using namespace std;

#define STACK_INIT_SIZE 8
#define Elemtype int

class LinkQueue;
class Node;

class Node
{
    friend class LinkQueue;
    private:
    Elemtype data;
    Node* next;
};

class LinkQueue   
{
    private:
    Node *front;//队头指针
    Node *tail;//队尾指针
    public:
    void Init(LinkQueue &q);
    void EnLink(LinkQueue &q,Elemtype x);
    void Show(LinkQueue &q);
    void DeQueue(LinkQueue &q);//从尾部删除
};

#endif