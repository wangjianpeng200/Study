//可以使用回溯，但是需要去重
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//注意在特殊示例下，sun超过int数据最大位限制的情况
class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums,int startindex,long long sum,int target)
    {
        if (path.size() >= 4)
        {
            if (sum == target)
            {
                result.push_back(path);
            }
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            if (i > startindex && nums[i - 1] == nums[i])
            {
                continue;
            }
            path.push_back(nums[i]);
            sum += nums[i];
            backtracking(nums, i + 1, sum, target);
            sum -= nums[i];
            path.pop_back();
        }
    } 
    vector<vector<int>> fourSum(vector<int>& nums, int target) 
    {
        path.clear();
        result.clear();
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, 0, target);
        return result;
    }
};