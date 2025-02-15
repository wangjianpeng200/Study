#ifndef _SCLIST_H_
#define _SCLIST_H_

#include<iostream>
#include<stdio.h>
#include<cassert>
#include<algorithm>
using namespace std;

#define STACK_INIT_SIZE 8
#define Export 8
#define Elemtype int

class Seqstack
{
private:
    Elemtype *base;
    int capcaity;
    int top;
public:
    void Init(Seqstack &seq);
    bool IsFull(Seqstack &seq);
    bool IsEmpty(Seqstack &seq);
    void Push(Seqstack &seq,Elemtype x); 
    void Show(Seqstack &seq);
    void Pop(Seqstack &seq);
    Elemtype GetTop(Seqstack &seq);
    bool Inc(Seqstack &seq);
};


#endif