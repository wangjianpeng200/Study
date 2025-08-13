#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode *next;
};

class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        unordered_set<ListNode *> set;
        ListNode* cur=head;
        ListNode* res=nullptr;
        while(cur!=nullptr)
        {
            if(set.find(cur)!=set.end())
            {
                res=*set.find(cur);
                break;
            }
            set.insert(cur);
            cur=cur->next;
        }
        return res;
    }
};