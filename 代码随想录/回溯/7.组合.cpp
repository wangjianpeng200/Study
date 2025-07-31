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


//与组合3的区别是可以重复选取元素


class Solution
{
public:
    vector<vector<int>> result; // 保存结果
    vector<int> path;           // 路径结果
    void backtracking(const vector<int>& candidates, int target, int sum, int start)
    {
        if (sum >= target)
        {
            if (sum == target)
            {
                result.push_back(path);
            }
            return;
        }
        for (int i = start; i < candidates.size(); i++)
        {
            path.push_back(candidates[start]);
            sum += candidates[start];
            backtracking(candidates,target,sum,i)
            sum-= candidates[start];
            path.pop_bcak(candidates[start]);
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        backtracking(candidates, target, 0, 0);
        return result;
    }
};