
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 有两种方法
// 1.双指针法，先排序，两个指针在左右两端，中间移动的指针，通过判断相加的和与目标制的大小关系来移动指针
// 三个指针相当于a b c，需要对三个指针去重
//i为a，left为b，right为c
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end()); // 排序
        for (int i = 0; i < nums.size(); i++)
        {
             // 如果a是正数，a<b<c，不可能形成和为0的三元组，如果是target同样也可以比较
            if (nums[i] > 0)
            {
                return result;
            }
            if (i > 0 && nums[i] == nums[i - 1]) // a去重
            {
                continue;
            }
            int left = i + 1;  //left每一次循环都需要重新赋值，从i+1开始
            int right = nums.size() - 1;
            while (right > left)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1])
                        right--; // c去重
                    while (right > left && nums[left] == nums[left + 1])
                        left++; // b去重

                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking(vector<int>& nums, int startindex, int sum, int target) {
        if (path.size() == 3) {
            if (sum == target) {
                result.push_back(path);
                return;
            }
            return;
        }

        for (int i = startindex; i < nums.size(); i++) {
            // 去重逻辑
            if (i > startindex && nums[i] == nums[i - 1]) {
                continue;
            }

            path.push_back(nums[i]);
            sum += nums[i];

            backtracking(nums, i + 1, sum, target);

            sum -= nums[i];
            path.pop_back();
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        path.clear();
        result.clear();
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, 0, 0);
        return result;
    }
};