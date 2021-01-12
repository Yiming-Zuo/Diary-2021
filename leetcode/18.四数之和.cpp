class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // 双指针
        // 三数之和基础上加了一个for循环
        // 时间 O(n3)
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        if (nums.size() < 4) return res;
        for (int i = 0; i <= nums.size()-4; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            for (int j = i + 1; j <= nums.size()-3; j++) {
                if (j > i + 1 && nums[j] == nums[j-1]) continue;
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum > target) right--;
                    else if (sum < target) left++;
                    else {
                        res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left+1]) left++;
                        while (left < right && nums[right] == nums[right-1]) right--;
                        left++;
                        right--;
                    }
                }
            }
        }
        return res;
    }
};