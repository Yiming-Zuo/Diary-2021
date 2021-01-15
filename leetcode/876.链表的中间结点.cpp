class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // 快慢指针
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast) {
            if (fast->next == NULL) return slow;  // 奇
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;  // 偶
    }
};
