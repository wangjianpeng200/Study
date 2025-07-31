#include<iostream>
#include<vector>
#include<queue>

using namespace std;


class Solution {
    public:
        int minSubArrayLen(int s, vector<int>& nums) {
            int result = INT32_MAX;
            int sum=0;
            int slow,fast=0;
            int sublength=0;
            for(;fast<nums.size();fast++)
            {
                sum+=nums[fast];
                //如果此时滑动窗口内的值已经大于了目标值则进入滑动窗口的管理
                while(sum>=s)
                {
                    sublength=fast-slow+1;
                    result=min(result,sublength);
                    sum-=nums[slow++]
                }   
            }
            return result==INT32_MAX?0:result;
        }
    };