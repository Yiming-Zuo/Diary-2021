class Solution {
public:
    // 滑动窗口
    // 根据子序列和大小情况不断调整子序列的起始位置和结束位置
    // O(n2) -> O(n)
    int minSubArrayLen(int s, vector<int>& nums) {
        // 滑动窗口
        // 时间复杂度 O(n)
        int i = 0;
        int len = 0;
        int result = INT32_MAX;
        int sum = 0;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= s) {  // 不断根据当前子序列的情况调整子序列的起始位置和结束位置
                len = j - i + 1;
                result = len < result ? len : result;
                sum -= nums[i++];
            }
        }
        return result = result != INT32_MAX ? result : 0;
        
    }
};

