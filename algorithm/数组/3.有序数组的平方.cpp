#include<iostream>
#include<vector>
#include<queue>


class Solution {
    public:
        vector<int> sortedSquares(vector<int>& A) {
            int size=A.size();
            vector<int> result(size,0); //定义结果数组
            int right=size-1;
            int left=0; //定义左右指针
            for(int i=size-1;i>=0;i--) //从后往前遍历数组
            {
                if(A[left]*A[left]>A[right]*A[right]) //如果左边的平方大于右边的平方
                {
                    result[i]=A[left]*A[left]; //将左边的平方赋值给结果数组
                    left++; //左指针后移一位
                }
                else //如果右边的平方大于等于左边的平方
                {
                    result[i]=A[right]*A[right]; //将右边的平方赋值给结果数组
                    right--; //右指针前移一位
                }
            }
            return result;
        }
    };