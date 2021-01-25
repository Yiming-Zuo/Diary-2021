class Solution {
    // 1.手写大顶堆
    // 时间复杂度 O(n * logn)
    int head[10000];
    int size;
public:
    Solution() : size(0) {}
    // 上浮 时间复杂度 O(logn)
    void push(int val) {
        head[++size] = val;
        int i = size;
        while (i / 2 > 0 && head[i / 2] < head[i]) {
            swap(head[i], head[i / 2]);
            i /= 2;
        }
    }
    void pop() {
        if (size == 0) return;
        head[1] = head[size--];
        headify(1);
    }
    // 堆化 时间复杂度 O(logn)
    void headify(int i) {
        while (true) {
            int maxNode = i;
            if (i * 2 <= size && head[i * 2] > head[i]) maxNode = i * 2;
            if (i * 2 + 1 <= size && head[i * 2 + 1] > head[maxNode]) maxNode = i * 2 + 1;
            if (maxNode == i) break;
            swap(head[i], head[maxNode]);
            i = maxNode;
        }
    }
    vector<int> getLeastNumbers1(vector<int>& arr, int k) {
        for (int n : arr) {
            push(n);
            if (size > k) {
                pop();
            }
        }
        return vector<int>(head+1, head + k + 1);
    }
    // 2.优先队列
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int, vector<int>, less<int>> que;  // 大顶堆
        for (int n : arr) {
            que.push(n);
            if (que.size() > k) {
                que.pop();
            }
        }
        vector<int> res;
        while (k--) {
            res.push_back(que.top());
            que.pop();
        }
        return res;
    }
};