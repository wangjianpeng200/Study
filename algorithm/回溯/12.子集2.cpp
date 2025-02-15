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
//���������2�еģ������ظ�Ԫ�أ���Ҫȥ�ء������������ڷָ��ִ��е���ֹ����
//1.ʹ��startindexȥ��
//2.ʹ��uesd����ȥ��

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
            if (i > startindex && nums[i] == nums[i - 1])//���i�������startindex����Ϊ�˱��������ϵ��ظ�ȥ��
            {
                continue;
            }
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        result.push_back(vector<int>());
        return result;
    }
};