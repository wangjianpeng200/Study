#include<iostream>


  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL || head->next==NULL)
        {
            return head;
        }
        ListNode* _dummyHead=new ListNode(0); //头结点
        _dummyHead->next=head; //头结点指向头节点
        ListNode* pre=_dummyHead; //前一个节点
        ListNode* cur=head;
        while(cur!=NULL && cur->next!=NULL)
        {
            pre->next=cur->next; 
            cur->next=cur->next->next; //当前节点的下一个节点指向当前节点的下一个节点的下一个节点
            pre->next->next=cur; //前一个节点的下一个节点的下一个节点指向当前节点
            pre=cur; //前一个节点指向当前节点
            cur=cur->next; //当前节点指向当前节点的下一个节点
        }
        ListNode* result=_dummyHead->next; //结果指向头结点的下一个节点
        delete _dummyHead; //删除头结点
        return result; //返回结果
        
    }
};