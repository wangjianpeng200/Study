#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <functional>
#include <climits>
#include <cstdlib>
#include <numeric>

using namespace std;
//类似于组合2中的，包含重复元素，需要去重。但是又类似于分割字串中的终止条件
//1.使用startindex去重
//2.使用uesd数组去重

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, int startindex)
    {
        if (startindex >= nums.size())
        {
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            if (i > startindex && nums[i] == nums[i - 1])//这个i必须大于startindex，是为了避免把深度上的重复去掉
            {
                continue;
            }
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        result.push_back(vector<int>());
        return result;
    }
};