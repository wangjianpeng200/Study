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

//找全部的递增子序列，其主要需要解决的问题有两点
//1.需要去重，但是为了寻找递增序列所以不能对数组进行排序
//2.使用哈希表来辅助去重，使用数组当作hash表

//可以与数组2中的去重做比较

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
        }
        int used[201] = { 0 };
        for (int i = startIndex; i < nums.size(); i++)
        {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1)
            {
                continue;
            }
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};



class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    un
    void backtracking(vector<int>& nums, int startIndex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
        }
        int used[201] = { 0 };
        for (int i = startIndex; i < nums.size(); i++)
        {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1)
            {
                continue;
            }
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};
