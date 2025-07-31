#include<iostream>
using namespace std;
#include<vector>
#include<queue>


class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int start=0;
            int fin=nums.size()-1;
            int mid;
            while(start<=fin)
            {
                mid=(fin+start)/2;
                if(target>nums[mid])
                {
                    start=mid;
                    start++;
                }
                else if(target<nums[mid])
                {
                    fin=mid;
                    fin--;
                }
                else  //在中间找到了
                {
                    return mid;
                }
            }
            return -1;
        }
    };