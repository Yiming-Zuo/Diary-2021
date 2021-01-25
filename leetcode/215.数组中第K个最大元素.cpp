class Solution {
public:
    //1.手写小顶堆
    void headify(vector<int> &vec, int index) {
        int i = index;
        while (true) {
            int minNode = i;
            if (i * 2 + 1 < vec.size() && vec[i * 2 + 1] < vec[i]) minNode = i * 2 + 1;
            if (i * 2 + 2 < vec.size() && vec[i * 2 + 2] < vec[minNode]) minNode = i * 2 + 2;
            if (minNode == i) break;
            swap(vec[i], vec[minNode]);
            i = minNode;
        }
    }
    void buildHead(vector<int> &vec) {
        for (int i = vec.size() / 2 - 1; i >= 0; i--) {
            headify(vec, i);
        }
    }
    int findKthLargest1(vector<int>& nums, int k) {
        vector<int> vec(nums.begin(), nums.begin() + k);
        buildHead(vec);
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] < vec[0]) continue;
            vec[0] = nums[i];
            headify(vec, 0);
        }
        return vec[0];
    }
    // 2.优先队列
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pri_que;
        for (int n : nums) {
            pri_que.push(n);
            if (pri_que.size() > k) pri_que.pop();
        }
        return pri_que.top();
    }
};