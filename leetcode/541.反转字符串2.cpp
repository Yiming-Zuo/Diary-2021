class Solution {
public:
    string reverseStr(string s, int k) {
        // 模拟
        // 固定规律一段一段处理字符串->使用for循环
        for (int i = 0; i < s.size(); i += 2*k) {
            if (i + k <= s.size()) reverse(s.begin()+i, s.begin()+i+k);
            else reverse(s.begin()+i, s.end());
        }
        return s;
    }
};
