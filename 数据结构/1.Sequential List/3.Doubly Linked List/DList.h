#ifndef _SCLIST_H_
#define _SCLIST_H_

#include<iostream>
#include<stdio.h>
#include<cassert>
using namespace std;

using ElemType = int;
typedef Node* PNode;

class Node
{
    public:
    ElemType data;
    PNode next;
    PNode prio;
    //每当涉及尾节点的时候需要单独进行考虑
    Node* BuyNode(ElemType x);
    void InitDList(List &list);//初始化
    void Push_back(List &list,ElemType x);//尾插,先链接前驱。
    void Push_front(List &list,ElemType x);//头插,头插要考虑一种特别的情况(链中节点为空)，先连接再断开
    void Pop_bcak(List &list);//尾部删除
    void Pop_front(List &list);//头部删除，要考虑特殊情况（删除的是否为最后一个节点，如是为最后一个节点，需要将last指向）
    void Insert(List &list,ElemType x);//插入,如果在中间没有插入，就需要判断是否需要尾部插入
    Node* Find(List &list,ElemType key);//查找，返回地址
    void Delete_val(List &list,ElemType key);//按值删除,需要考虑删除尾部数据的情况
    void Sort(List &list);//排序，从小到大
    void Resver(List &list);//逆置双向链表
    void Clear(List &list);//清空
    void Destory(List &list);//催还链表
    int Length(List &list);//返回链表的长度
    void ShowList(List &list);//显示
};

class List
{
    private:
    PNode first;
    PNode last;
    int size;
    friend Node;
};

void Select(List &list);

#endif