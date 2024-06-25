#include <iostream>
#include <vector>

using std::cout, std::endl;
struct Node{
    int val;
    Node *next;
    Node(int element, Node *data) : val(element), next(data) {}
};

class Stack{

public:
    Stack() : _top(new Node(0, nullptr)), _size(0), _capacity(10) {}

    bool empty(){	//判断栈是否为空
        return _size == 0;
    }
	bool full(){	//判断栈是否已满
        return _size == _capacity;
    }
	void push(int element){ //元素入栈

        if(_size == _capacity){
            cout << "push failed, stack is full!" << endl;
            return ;
        }
        Node *node = new Node(element, _top);
        _top = node;
        _size++;
        cout << "push success!" << endl;
    }
	void pop(){ //元素出栈
    
        if(_size <= 0){
            cout << "pop failed, stack is empty!" << endl;
            return ;
        }
        Node *temp = _top;
        _top = _top->next;
        delete temp;
        _size--;
        cout << "pop success!" << endl;
    }
	int top(){	//获取栈顶元素
        return _top->val;
    }   

private:
    Node *_top;
    int _size;
    int _capacity;
};

int main(void) {

    Stack s;
    cout << "is empty: " << s.empty() << endl;
    for(int i = 0; i < 12; i++){
        s.push(i);
    }
    cout << "is full:" << s.full() << endl;
    for(int i = 0; i < 11; i++){
        cout << s.top() << endl;
        s.pop();
    }
    cout << "is empty: " << s.empty() << endl;

    return 0;
}