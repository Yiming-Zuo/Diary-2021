class MyLinkedList {
public:
    struct Listnode {
        int val;
        Listnode *next;
        Listnode(int val) : val(val), next(NULL) {}
    };
    /** Initialize your data structure here. */
    MyLinkedList() {
        _dummyHead = new Listnode(0);  // 虚拟头结点
        _size = 0;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index >= _size || index < 0) return -1;
        Listnode *cur = _dummyHead->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Listnode *newNode = new Listnode(val);
        newNode->next = _dummyHead->next;  // error
        _dummyHead->next = newNode;
        _size++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Listnode *cur = _dummyHead;
        Listnode *newNode = new Listnode(val);
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index > _size) return;
        // if (index = _size) addAtTail(val) ;  // error
        if (index < 0) index = 0;
        Listnode *cur = _dummyHead;
        Listnode *newNode = new Listnode(val);
        while (index--) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index >= _size || _size == 0) return;
        Listnode *cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        Listnode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        _size--;
    }
private:
    Listnode *_dummyHead;
    int _size;
};

