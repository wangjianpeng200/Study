//不要想复杂，就是把每一个节点都遍历到，然后判断

class Solution {
public:
    int leftleaves(TreeNode* node)
    {
      if(node==NULL) return 0;
      if (node->left == NULL && node->right== NULL) return 0;

      int left_num=leftleaves(node->left);
      if(node->left!=NULL && node->left->left==NULL && node->left->right==NULL)
      {
        left_num=node->left->val;
      }


      int right_num=leftleaves(node->right);
    


    }

    int sumOfLeftLeaves(TreeNode* root) {

    }
};