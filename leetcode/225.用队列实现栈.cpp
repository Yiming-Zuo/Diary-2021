// 2
// 一个队列实现栈
// 每次push时将之前所有元素移动到新元素后面
// 入栈 O(n) 出栈 O(1)
class MyStack {
    queue<int> que;
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        int _size = que.size();
        que.push(x);
        while (_size--) {
            que.push(que.front());
            que.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int num = que.front();
        que.pop();
        return num;
    }
    
    /** Get the top element. */
    int top() {
        return (que.front());
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// 1
// 两个队列实现栈
// 用一个辅助队列备份对最后一个元素前的所有元素
// 将que1除最后一个元素以外的元素弹出备份到que2，然后弹出最后一个元素后将que2重新导入que1，清空que2.
class MyStack {
public:
    queue<int> que1;
    queue<int> que2;
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        que1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int _size = que1.size();
        while (_size-- != 1) {
            que2.push(que1.front());
            que1.pop();
        }
        int res = que1.front();
        que1.pop();
        que1 = que2;
        while (!que2.empty()) {  // 清空que2
            que2.pop();
        }
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return que1.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return (que1.empty() && que2.empty());
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */