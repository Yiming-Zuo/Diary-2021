class Solution {
public:
    // KMP
    // 时间复杂度 O(n*m) -> O(n+m)
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        int _size = haystack.size();
        vector<int> next(getNext(needle));
        int j = 0;
        for (int i = 0; i < _size; i++) {
            while (j > 0 && haystack[i] != needle[j]) j = next[j-1];
            if (haystack[i] == needle[j]) j++;
            if (j == needle.size()) return i - needle.size() + 1;
        }
        return -1;
    }
    // 可以看成模式字符串的前缀来匹配模式字符串的过程
    // j是前缀的尾
    // i是后缀的尾
    vector<int> getNext(string &s) {
        int _size = s.size();
        vector<int> next(_size, 0);
        int j = 0;  // 前缀
        for (int i = 1; i < _size; i++) {  // 后缀
            while (j > 0 && s[i] != s[j]) j = next[j-1];
            if (s[i] == s[j]) j++;
            next[i] = j;
        }
        return next;
    }
};