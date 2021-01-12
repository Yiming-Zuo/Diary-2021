class Solution {
public:
    // 快慢指针(有循环发生)
    // 空间复杂度 O(1)
    bool isHappy(int n) {
            int slow = n;
            int fast = n;
        do {
            slow = getSum(slow);
            fast = getSum(fast);
            fast = getSum(fast);
        } while (slow != fast);
        return fast == 1;
    }
    // unordered_set
    bool isHappy1(int n) {
        unordered_set<int> st;
        while (1) {
            int sum = getSum(n);
            if (sum == 1) return true;
            if (st.find(sum) != st.end()) return false;  // 最后都会无线循环
            st.insert(sum);
            n = sum;
        }
    }
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }
};
