class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 模拟行为
        // 时间复杂度 O(n2)
        // 空间复杂度 O(n2)
        vector<vector<int>> res(n, vector<int>(n, 0));
        int num = 1;
        int l = 0, r = n - 1, t = 0, b = n - 1;
        while (true) {
            for (int i = l; i <= r; i++) res[t][i] = num++;  // 注意边界问题
            if (++t > b) break;
            for (int i = t; i <= b; i++) res[i][r] = num++;
            if (--r < l) break;
            for (int i = r; i >= l; i--) res[b][i] = num++;
            if (--b < t) break;
            for (int i = b; i >= t; i--) res[i][l] = num++;
            if (++l > r) break;
        }
        return res;
    }
};

