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


//�����3�������ǿ����ظ�ѡȡԪ��


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
            path.push_back(candidates[start]);
            sum += candidates[start];
            backtracking(candidates,target,sum,i)
            sum-= candidates[start];
            path.pop_bcak(candidates[start]);
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        backtracking(candidates, target, 0, 0);
        return result;
    }
};