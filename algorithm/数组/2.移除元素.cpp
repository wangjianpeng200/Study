#include<iostream>
#include<vector>
#include<queue>

class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int slow=0; //定义快慢指针
            for(fast=0;fast<nums.size();fast++) //遍历数组
            {
                if(nums[fast]!=val) //如果当前元素不等于val
                {
                    nums[slow]=nums[fast]; //将当前元素赋值给慢指针指向的元素
                    slow++; //慢指针后移一位
                }
            }
        }
    }; 