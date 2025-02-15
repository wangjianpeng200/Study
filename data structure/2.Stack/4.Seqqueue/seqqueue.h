#ifndef _SEQQUEUE_H_
#define _SEQQUEUE_H_

#include<iostream>
#include<stdio.h>
#include<cassert>
#include<algorithm>
using namespace std;

#define MAXSIZE 8
#define Elemtype int
//会出现假空的情况
class SeqQueue
{
    private:
    Elemtype *base;//指向有效的队列空间
    int front;//指向头的下标
    int tail;//指向队尾的下个一个的下标
    public:
    void Init(SeqQueue &q);
    void EnLink(SeqQueue &q,Elemtype x);
    void Show(SeqQueue &q);
    void DeQueue(SeqQueue &q);//从尾部删除
    bool IsEmpty(SeqQueue &q);//判断该队列是否为空
    bool IsFull(SeqQueue &q);//判断队列是否为满
    void GetHead(SeqQueue &q);//获得栈头元素
};
#endif 