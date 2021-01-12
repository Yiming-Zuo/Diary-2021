// https://leetcode-cn.com/problems/two-sum/description/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 哈希表 unordered_map
        // 时间 O(n)
        // 空间 O(n)
        unordered_map<int, int> mp;
        vector res(2, -1);
        for (int i = 0; i < nums.size(); i++) {
            auto it = mp.find(target-nums[i]);
            if (it != mp.end()) {
                res[0] = it->second;
                res[1] = i;
            }
            mp[nums[i]] = i;
        }
        return res;
    }
};