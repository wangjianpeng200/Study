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
//��ô��Ȼ������ȡ����Ԫ�ز����ظ�ȡ��д�����㷨��ʱ��for��Ҫ��startIndex��ʼ�������Ǵ�0��ʼ��
//����Ŀ����ֹ������forѭ������ֹ������ͬ�����Կ���ʡ����ֹ����

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, int startindex)
    {
        if (startindex >= nums.size())
        {
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        path.clear();
        result.clear();
        backtracking(nums, 0);
        result.push_back(std::vector<int>());
        return result;
    }
};