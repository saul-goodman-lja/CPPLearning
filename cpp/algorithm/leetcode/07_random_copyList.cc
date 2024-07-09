#include <iostream>
#include <unordered_map>
using std::unordered_map;
using std::cin, std::cout, std::endl;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node *cur = head;
        unordered_map<Node*, Node*> dic;
        while(cur){
            dic[cur] = new Node(cur->val);
            cur = cur->next;
        }
        for(auto &elem : dic){
            elem.second->next = elem.first->next ? dic[elem.first->next] : nullptr;
            elem.second->random = elem.first->random ? dic[elem.first->random] : nullptr;
        }
        return dic[head];
    }
};

void test(){
    Node *head = new Node(7);
    head->next = new Node(13);
    head->next->next = new Node(11);
    head->next->next->next = new Node(10);
    head->next->next->next->next = new Node(1);
    head->random = nullptr;
    head->next->random = head;
    head->next->next->random = head->next->next->next->next;
    head->next->next->next->random = head->next->next;
    head->next->next->next->next->random = head;
    Solution s;
    cout << s.copyRandomList(head)->val << endl;
    cout << s.copyRandomList(head)->next->val << endl;
    cout << s.copyRandomList(head)->next->next->val << endl;
    cout << s.copyRandomList(head)->next->next->next->val << endl;
    cout << s.copyRandomList(head)->next->next->next->next->val << endl;
    cout << s.copyRandomList(head)->random->val << endl;
    cout << s.copyRandomList(head)->next->random->val << endl;
    cout << s.copyRandomList(head)->next->next->random->val << endl;
    cout << s.copyRandomList(head)->next->next->next->random->val << endl;
    cout << s.copyRandomList(head)->next->next->next->next->random->val << endl;
    return;
}

int main(){
    test();
    return 0;
}