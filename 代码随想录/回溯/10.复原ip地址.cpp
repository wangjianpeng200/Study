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

// �������ַ����ķָ������Ҫ�жϵ���������
//

// class Solution {
// private:
// 	vector<string> result;
// 	string path;
// 	//�жϵ�ǰ�ִ��Ƿ��������
// 	bool IsVaild(const string& s, int start, int end)
// 	{
// 		if (start > end) { //��ʼλ�ó���ĩ��λ�ò��Ϸ�
// 			return false;
// 		}
// 		if (s[start] == '0' && start != end) { // 0��ͷ�����ֲ��Ϸ������������Ϊ0ȴ�Ϸ�
// 			return false;
// 		}
// 		int num = 0;
// 		for (int i = start; i <= end; i++) {
// 			if (s[i] > '9' || s[i] < '0') { // �����������ַ����Ϸ�
// 				return false;
// 			}
// 			num = num * 10 + (s[i] - '0');
// 			if (num > 255) { // �������255�˲��Ϸ�
// 				return false;
// 			}
// 		}
// 		return true;
// 	}
// 	// startIndex: ��������ʼλ�ã�pointNum:���Ӷ��������
// 	void backingtracking(string& s, int startindex, int num)
// 	{
// 		if (num == 3)
// 		{
// 			if (IsVaild(s, startindex, s.size() - 1))
// 			{
// 				result.push_back(s);
// 			}
// 			return;
// 		}

// 		for (int i = startindex; i <= s.size(); i++)
// 		{
// 			if (IsVaild(s, startindex, i))
// 			{
// 				s.insert(s.begin() + i + 1, '.');
// 				num++;
// 				backingtracking(s, i + 2, num);
// 				num--;
// 				s.erase(s.begin() + i + 1);
// 			}
// 			else break;
// 		}
// 	}
// public:
// 	vector<string> restoreIpAddresses(string s) {
// 		result.clear();
// 		if (s.size() < 4 || s.size() > 12) return result; //��֦����
// 		backingtracking(s, 0, 0);
// 		return result;
// 	}
// };

class Solution
{
private:
	vector<string> result;
	string path;
	bool IsVaild(const string &s, int start, int end)
	{
		if (start > end)
			return false; // 如果起始位置大于结束位置，说明这段无效
		if (s[start] == '0' && start != end)
		{ // 0开头的数字不合法,但是0可以单独做一个数字
			return false;
		}
		int num=0;
		for (int i = start; i <= end; i++)
		{
			if (s[i] > '9' || s[i] < '0') // 不是数字，直接返回false
			{
				return false;
			}
			num = num * 10 + (s[i] - '0'); // 数字转为整数类型的变量-------------------------
			if(num>255) // 如果数字大于255，直接返回false
				return false;
		}
	}
	void backingtracking(string & s, int startindex, int num)
	{
		if(num==3)
		{
			IsVaild(s, startindex, s.size() - 1);
			result.push_back(s);
		}
		for (int i = startindex; i < s.size(); i++)  //i本身就是开始的位置
		{
			IsVaild(s, startindex, i);
			{
				s.insert(s.begin() + i + 1, '.');
				num++;
				backingtracking(s, i + 2);
				num--;
				s.erase(s.begin() + i + 1);
			}
		}
		else break;
	}

public:
	vector<string> restoreIpAddresses(string s)
	{
		result.clear();
		if (s.size() < 4 || s.size() > 12)
			return result;
		backingtracking(s, 0, 0);
		return result;
	}
};