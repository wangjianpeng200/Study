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


class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1);  //dp[i]的含义是    dp数组在i的最大乘机
        dp[2] = 1;
        for (int i = 3; i <= n; i++) { //从3开始计算
            for (int j = i / 2; j < i; j++)
            {
                dp[i] = max(dp[i], max(dp[i-j] * j), j * (i - j));
            }
        }
        return dp[n];
    }
};