#include<iostream>
#include<vector>
using namespace

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//方法一：
class Solution {
public:
    TreeNode* pre = NULL;
    void BST(TreeNode* node, int val)
    {
        //如果遇到了空节点
        if (!node && pre)
        {
            if (val < pre->val)
            {
                TreeNode* temp = new TreeNode(val);
                pre->left = temp;
                return;
            }
        }
        else
        {
            if (val > pre->val)
            {
                TreeNode* temp = new TreeNode(val);
                pre->right = temp;
                return;
            }
        }
        //如果遇到的节点有值
        if (val < node->val)
        {
            pre = node;
            BST(node->left, val);
        }
        if (val > node->val)
        {
            pre = node;
            BST(node->right, val);

        }
        return;
    }
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root)
        {
            return new TreeNode(val);
        }
        BST(root, val);
        return root;
    }
};


//方法二：
class Solution {
private:
    TreeNode* parent;
    void traversal(TreeNode* cur, int val) {
        if (cur == NULL) {
            TreeNode* node = new TreeNode(val);
            if (val > parent->val) parent->right = node;
            else parent->left = node;
            return;
        }
        parent = cur;
        if (cur->val > val) traversal(cur->left, val);
        if (cur->val < val) traversal(cur->right, val);
        return;
    }

public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        parent = new TreeNode(0);
        if (root == NULL) {
            root = new TreeNode(val);
        }
        traversal(root, val);
        return root;
    }
};
