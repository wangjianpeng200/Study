#ifndef _SCLIST_H_
#define _SCLIST_H_

// 链栈，是功能受限的线性表
// 只能进行头插和头删
// 没有头节点，也没有管理节点的first指针
#include <iostream>
#include <stdio.h>
#include <cassert>
#include <algorithm>
using namespace std;

#define STACK_INIT_SIZE 8
#define Export 8
#define Elemtype int

class LinkNode
{
private:
    Elemtype data;
    LinkNode *next;
};

typedef LinkNode *LinkStack;

#endif