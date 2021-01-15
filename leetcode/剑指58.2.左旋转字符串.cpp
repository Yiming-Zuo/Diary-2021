class Solution {
public:
    string reverseLeftWords(string s, int n) {
        // 局部反转+整体反转
        // 时间复杂度 O(n)
        if (n > s.size()) return s;
        reverse(s.begin(), s.begin()+n);
        reverse(s.begin()+n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};
