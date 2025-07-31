class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            ListNode* temp;
            ListNode* cur=head;
            ListNode* pre=NULL;
            while(cur!=NULL)
            {
                temp=cur->next;
                cur->next=pre;
                pre=cur;
                cur=temp;
            }
            return pre;
        }
    };