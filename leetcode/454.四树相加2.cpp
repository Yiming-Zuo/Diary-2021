class Solution {
public:
    // 索引法 map
    // key:两数之和 value:出现次数
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> mp;
        for (int a : A) {
            for (int b : B) {
                mp[a+b]++;
            }
        }
        int count = 0;
        for (int c : C) {
            for (int d : D) {
                if (mp[-c-d]) count += mp[-c-d];
            }
        }
        return count;
    }
};