#include<iostream>
#include<vector>
#include<algorithm>
using namespace

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    vector<int> result;
    int count = 0;
    int MAX_COUNT = 0;
    TreeNode* pre = NULL;
    void BST(TreeNode* node)
    {
        if (node == NULL) return;
        BST(node->left);
        if (pre == NULL)  //��pre�ڵ����ж��Ƿ�Ϊ�����ĵ�һ���ڵ�
        {
            count++;
        }
        else
        {
            if (pre->val == node->val)
            {
                count++;
            }
        }
        if (count == MAX_COUNT)  //���Ƶ������򽫸ýڵ����
        {
            result.push_back(node->val);
        }
        if (count > MAX_COUNT)  //���Ƶ���������մ�ʱ�Ľ��
        {
            result.clear();
            result.push_back(node->val);
        }
        MAX_COUNT = max(count, MAX_COUNT);
        BST(node->right);
        return;
    }
    vector<int> findMode(TreeNode* root) {
        BST(root);
        return result;
    }
};
