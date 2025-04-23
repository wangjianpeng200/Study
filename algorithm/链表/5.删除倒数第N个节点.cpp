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
        ListNode* removeNthFromEnd(ListNode* head, int n) 
        {
            ListNode* _dummyList=new ListNode(0);
            _dummyList->next=head;
            ListNode* slow=_dummyList;
            ListNode* fast=_dummyList;
            for(int i=0;i<n;i++)
            {
                fast=fast->next;
            }
            while(fast->next!=NULL)
            {
                fast=fast->next;
                slow=slow->next;
            }
            slow=cur->next;
            return _dummyList->next;
        }
    };