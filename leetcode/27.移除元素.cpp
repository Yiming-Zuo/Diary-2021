
class Solution {
public:
    // 快慢指针法
    // 时间复杂度 O(n)
	// 用一个快指针和一个慢指针在一个for循环中实现在两个for循环中的工作
	// 时间复杂度 O(n2) -> O(n)
	// 适用于数组和链表
    int removeElement(vector<int>& nums, int val) {
        int i = 0;
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] != val) nums[i++] = nums[j];
        }
        return i;
    }
};
