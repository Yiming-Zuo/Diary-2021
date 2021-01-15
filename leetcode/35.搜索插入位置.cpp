class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 二分法
        // 时间复杂度 O(logn)
        int left = 0, right = nums.size();  // 左闭右开 [left, right)
        while (left < right) {  // [n, n)无效
            int mid = left + (right - left) / 2;  // 防止溢出
            if (nums[mid] > target) right = mid;  // [left, mid)
            else if (nums[mid] < target) left = mid + 1;  // [mid+1, right]
            else return mid;
        }
        // target在所有元素之前 [0,0)
        // 在所有元素之后 [nums.size(), nums.size())
        // 在两元素之间 [target+, target+]
        return right;
    }
};

