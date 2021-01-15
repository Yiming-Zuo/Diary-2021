class Solution {
public:
    // 先整体反转再局部反转
    string reverseWords(string s) {
        if (s.empty()) return s;
        // 1 双指针移除多余空格
        int slow = 0, fast = 0;
        while (s[fast] == ' ' && fast < s.size()) fast++;  // 去掉字符串前面空格
        while (fast < s.size()) {  // 去掉字符串中间空格
            if (fast-1 > 0 && s[fast] == s[fast-1] && s[fast] == ' ') {
                fast++;
                continue;
            }
            else {
                s[slow++] = s[fast++];
            }
        }
        if (s[slow-1] == ' ') s.resize(slow-1);  // 去掉字符串后面空格
        else s.resize(slow);
        // 2 反转整个字符串
        reverseWord(s, 0, s.size()-1);
        // 3 反转每个单词
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                end = i - 1;
                reverseWord(s, start, end);
                start = i + 1;
            }
        }
        end = s.size()-1;
        reverseWord(s, start, end);
        return s;
    }
    void reverseWord(string &s, int start, int end) {
        int l = start, r = end;
        while (l < r) {
            swap(s[l], s[r]);
            l++;
            r--;
        }
    }
};
