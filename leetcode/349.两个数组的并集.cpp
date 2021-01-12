class Solution {
public:
    // unordered_set
    // 空间 O(n)
    // 时间 O(n)
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> st1(nums1.begin(), nums1.end());
        unordered_set<int> st2;
        for (int n : nums2) {
            // if (st1.count(n) != 0) v.push_back(n);
            if (st1.find(n) != st1.end()) {
                st2.insert(n);  // 输出的每个元素一定是唯一的
            }
        }
        return vector<int>(st2.begin(), st2.end());
    }
};
