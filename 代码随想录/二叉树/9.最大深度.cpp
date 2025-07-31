// 左右中
class Solution
{
public:
    int getdepth(TreeNode *node)
    {
        if (node == NULL)
            return 0;
        int leftdepth = getdepth(node->left);       // 左
        int rightdepth = getdepth(node->right);     // 右
        int depth = 1 + max(leftdepth, rightdepth); // 中
        return depth;
    }
    int maxDepth(TreeNode *root)
    {
        return getdepth(root);
    }
};

// 中左右

class Solution
{
public:
    int result;
    void getdepth(TreeNode *node, int depth)
    {
        result = depth > result ? depth : result; // 中
        if (node->left == NULL && node->right == NULL)
            return;
        if (node->left)
        { // 左
            getdepth(node->left, depth + 1);
        }
        if (node->right)
        { // 右
            getdepth(node->right, depth + 1);
        }
        return;
    }
    int maxDepth(TreeNode *root)
    {
        result = 0;
        if (root == 0)
            return result;
        getdepth(root, 1);
        return result;
    }
};