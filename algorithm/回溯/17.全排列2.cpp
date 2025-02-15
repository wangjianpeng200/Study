//�����������ظ�Ԫ�ص����У���Ҫ��uesd���鼴ȥͬһ����أ���Ҫȥ���ݹ���ظ�

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
			if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) //ȥͬһ�����
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
		sort(nums.begin(), nums.end()); // ����
		vector<bool> used(nums.size(), false);
		backtracking(nums, used);
		return result;
	}
};
