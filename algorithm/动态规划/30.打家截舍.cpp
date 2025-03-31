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

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        int result1 = robrange(nums, 0, nums.size() - 2);
        int result2 = robrange(nums, 1, nums.size() - 1);
        return max(result1, result2);
    }

    int robrange(vector<int> &nums, int start, int end)
    {
        if (start == end)
            return nums[start];
        vector<int> dp(nums.size(), 0);
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++)
        {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
};