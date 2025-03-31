class Solution {
    public:
        int wiggleMaxLength(vector<int>& nums) {
            if(nums.size()<=1)
            {
                return nums.size();
            }
            int pre=0;
            int cur=0;
            int result=1;
            for(int i=0;i<nums.size()-1;i++) //不需要遍历最后一个元素，因为默认数组结尾有一个摆动
            {
                cur=nums[i+1]-nums[i];
                if((pre<=0 && cur>0) || (pre>=0 && cur<0))
                {
                    result++;
                    pre=cur;  //在有摆动时才更新，避免单调有平坡情况
                }
            }
            return result;
        }
    };