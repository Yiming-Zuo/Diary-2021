class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 双指针
        // 时间 O(n2)
        // 空间 O(1)
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int left = nums.size() - 1;
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            for (int j = i + 1; j < nums.size(); j++) {
                if (j > i + 1 && nums[j] == nums[j-1]) continue;
                int sum = nums[i] + nums[j];
                // int left = nums.size() - 1;  // 超出时间限制
                while (left != nums.size() || left != j) {
                    if (nums[left] == -sum) {
                        res.push_back({nums[i], nums[j], nums[left]});
                        break;
                    }
                    else if (nums[left] < -sum) {
                        if (left == nums.size() - 1) break;
                        else left++;
                    }  // 不能++
                    else if (nums[left] > -sum) {
                        if (left == j) break;
                        else left--;
                    };
                }
            }
        }
        return res;
    }
    // 双指针+遍历
    // 超出时间限制
    vector<vector<int>> threeSum1(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i < nums.size()) {
            if (i > 0 && nums[i] == nums[i-1]) {  // 去重
                i++;
                continue;
            }
            int j = i+1;
            while (j < nums.size()) {
                if (j > i+1 && nums[j] == nums[j-1]) {  // 去重
                    j++;
                    continue;
                }
                int sum = nums[i] + nums[j];
                for (int k = j+1; k < nums.size(); k++) {
                    if (k > j+1 && nums[k] == nums[k-1]) continue;  // 去重
                    if (nums[k] == -sum) res.push_back({nums[i], nums[j], nums[k]});
                }
                j++;
            }
            i++;
        }
        for (auto &v : res) sort(v.begin(), v.end());
        return res;
    }
};