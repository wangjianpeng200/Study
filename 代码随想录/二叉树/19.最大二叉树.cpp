#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

    
    
class Solution
{
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums)
    {
        if(nums.size()==0)
        {
            return nullptr;
        }
        TreeNode* root=new TreeNode(0);
        if(nums.size()==1)
        {
            root->val=nums[0];
            return root;
        }
        else 
        {
            auto max_ptr=max_element(nums.begin(),nums.end());
            root->val=*max_ptr;
            vector<int> left(nums.begin(),max_ptr);
            vector<int> end(max_ptr+1,nums.end());
            
            root->left=constructMaximumBinaryTree(left);
            root->right=constructMaximumBinaryTree(end);

            return root;
        }
    }
};