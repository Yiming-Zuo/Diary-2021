class Solution {
public:
    // 快慢指针
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (true) {
            if (fast == NULL || fast->next == NULL) return NULL;
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) break;
            // 两结点相遇时 f=2s f=s+nb
            // s=nb f=2nb
            // node=a+nb=a+s
            // s已经走了nb了，只要再走a就可以到达结点除
        }
        // f和s往前走a步后，fs相遇，此时就是结点处
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

