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
//把分割想成组合，需要列举出该字符串所有的分割方式。
//但是判断该分割情况下是否满足回文条件需要在分割时判断，如果不满足直接跳过该分割方式

//class Solution
//{
//private:
//	vector<vector<string>> result;
//	vector<string> path//存放切割后的子串
//		bool isPalindrome(const string& s, int start, int end)
//	{
//		for (i = start, j = end; i < j; i++, j--)
//		{
//			if (s[i] != s[j];)
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	void backtracking(const string& s, int startindex)
//	{
//		if (startindex >= s.size())
//		{
//			result.push_back(path);
//			return;
//		}
//		for (int i = startindex; i < s.size(); i++)
//		{
//			if (isPalindrome(s, startindex, i))//如果成立，则当前子串为回文串
//			{
//				string str = s.substr(startindex, i - startindex + 1);
//				path.push_back(str);
//			}
//			else
//			{
//				continue;
//			}
//			backtracking(s, i + 1);
//			psth.pop_back();
//		}
//	}
//public:
//	vector<vector<string>> partition(string s) {
//		result.clear();
//		path.clear();
//		backtracking(s, 0);
//		return result;
//	}
//};



class Solution
{
private:
	vector<vector<string>> result;
	vector<string> path
	bool isPalindrome(const string& s, int start, int end)
	{
		
		for (int i = start,j=end; i < j; i++,j--)
		{
			if (s[i] != s[j])
			{
				return false;
			}
			return true;
		}
	}
	void backtracking(const string& s, int startindex)
	{
		if (startindex >= s.size())
		{
			result.push_back(path);
			return 
		}
		for (int i = startindex; i < s.size(); i++)
		{
			if (isPalindrome(s, startIndex, i))
			{
				string str = s.substr(startindex, i - startIndex + 1);
				path.push_back(str);
			}
			else
			{
				continue;
			}
		}
	}
public:
	vector<vector<string>> partition(string s) {
		result.clear();
		path.clear();
		backtracking(s, 0);
		return result;
	}
};