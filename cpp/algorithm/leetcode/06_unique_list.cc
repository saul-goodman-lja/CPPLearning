#include <iostream>
#include <memory>

using std::cin, std::cout, std::endl;
using std::unique_ptr, std::make_unique;

class MyLinkedList {
    struct ListNode{
        int val;
        unique_ptr<ListNode> next;

        ListNode(int value, ListNode *_next = nullptr) : val(value), next(_next) {}
    };

    unique_ptr<ListNode> head;
public:
    MyLinkedList() : head(nullptr) {    

    }
    
    int get(int index) {
        auto cur = head.get();
        for(int i = 0; i < index && cur != nullptr; i++){
            cur = cur->next.get();
        }
        return cur ? cur->val : -1;
    }
    
    void addAtHead(int val) {
        auto newHead = make_unique<ListNode>(val);
        newHead->next = std::move(head);
        head = std::move(newHead);
    }
    
    void addAtTail(int val) {
        auto newTail = make_unique<ListNode>(val);
        if(head == nullptr){
            head = std::move(newTail);
            return ;
        }
        ListNode *cur = head.get();
        while(cur->next){
            cur = cur->next.get();
        }
        cur->next = std::move(newTail);
    }
    
    // void addAtIndex(int index, int val) {
    //     // ListNode dummy(0, head.get());
    //     if(index == 0){
    //         addAtHead(val);
    //         return ;
    //     }
    //     if(!head){
    //         return;
    //     }
    //     int i = 1;
    //     auto cur = head.get();
    //     while(cur->next){
    //         if(i >= index){
    //             break;
    //         }
    //         cur = cur->next.get();
    //         i++;
    //     }
    //     if(i == index && cur){
    //         auto newNode = make_unique<ListNode>(val);
    //         newNode->next = std::move(cur->next);
    //         cur->next = std::move(newNode);
    //     }
    //     // dummy.next.reset();
    // }
    
    // void deleteAtIndex(int index) {
    //     // ListNode dummy(0, head.get());
    //     if(index == 0){
    //         auto tmp = make_unique<ListNode>(0);
    //         tmp->next = std::move(head->next);
    //         if(tmp->next){
    //             head->val = tmp->next->val;
    //             head->next = std::move(tmp->next->next);
    //         }
    //         else{
    //             head = nullptr;
    //         }
    //         return ;
    //         // head->next = std::move(head->next->next);
    //         // return;
    //     }
    //     int i = 1;
    //     auto cur = head.get();
    //     while(cur->next){
    //         if(i >= index){
    //             break;
    //         }
    //         cur = cur->next.get();
    //         i++;
    //     }
    //     if(i == index && cur->next){
    //         cur->next = std::move(cur->next->next);
    //     }
    // }
        void addAtIndex(int index, int val) {
        ListNode dummy(0, head.release());
        int i = 0;
        ListNode* cur = &dummy;
        while (cur && i < index) {
            cur = cur->next.get();
            i++;
        }

        if (i == index && cur) {
            std::unique_ptr<ListNode> newNode = std::make_unique<ListNode>(val);
            newNode->next = std::move(cur->next);
            cur->next = std::move(newNode);
        }

        head = std::move(dummy.next); // 更新真正的头结点
    }

    void deleteAtIndex(int index) {
        ListNode dummy(0, head.release());
        // if(index == 0){
        //     auto tmp = make_unique<ListNode>(0);
        //     tmp->next = std::move(head->next);
        //     if(tmp->next){
        //         head->val = tmp->next->val;
        //         head->next = std::move(tmp->next->next);
        //     }
        //     else{
        //         head = nullptr;
        //     }
        //     return ;
        // }
        int i = 0;
        auto cur = &dummy;
        while(cur->next){
            if(i >= index){
                break;
            }
            cur = cur->next.get();
            i++;
        }
        if(i == index && cur->next){
            cur->next = std::move(cur->next->next);
        }
        head = std::move(dummy.next);
    }
    void print(){
        auto cur = head.get();
        while(cur){
            cout << cur->val << " ";
            cur = cur->next.get();
        }
        cout << endl;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
void test(){
    MyLinkedList* obj = new MyLinkedList();
    obj->addAtHead(1);
    obj->addAtTail(3);
    obj->addAtIndex(1, 2);
    cout << obj->get(1) << endl;
    obj->print();
    obj->deleteAtIndex(0);
    cout << obj->get(0) << endl;
    obj->print();

    delete obj;
}

void test1(){
    // ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
    // [[],[1],[3],[1,2],[1],[0],[0]]
    MyLinkedList* obj = new MyLinkedList();
    obj->addAtHead(1);
    obj->addAtTail(3);
    obj->addAtIndex(1, 2);
    cout << obj->get(1) << endl;
    obj->print();
    obj->deleteAtIndex(0);
    cout << obj->get(0) << endl;
    obj->print();

    delete obj;
}

int main(){
    test1();
    return 0;
}