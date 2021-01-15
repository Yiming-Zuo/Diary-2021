class Solution {
public:
    // 双指针
    ListNode* reverseList1(ListNode* head) {
        ListNode *pre = NULL;
        ListNode *cur = head;
        while (cur) {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
    // 递归1: 递归反转node->next以后的结点后链接node
    ListNode* reverseList2(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *node = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return node;  // 返回的是结束条件返回的值
    }
    // 递归2: 递归反转(pre, cur)
    ListNode* reverseList3(ListNode* head) {
        // 和双指针逻辑一样
        ListNode *pre = NULL;
        ListNode *cur = head;
        return recur(pre, cur);
    }
    ListNode* recur(ListNode* pre, ListNode* cur) {
        if (cur == NULL) return pre;
        ListNode *tmp = cur->next;
        cur->next = pre;
        return recur(cur, tmp);
    }
};