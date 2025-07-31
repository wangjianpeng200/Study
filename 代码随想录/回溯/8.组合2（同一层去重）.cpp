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


//�������ȣ���������candidates�е�Ԫ�����ظ��ģ�������Ҫ����ȥ�صĲ�����
//���ݵ���Ͽ��Կ���һ��������ȱ�����ȥ����ȥͬһ����ظ�������������ϵ��ظ�


//判断前一个值是否相等
class Solution
{
public:
	vector<vector<int>> result; // ������
	vector<int> path;           // ·�����
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


//使用数组
class Solution {
private:
	vector<vector<int>> result;
	vector<int> path;
	void backtracking(vector<int>& candidates, int target, int sum, int startIndex, vector<bool>& used) {
		if (sum == target) {
			result.push_back(path);
			return;
		}
		for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
			// used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
			// used[i - 1] == false，说明同一树层candidates[i - 1]使用过
			// 要对同一树层使用过的元素进行跳过
			if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)    //如果是false就说明是同一层
			{
				continue;
			}
			sum += candidates[i];
			path.push_back(candidates[i]);
			used[i] = true;
			backtracking(candidates, target, sum, i + 1, used); // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次
			used[i] = false;
			sum -= candidates[i];
			path.pop_back();
		}
	}

public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<bool> used(candidates.size(), false);   //初始化全部为false
		path.clear();
		result.clear();
		// 首先把给candidates排序，让其相同的元素都挨在一起。
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, target, 0, 0, used);    //used传入函数
		return result;
	}
};



// class Solution
// {
// public:
// 	vector<vector<int>> result; 
// 	vector<int> path;           
// 	void backtracking(const vector<int>& candidates, int target, int sum, int start)
// 	{
// 		if(sum)
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