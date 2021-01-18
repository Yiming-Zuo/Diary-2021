// 后缀表达式：不需要考虑运算的优先级，也可以看成二叉树的后序遍历。
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        // 遇到数字即入栈，遇到运算符取出两数字计算后重新入栈
        stack<int> st;
        for (string c : tokens) {
            if (c == "+" || c == "-" || c == "*" || c == "/") {
                int n1 = st.top();
                st.pop();
                int n2 = st.top();
                st.pop();
                if (c == "+") st.push(n2 + n1);  // n2是前面的数
                if (c == "-") st.push(n2 - n1);
                if (c == "*") st.push(n2 * n1);
                if (c == "/") st.push(n2 / n1);
            } else {
                st.push(stoi(c));
            }
        }
        return st.top();
    }
};