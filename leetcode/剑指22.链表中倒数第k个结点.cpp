class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        // 快慢指针法
        ListNode *slow = head;
        ListNode *fast = head;
        while (k--) fast = fast->next;
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

