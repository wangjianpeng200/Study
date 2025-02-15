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


//与组合相比，区别在于candidates中的元素有重复的，所以需要进行去重的操作。
//回溯的组合可以看作一棵树的深度遍历，去重是去同一层的重复，而不是深度上的重复


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
			if (i > start && candidates[i] == candidates[i - 1])
			{
				continue;
			}
			path.push_back(candidates[i]);
			sum += candidates[i];
			backtracking(candidates, target, sum, i);
			sum -= candidates[i];
			path.pop_back();
		}
	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		path.clear();
		result.clear();
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, target, 0, 0);
		return result;
	}
};