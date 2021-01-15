class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 虚拟头结点
        // 使用虚拟头结点将移除头结点和移除其它结点两种情况的操作方式统一
        while (head != NULL && head->val == val) {
           head = head->next;
        }
        ListNode *dummyNode = new ListNode(0);  // 虚拟头结点
        dummyNode->next = head;
        ListNode *cur = dummyNode;
        while (cur->next) {
            if (cur->next->val == val) {
                ListNode *tmp = cur->next;  // 释放删除结点的内存空间
                cur->next = cur->next->next;
                delete tmp;
            }
            else cur = cur->next;
        }
        return dummyNode->next;
    }
};

