class Solution {
public:
    // 1.栈
    // 时间复杂度 O(n)
    // 空间复杂度 O(n)
    string removeDuplicates1(string S) {
        stack<char> st;
        for (char c : S) {
            if (!st.empty() && st.top() == c) st.pop();
            else st.push(c);
        }
        string res = "";
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
    // 2. 字符串模拟栈
    // 时间复杂度 O(n)
    // 空间复杂度 O(n)
    string removeDuplicates2(string S) {
        string res = "";
        for (char c : S) {
            if (res.empty() || res.back() != c) res.push_back(c);
            else res.pop_back();
        }
        return res;
    }
    // 3. 计数法
    // 时间复杂度 O(n)
    // 空间复杂度 O(1)
    string removeDuplicates(string S) {
        int count = 0;  // count是新字符串的下标
        for (char c : S) {
            if (count == 0 || S[count-1] != c) S[count++] = c;
            else count--;  // 如果与前一个字符重复，c回退一位，遍历继续，c相当于落后两位。
        }
        S.resize(count);
        return S;
    }
};