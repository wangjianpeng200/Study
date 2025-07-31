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
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        int j = s.size() - 1;
        for (int i = g.size() - 1; i >= 0; i--)
        {
            if (j >= 0 && s[j] >= g[i])
            {
                result++;
                j--;
            }
        }
        return result;
    }
};