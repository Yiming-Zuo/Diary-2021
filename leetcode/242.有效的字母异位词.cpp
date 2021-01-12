// https://leetcode-cn.com/problems/valid-anagram/
class Solution {
public:
    bool isAnagram1(string s, string t) {
        // 排序法
        // 时间复杂度O(nlogn)
        sort(s.begin(), s.end());  // 时间复杂度O(nlogn)
        sort(t.begin(), t.end());
        return s == t;
    }
    bool isAnagram2(string s, string t) {
        // 哈系表1
        // 空间 O(n)
        // 时间 O(n)
        if (s.size() != t.size()) return false;
        unordered_map<char, int> map;
        for (char c : s) map[c]++;
        for (char c : t) map[c]--;
        for (auto it : map) {
            if (it.second != 0) return false;
        }
        return true;
    }
    bool isAnagram3(string s, string t) {
        // 哈系表2
        // 空间 O(n)
        // 时间 O(n)
        if (s.size() != t.size()) return false;
        unordered_map<char, int> map;
        for (char c : s) map[c]++;
        for (char c : t) {
            if (--map[c] == -1) return false;
        }
        return true;
    }
    bool isAnagram(string s, string t) {
            // 数组
            // 空间 O(1)
            // 时间 O(n)
            vector<int> v(26, 0);
            for (char c : s) {  // a 97 A 65
                v[c - 'a']++;
            }
            for (char c : t) v[c - 'a']--;
            for (int i : v) {
                if (i != 0) return false;
            }
            return true;
        }
};
