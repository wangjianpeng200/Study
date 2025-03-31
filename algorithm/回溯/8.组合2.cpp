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


// //�������ȣ���������candidates�е�Ԫ�����ظ��ģ�������Ҫ����ȥ�صĲ�����
// //���ݵ���Ͽ��Կ���һ��������ȱ�����ȥ����ȥͬһ����ظ�������������ϵ��ظ�


// class Solution
// {
// public:
// 	vector<vector<int>> result; // ������
// 	vector<int> path;           // ·�����
// 	void backtracking(const vector<int>& candidates, int target, int sum, int start)
// 	{
// 		if (sum >= target)
// 		{
// 			if (sum == target)
// 			{
// 				result.push_back(path);
// 			}
// 			return;
// 		}
// 		for (int i = start; i < candidates.size(); i++)
// 		{
// 			if (i > start && candidates[i] == candidates[i - 1])
// 			{
// 				continue;
// 			}
// 			path.push_back(candidates[i]);
// 			sum += candidates[i];
// 			backtracking(candidates, target, sum, i);
// 			sum -= candidates[i];
// 			path.pop_back();
// 		}
// 	}
// 	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
// 	{
// 		path.clear();
// 		result.clear();
// 		sort(candidates.begin(), candidates.end());
// 		backtracking(candidates, target, 0, 0);
// 		return result;
// 	}
// };


class Solution
{
public:
	vector<vector<int>> result; 
	vector<int> path;           
	void backtracking(const vector<int>& candidates, int target, int sum, int start)
	{
		if(sum)
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