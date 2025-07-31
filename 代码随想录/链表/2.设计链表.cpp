#include<iostream>
using namespace std;

class MyLinkedList
{
    public:
        struct LinkedNode
        {
            int val
            LinkedNode* next;
            LinkedNode(int val):val(val),next(nullptr){}   //init的作用
        };

        MyLinkedList()
        {
            _dummyHead=new LinkedNode(0); //头结点
            _size=0;
        }

        int get(int index) {
            if (index > (_size - 1) || index < 0) {
                return -1;
            }
            LinkedNode* cur = _dummyHead->next;
            while(index--){ // 如果--index 就会陷入死循环
                cur = cur->next;
            }
            return cur->val;
        }

        void addAtHead(int val) {
            LinkedNode* newNode = new LinkedNode(val);
            newNode->next = _dummyHead->next;
            _dummyHead->next = newNode;
            _size++;
        }

        
    private:
        LinkedNode* _dummyHead; //头结点
        int _size; //链表的大小

    
}