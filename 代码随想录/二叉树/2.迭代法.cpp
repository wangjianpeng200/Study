#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    // 前序遍历，压入stack的顺序是中右左
    vector<int> preorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == NULL)
            return result;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top(); // 中
            st.pop();
            result.push_back(node->val);
            if (node->right)          // 如果不为空
                st.push(node->right); // 右（空节点不入栈）
            if (node->left)
                st.push(node->left); // 左（空节点不入栈）
        }
        return result;
    }

    // 中序遍历
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur != NULL || !st.empty())
        {
            if (cur != NULL)
            {                    // 指针来访问节点，访问到最底层
                st.push(cur);    // 将访问的节点放进栈
                cur = cur->left; // 左
            }
            else
            {
                cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                st.pop();
                result.push_back(cur->val); // 中
                cur = cur->right;           // 右
            }
        }
        return result;
    }



    //后序遍历
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == NULL) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->left) st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            if (node->right) st.push(node->right); // 空节点不入栈
        }
        reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
        return result;
    }
};