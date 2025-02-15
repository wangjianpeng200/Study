//在数组中有重复元素的排列，需要用uesd数组即去同一层的重，还要去出递归的重复

class Solution {
private:
	vector<vector<int>> result;
	vector<int> path;
	backtracking(const vector<int> nums, vector<int>& used)
	{
		if (path.size() == nums.size())
		{
			result.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); i++)
		{
			if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) //去同一层的重
			{
				continue;
			}
			if (used[i] == false)
			{
				path.push_back(nums[i]);
				used[i] = true;
				backtracking(nums, used);
				path.pop_back();
				used[i] = false;
			}
		}
	}
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		result.clear();
		path.clear();
		sort(nums.begin(), nums.end()); // 排序
		vector<bool> used(nums.size(), false);
		backtracking(nums, used);
		return result;
	}
};
