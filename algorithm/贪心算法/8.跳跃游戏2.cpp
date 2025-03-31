class Solution {
    public:
        int jump(vector<int>& nums) {
            if (nums.size() == 1) return 0;
            int curDistance = 0;    // 当前覆盖最远距离下标
            int ans = 0;            // 记录走的最大步数
            int nextDistance = 0;   // 下一步覆盖最远距离下标
            for (int i = 0; i < nums.size(); i++) {
                nextDistance = max(nums[i] + i, nextDistance);  // 更新下一步覆盖最远距离下标
                if (i == curDistance) {                         // 遇到当前覆盖最远距离下标
                    ans++;                                  // 需要走下一步
                    curDistance = nextDistance;             // 更新当前覆盖最远距离下标（相当于加油了）
                    if (nextDistance >= nums.size() - 1) break;  // 当前覆盖最远距到达集合终点，不用做ans++操作了，直接结束
                }
            }
            return ans;
        }
    };







class Solution {
public:
    int jump(vector<int>& nums) {
        int nextcover = 0;
        int curcover=0
        int result = 0;
        if (nums.size() == 1)
        {
            return 0;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            nextcover = max(nums[i] + i, nextDistance);
            if (i == curcover)
            {
                result++;
                curcover = nextcover;
            }
            if (curcover >= nums.size() - 1)
            {
                break;
            }
        }
        return result;
    }
};