#include<iostream>
using namespace std;

class Solution {
private:
    vector<string> result;
    vector<int> path;
    void traversal(TreeNode* node, vector<int>& path, vector<string>& result) 
    {
        path.push_back(cur->val);
        if (cur->left == NULL && cur->right == NULL)
        {
            string sPath;
            for (int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }
        if (cur->left) { // �� 
            traversal(cur->left, path, result);
            path.pop_back(); // ����
        }
        if (cur->right) { // ��
            traversal(cur->right, path, result);
            path.pop_back(); // ����
        }
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return result;
        traversal(root, path, result);
        return result;
    }

};