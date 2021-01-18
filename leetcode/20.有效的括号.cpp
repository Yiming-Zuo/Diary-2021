// 括号匹配是使用栈解决的经典问题。
class Solution {
public:
    // 1.栈+哈系表
    // 当栈顶匹配到相应的右括号时，出栈，否则入栈
    // 时间复杂度 O(n) 遍历了一遍字符串
    // 空间复杂度 O(n) 当都不匹配时全部入栈
    bool isValid1(string s) {
        stack<char> st;
        unordered_map<char, char> mp{{'(', ')'}, {'[', ']'}, {'{', '}'}};
        for (char c : s) {
            if (!st.empty() && mp[st.top()] == c) st.pop();
            else st.push(c);
        }
        return st.empty();
    }
    // 2.栈
    // 遇到左括号时，直接将其要匹配的右括号入栈
    // 遇到右括号直接与栈顶元素比对，如果相同则出栈
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            // 左括号入栈相匹配的右括号
            if (c == '(') st.push(')');
            else if (c == '[') st.push(']');
            else if (c == '{') st.push('}');
            // 右括号直接取栈顶元素开始匹配
            // 1. 多余的右括号，栈为空。
            // 2. 不匹配的左右括号，栈顶元素与右括号不相同
            else if (st.empty() || st.top() != c) return false;
            else st.pop();  // 栈顶元素与右括号相同，出栈。
        }
        return st.empty();  // 3. 多余的左括号，栈不为空。
    }
};