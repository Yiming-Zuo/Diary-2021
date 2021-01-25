typedef pair<int, int> PAIR;
class Solution {
public:
    class comparsion {
    public:
        // public
        // 运算符重载
        bool operator()(const PAIR v1, const PAIR v2) {
            return v1.second > v2.second;
        }
    };
    // 1.优先队列
    // 时间复杂度 O(n*logk)
    // 空间复杂度 O(n)
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int n : nums) {
            mp[n]++;
        }
        priority_queue<PAIR, vector<PAIR>, comparsion> que;
        vector<int> vec;
        for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
            que.push(*it);
            if (que.size() > k) que.pop();
        }
        while (k--) {
            vec.push_back(que.top().first);
            que.pop();
        }
        return vec;
    }
    // 2 使用multimap key: 次数 value: 值
    vector<int> topKFrequent2(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        multimap<int, int, greater<int>> mp;  // multimap没有重载[]
        vector<int> res;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) { 
            if (i > 0 && nums[i] != nums[i-1]) {
                mp.insert(PAIR(count, nums[i-1]));
                count = 1;
            } else {
                count++;
            }
        }
        mp.insert(PAIR(count, nums[nums.size()-1]));
        // map双向迭代器 只能++ --
        map<int, int, greater<int>>:: iterator it = mp.begin();
        while (k--) {
            res.push_back(it->second);
            it++;
        }
        return res;
    }
    // 3 数组排序 + 哈希
    // 数组排序后遍历 哈希记录每个数出现的次数 将map转换为vector进行value排序，取出前k个值
    // 或者 key = 次数 value = 值
    // 时间复杂度 O(n * logn)
    // 空间复杂度 O(n)
    vector<int> topKFrequent1(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());  // n * logn
        unordered_map<int, int> mp;
        vector<int> res;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {  // n
            if (i > 0 && nums[i] != nums[i-1]) {
                mp[nums[i-1]] = count;
                count = 1;
            } else {
                count++;
            }
        }
        mp[nums[nums.size()-1]] = count;
        // 把map转换成vector按value排序
        vector<PAIR> v(mp.begin(), mp.end());
        sort(v.begin(), v.end(), this->cmp);  // n * logn
        for (int i = 0; i < k; i++) {
            res.push_back(v[i].first);
        }
        return res;
    }
    static bool cmp(const PAIR &k1, const PAIR &k2) {
        return k1.second > k2.second;
    }
};