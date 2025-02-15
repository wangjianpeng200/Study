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

//类似于字符串的分割，但是需要判断的条件更多
//

class Solution {
private:
	vector<string> result;
	string path;
	//判断当前字串是否符合条件
	bool IsVaild(const string& s, int start, int end)
	{
		if (start > end) { //起始位置超过末端位置不合法
			return false;
		}
		if (s[start] == '0' && start != end) { // 0开头的数字不合法，但如果单独为0却合法
			return false;
		}
		int num = 0;
		for (int i = start; i <= end; i++) {
			if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
				return false;
			}
			num = num * 10 + (s[i] - '0');
			if (num > 255) { // 如果大于255了不合法
				return false;
			}
		}
		return true;
	}
	// startIndex: 搜索的起始位置，pointNum:添加逗点的数量
	void backingtracking(string& s, int startindex, int num)
	{
		if (num == 3)
		{
			if (IsVaild(s, startindex, s.size() - 1))
			{
				result.push_back(s);
			}
			return;
		}

		for (int i = startindex; i <= s.size(); i++)
		{
			if (IsVaild(s, startindex, i))
			{
				s.insert(s.begin() + i + 1, '.');
				num++;
				backingtracking(s, i + 2, num);
				num--;
				s.erase(s.begin() + i + 1);
			}
			else break;
		}
	}
public:
	vector<string> restoreIpAddresses(string s) {
		result.clear();
		if (s.size() < 4 || s.size() > 12) return result; //减枝操作
		backingtracking(s, 0, 0);
		return result;
	}
};