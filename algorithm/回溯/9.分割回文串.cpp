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
//�ѷָ������ϣ���Ҫ�оٳ����ַ������еķָʽ��
//�����жϸ÷ָ�������Ƿ��������������Ҫ�ڷָ�ʱ�жϣ����������ֱ�������÷ָʽ

//class Solution
//{
//private:
//	vector<vector<string>> result;
//	vector<string> path//����и����Ӵ�
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
//			if (isPalindrome(s, startindex, i))//�����������ǰ�Ӵ�Ϊ���Ĵ�
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