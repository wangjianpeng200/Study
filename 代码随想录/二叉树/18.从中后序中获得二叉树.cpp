#include<iostream>
#include<vector>
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
private:
    // �������䣺[inorderBegin, inorderEnd)����������[postorderBegin, postorderEnd)
    // TreeNode* traversal(vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& postorder, int postorderBegin, int postorderEnd)
    // {
    //     // �߽�����
    //     if (postorderBegin == postorderEnd)
    //         return NULL;

    //     // ��������еĸ��ڵ�
    //     int rootvalue = postorder[postorderEnd - 1];
    //     TreeNode* root = new TreeNode(rootvalue);

    //     if (postorderEnd - postorderBegin == 1) return root;

    //     // �����������Ѱ�Ҹ��ڵ㣬�ָ���������
    //     int segment = inorderBegin;
    //     for (; segment < inorderEnd; segment++)
    //     {
    //         if (inorder[segment] == rootvalue)
    //             break;
    //     }

    //     // �ָ�����������飬������
    //     int inorderbegin_left = inorderBegin;
    //     int inorderend_left = segment;
    //     // �ָ�����������飬������
    //     int inorderbegin_right = segment + 1;
    //     int inorderend_right = inorderEnd;

    //     // �ָ�����������,������
    //     int postorderbegin_left = postorderBegin;
    //     int postorderend_left = postorderBegin + (segment - inorderBegin);

    //     // �ָ����������飬������
    //     int postorderbegin_right = postorderBegin + (segment - inorderBegin);
    //     int postorderend_right = postorderEnd - 1;

    //     root->left = traversal(inorder, inorderbegin_left, inorderend_left, postorder, postorderbegin_left, postorderend_left);
    //     root->right = traversal(inorder, inorderbegin_right, inorderend_right, postorder, postorderbegin_right, postorderend_right);

    //     return root;
    // }




    TreeNode* traversal(vector<int> inorder,vector<int> postorder,int inorderbegin,int inorderend,int postorderbegin,int postorderend)
    {
        if(postorderbegin == postorderend)
            return NULL;

        int rootvalue = postorder[postorderend - 1];
        TreeNode* root = new TreeNode(rootvalue);

        int inorder_segment;
        for(int i=inorderbegin;i<inorderend;i++)
        {
            if(inorder[i]==rootvalue)
            {
                inorder_segment=i;
                break;
            }
        }

        int inorder_left_begin=inorderbegin;
        int inorder_left_end=inorder_segment;

        int inorder_right_begin=inorder_segment+1;
        int inorder_right_end=inorderend;;

        int postorder_left_begin=postorderbegin;
        int postorder_left_end=postorderbegin+(inorder_segment-inorderbegin);

        int postorder_right_begin=postorder_left_end;
        int postorder_left_end=postorderend-1;

        int root->left=traversal(inorder,postorder,inorder_left_begin,inorder_left_end,postorder_left_begin,postorder_left_end);;
        int root->right=traversal(inorder,postorder,inorder_right_begin,inorder_right_end,postorder_right_begin,postorder_right_end);
        
        return root;

    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        if (inorder.size() == 0 || postorder.size() == 0)
            return NULL;
        return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
};