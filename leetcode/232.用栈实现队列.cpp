// 1
// pops栈中有元素时，pushs栈不能倒入元素
// pushs栈倒入元素时要一次性倒完
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        stIn.push(x);
    }
    
    // 如果out不为空直接返回并删除out顶的值，如果out为空先将in里的值都push进out
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (stIn.empty() && stOut.empty()) return -1;
        if (stOut.empty()) {
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
        }
        }
        int num = stOut.top();
        stOut.pop();
        return num;
    }
    
    /** Get the front element. */
    int peek() {
        int num = this->pop();
        stOut.push(num);  // 函数复用
        return num;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (stIn.empty() && stOut.empty());
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


// 2
// 每次操作结束都将st2的值放回st1
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
        st1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (st1.empty() && st2.empty()) return -1;
        while (!st1.empty()) {
            st2.push(st1.top());
            st1.pop();
        }
        int num = st2.top();
        st2.pop();
        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
        return num;
    }
    
    /** Get the front element. */
    int peek() {
        if (st1.empty() && st2.empty()) return -1;
        while (!st1.empty()) {
            st2.push(st1.top());
            st1.pop();
        }
        int num = st2.top();
        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
        return num;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (st1.empty() && st2.empty());
    }
private:
    stack<int> st1;
    stack<int> st2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */