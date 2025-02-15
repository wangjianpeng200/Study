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
//那么既然是无序，取过的元素不会重复取，写回溯算法的时候，for就要从startIndex开始，而不是从0开始！
//该题目的终止条件和for循环的终止条件相同，所以可以省略终止条件

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
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        path.clear();
        result.clear();
        backtracking(nums, 0);
        result.push_back(std::vector<int>());
        return result;
    }
};