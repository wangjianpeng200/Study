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

//��ȫ���ĵ��������У�����Ҫ��Ҫ���������������
//1.��Ҫȥ�أ�����Ϊ��Ѱ�ҵ����������Բ��ܶ������������
//2.ʹ�ù�ϣ��������ȥ�أ�ʹ�����鵱��hash��

//����������2�е�ȥ�����Ƚ�

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
        }
        int used[201] = { 0 };
        for (int i = startIndex; i < nums.size(); i++)
        {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1)
            {
                continue;
            }
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};



class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    un
    void backtracking(vector<int>& nums, int startIndex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
        }
        int used[201] = { 0 };
        for (int i = startIndex; i < nums.size(); i++)
        {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1)
            {
                continue;
            }
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};
