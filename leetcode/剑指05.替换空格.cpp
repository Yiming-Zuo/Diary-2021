class Solution {
public:
    // 双指针原地修改
    // 统计原字符串中空格数量，由此来确定扩充字符串的大小。
    // 倒序遍历修改扩充后字符串。
    // 时间复杂度O(N): 遍历统计空格数量、遍历修改字符串
    // 空间复杂度O(1)
    string replaceSpace(string s) {
        int count = 0, len = s.size();
        for (auto c : s) {
            if (c == ' ') count++;
        }
        s.resize(len + 2 * count);
        for (int i = len-1, j = s.size()-1; i<j; i--) {
            if (s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            } else {
                s[j--] = s[i];
            }
        }
        return s;
    }
    // String 内置算法
    // int find(const char c)
    // string& replace(int pos, int n, const string str)  替换从pos开始n个字符为字符串str
    string replaceSpace(string s) {
        int pos = s.find(' ');
        while (pos != -1) {
            s.replace(pos, 1, "%20");  // 会引起额外的移动，时间复杂度很高
            pos = s.find(' ');   
        }
        return s;
    }
    // 开辟新数组
    // 时间复杂度O(N)
    // 空间复杂度O(N)
    string replaceSpace(string s) {
        string new_s;
        for (auto c : s) {
            if (' ' == c) new_s += "%20";
            else new_s += c;
        }
        return new_s;
    }
};
