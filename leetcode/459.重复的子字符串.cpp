class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        return (s + s).find(s, 1) != s.size();  // s+s中屏蔽第一个循环节
        // 如果不是循环节构成的子字符串，返回第二个s的位置 = s.size()
    }
    // KMP
    // 字符串长度 - 字符串的最长相等前后缀的长度 = 一个循环节
    // 如果循环节的长度是字符串长度的倍数，那么这个字符串就是由一个循环节重复构成的字符串
    bool repeatedSubstringPattern1(string s) {
        int _size = s.size();
        vector<int> next(getNext(s));
        if (next[_size-1] == 0) return false;
        return !(_size % (_size - next[_size-1]));
    }
    vector<int> getNext(string &s) {
        int _size = s.size();
        vector<int> next(_size, 0);
        int j = 0;
        for (int i = 1; i < _size; i++) {
            while (j > 0 && s[i] != s[j]) j = next[j-1];
            if (s[i] == s[j]) j++;
            next[i] = j;
        }
        return next;
    }
};