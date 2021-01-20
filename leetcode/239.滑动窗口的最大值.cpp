class Solution {
public:
    // 单调队列(递减)：单调队列不是维护窗口中的所有值，它只维护可能成为窗口中最大值的元素，并且保证队列中的值是递减的。
    // 滑动窗口的过程中队列不会为空，因为push的值大于队尾值时会替换这个值，否则直接push进队列。
	// 时间复杂度 O(n): nums里的数最多会被push和pop各一次
    class MyQueue {
    public:
        deque<int> que;  // 底层使用双向队列，因为push和pop需要比较队尾和队首的值
        // 当push值大于当前队尾值时，弹出当前队尾值，直到队列为空或者当前值小于队尾值，保证队列的递减性。
        void push(int x) { 
            while (!que.empty() && que.back() < x) que.pop_back();
            que.push_back(x);
        }
        // 如果要pop的值位于队首，则弹出。
        void pop(int x) {
            if (!que.empty() && que.front() == x) que.pop_front();
        }
        int front() {
            return que.front();
        }
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            que.push(nums[i]);
        }
        res.push_back(que.front());
        for (int i = k; i < nums.size(); i++) {
            que.push(nums[i]);
            que.pop(nums[i - k]);
            res.push_back(que.front());
        }
        return res;
    }
};
