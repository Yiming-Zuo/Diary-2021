class Solution {
public:
    // 模拟行为
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int l = 0, r = matrix[0].size() - 1, t = 0, b = matrix.size() - 1;
        int total = (r+1) * (b+1), num = 0;
        while (total > num) {
            for (int i = l; i <= r; i++) res.push_back(matrix[t][i]);
            if (++t > b) break;
            for (int i = t; i <= b; i++) res.push_back(matrix[i][r]);
            if (--r < l) break;
            for (int i = r; i >= l; i--) res.push_back(matrix[b][i]);
            if (--b < t) break;
            for (int i = b; i >= t; i--) res.push_back(matrix[i][l]);
            if (++l > r) break;
        }
        return res;
    }
};
