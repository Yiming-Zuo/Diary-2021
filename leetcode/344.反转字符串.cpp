class Solution {
public:
    void reverseString(vector<char>& s) {
        // 双指针
        // 时间复杂度 O(n)
        int l = 0, r = s.size() - 1;
        while (l < r) {
            swap(s[l], s[r]);
            /* 按位异或
            s[l] ^= s[r];
            s[r] ^= s[l];
            s[l] ^= s[r];
            */
            l++;
            r--;
        }
    }
};
