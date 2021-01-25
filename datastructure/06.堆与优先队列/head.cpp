#include <iostream>
#include <vector>

using namespace std;

// 1 手写最大堆
class MyHead {
public:
	MyHead() : size(0) {}
	// 插入元素：从下往上堆化
	// 因为树的高度不会超过log2n 所以时间复杂度 O(logn)
	void push(int val) {
		head[++size] = val;  // 从索引1开始存放数据，数组数量 = size + 1
		int i = size;  // 最后一个结点的索引
		while (i / 2 > 0 && head[i] > head[i / 2])
		{
			swap(head[i], head[i / 2]);
			i /= 2;
		}
	}
	// 移除堆顶元素
	void pop() {
		if (size == 0) return;
		head[1] = head[size];  // swim
		size--;
		headify(1);
	}
	// 移除堆顶元素后 从上往下堆化
	// 时间复杂度 O(logn)
	void headify(int i) {
		// !
		while (true) {
			int maxNode = i;
			if (2 * i <= size && head[i * 2] > head[i]) maxNode = i * 2;
			if (2 * i + 1 <= size && head[2 * i + 1] > head[maxNode]) maxNode = i * 2 + 1;  // 当前结点和它的左右子结点最大值的索引
			if (maxNode == i) break;
			swap(head[i], head[maxNode]);
			i = maxNode;  // 检查交换完值的子结点是否满足顶堆的性质
		}
	}
	// 建堆 时间复杂度 O(n)
	// 每个结点堆化时间复杂度O(logn) 一共 n/2个结点 n：堆中元素个数
	// 每个结点堆化的时间复杂度是O(h)
	// S = 1 * h + 2 * h-1 + 2^2 * h-2 + ... + 2^h-1 * 1
	// 2S =        2 * h   + 2^2 * h-1 + ... + 2^h-1 * 2 + 2^h * 1
	// S = 2 + 2^2 + ... + 2^h-1 + 2^h - h = 2 * 1-2^h/1 - 2 = -2(1-2^h) = 2^h+1-2-h
	// h = log2n
	// S = 2n-2-log2n = O(n)
	void build(int* arr, int l) {
		// 最后结点 n-1
		// 叶子结点是最后结点的子结点 (n-1)/2
		int idx = 1;
		for (int i = 0; i < l; i++) {
			this->head[idx++] = arr[i];
		}
		size = l;
		for (int i = size / 2; i > 0; i--) {
			headify(i);
		}
	}
	// 堆排序
	// 堆排序就是不断的取堆顶元素后将剩下的n-1个元素重新建堆,直到排序完成
	// 时间复杂度 O(n * logn)
	// 不稳定，堆顶结点交换时可能改变值相同数据的原始相对位置
	void sort(int arr[], int l) {
		build(arr, l);  // O(n)
		while (size > 0) {  // O(n * logn)
			swap(head[1], head[size--]);
			headify(1);  // O(logn)
		}
	}
private:
	int head[1000];
	int size;
};

// 2 手写最小堆
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

int main()
{

}
