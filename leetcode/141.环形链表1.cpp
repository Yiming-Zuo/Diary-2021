class Solution {
public:
    // 快慢指针
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next) {  // 每一次循环两指针相差距离1，n此后两指针相遇。
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

