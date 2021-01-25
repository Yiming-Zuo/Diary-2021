class Solution {
public:
    int nthUglyNumber(int n) {
        // 小顶堆
        priority_queue<long, vector<long>, greater<long>> que;
        long res = 1;
        que.push(1);
        // n--
        while (n--) {
            que.push(res * 2);
            que.push(res * 3);
            que.push(res * 5);
            res = que.top();
            que.pop();
            while (!que.empty() && que.top() == res) {
                que.pop();
            }
        }
        return res;
    }
};