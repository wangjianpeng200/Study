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
// ��ô��Ȼ������ȡ����Ԫ�ز����ظ�ȡ��д�����㷨��ʱ��for��Ҫ��startIndex��ʼ�������Ǵ�0��ʼ��
// ����Ŀ����ֹ������forѭ������ֹ������ͬ�����Կ���ʡ����ֹ����

class Solution
{
private:
    vector<vector<int>> result;
    vector<int> path;
    //需要手动压入空集合，否则会漏掉自己
    void backtracking_1(const vector<int> &nums, int startindex)
    {
        if (startindex >= nums.size())
        {
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking_1(nums, i + 1);
            path.pop_back();
        }
    }
    
    //不需要手动压入空集合，因为下面的for循环会把自己也加入到result中
    void backtracking_2(vector<int> &nums, int startIndex)
    {
        result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己
        if (startIndex >= nums.size())
        { // 终止条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            backtracking_2(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        path.clear();
        result.clear();
        backtracking(nums, 0);
        result.push_back(std::vector<int>());
        return result;
    }
};