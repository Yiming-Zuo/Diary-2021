class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // 哈希法 数组
        int record[26] = {0};
        for (int c : magazine) record[c-'a']++;
        for (int c : ransomNote) {
            if (record[c-'a'] == 0) return false;
            record[c-'a']--;
        }
        return true;
    }
};