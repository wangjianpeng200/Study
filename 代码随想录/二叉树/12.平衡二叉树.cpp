#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


class Solution {
public:
    int getHeight(TreeNode* node) {
       if(node=NULL)
       {
         return 0; // 空节点高度为0
       }
       int leftHeight=getHeight(node->left); // 左
       if(leftHeight==-1) return -1; // 说明左子树已经不是平衡二叉树了，直接返回-1
       int rightHeight=getHeight(node->right); // 右
       if(rightHeight==-1) return -1; // 说明右子树已经不是平衡二叉树了，直接返回-1
       return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
    }
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};