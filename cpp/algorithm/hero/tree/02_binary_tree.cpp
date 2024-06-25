// #include <iostream>

// using namespace std;

// template <typename T>
// struct TreeNode{
//     T val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
// };

// template<typename T>
// class Tree{

// public:
//     Tree();
//     Tree(int maxNodes);
//     ~Tree();
//     TreeNode<T> *GetTreeNode(int id);
//     void CreateTree(T a[], int size, T nullNode);
//     void preOrderTraversal();
//     void inOrderTraversal();
//     void postOrderTraversal();

// private:
//     TreeNode<T> *nodes;
//     TreeNode<T> *root;
//     size_t nodeSize;

//     TreeNode<T> *Create(T a[], int size, int nodeId, T nullNode);
//     void visit(TreeNode<T> *node);
//     void preOrder(TreeNode<T> *node);
//     void inOrder(TreeNode<T> *node);
//     void postOrder(TreeNode<T> *node);
//     void levelOrder(TreeNode<T> *node);
// };

// template <typename T>
// Tree<T>::Tree(){
//     nodeSize = 100001;
//     nodes = new TreeNode<T> [nodeSize];
// }

// template <typename T>
// Tree<T>::Tree(int maxNodes){
//     nodeSize = maxNodes;
//     nodes = new TreeNode<T>[nodeSize];
// }

// template <typename T>
// Tree<T>::~Tree(){
//     delete [] nodes;
// }

// template <typename T>
// TreeNode<T>* Tree<T>::GetTreeNode(int id){
//     return &nodes[id];
// }

// template <typename T>
// void Tree<T>::visit(TreeNode<T> *node){
//     cout << node->val;
// }

// template <typename T>
// void Tree<T>::inOrder(TreeNode<T>* node){
//     if(node){
//         inOrder(node->left);
//         visit(node);
//         inOrder(node->right);
//     }
// }

// template <typename T>
// void Tree<T>::preOrder(TreeNode<T> *node){
//     if(node){
//         visit(node);
//         preOrder(node->left);
//         preOrder(node->right);
//     }
// }

// template <typename T>
// void Tree<T>::postOrder(TreeNode<T> *node){
//     if(node){
//         postOrder(node->left);
//         postOrder(node->right);
//         visit(node);
//     }
// }

// template <typename T>
// void Tree<T>::CreateTree(T a[], int size, T nullNode){
//     root = Create(a, size, 1, nullNode);
// }

// template <typename T>
// TreeNode<T>* Tree<T>::Create(T a[], int size, int nodeId, T nullNode){
//     if(nodeId >= size || a[nodeId] == nullNode){
//         return nullptr;
//     }
//     TreeNode<T> *newNode = GetTreeNode(nodeId);
//     newNode->val = a[nodeId];
//     newNode->left = Create(a, size, nodeId * 2, nullNode);
//     newNode->right = Create(a, size, nodeId * 2 + 1, nullNode);
//     return newNode;
// }   

// template <typename T>
// void Tree<T>::preOrderTraversal(){
//     preOrder(root);
// }

// template <typename T>
// void Tree<T>::inOrderTraversal(){
//     inOrder(root);
// }

// template <typename T>
// void Tree<T>::postOrderTraversal(){
//     postOrder(root);
// }

// int main(void){

//     const char nullNode = '-';
//     char a[15] = {
//         nullNode, 'a', 'b', 'c', 'd',
//         nullNode, 'e', 'f', 'g', 'h',
//         nullNode, nullNode, nullNode, nullNode, 'i'
//     };

//     Tree<char> T(15);
//     T.CreateTree(a, 15, nullNode);
//     T.preOrderTraversal();
//     cout << endl;
//     T.inOrderTraversal();
//     cout << endl;
//     T.postOrderTraversal();
//     cout << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode {
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
class Tree {

public:
    Tree();
    Tree(int maxNodes);
    ~Tree();
    TreeNode<T>* GetTreeNode(int id);
    void CreateTree(T a[], int size, T nullNode);
    void preOrderTraversal();
    void inOrderTraversal();
    void postOrderTraversal();
    void levelOrderTraversal(); // 新增的层次遍历函数

private:
    TreeNode<T> *nodes;
    TreeNode<T> *root;
    size_t nodeSize;

    TreeNode<T>* Create(T a[], int size, int nodeId, T nullNode);
    void visit(TreeNode<T> *node);
    void preOrder(TreeNode<T> *node);
    void inOrder(TreeNode<T> *node);
    void postOrder(TreeNode<T> *node);
    void levelOrder(TreeNode<T> *node);
};

template <typename T>
Tree<T>::Tree() {
    nodeSize = 100001;
    nodes = new TreeNode<T>[nodeSize];
}

template <typename T>
Tree<T>::Tree(int maxNodes) {
    nodeSize = maxNodes;
    nodes = new TreeNode<T>[nodeSize];
}

template <typename T>
Tree<T>::~Tree() {
    delete[] nodes;
}

template <typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int id) {
    return &nodes[id];
}

template <typename T>
void Tree<T>::visit(TreeNode<T> *node) {
    cout << node->val;
}

template <typename T>
void Tree<T>::inOrder(TreeNode<T> *node) {
    if (node) {
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

template <typename T>
void Tree<T>::preOrder(TreeNode<T> *node) {
    if (node) {
        visit(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

template <typename T>
void Tree<T>::postOrder(TreeNode<T> *node) {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}

template <typename T>
void Tree<T>::CreateTree(T a[], int size, T nullNode) {
    root = Create(a, size, 1, nullNode);
}

template <typename T>
TreeNode<T>* Tree<T>::Create(T a[], int size, int nodeId, T nullNode) {
    if (nodeId >= size || a[nodeId] == nullNode) {
        return nullptr;
    }
    TreeNode<T> *newNode = GetTreeNode(nodeId);
    newNode->val = a[nodeId];
    newNode->left = Create(a, size, nodeId * 2, nullNode);
    newNode->right = Create(a, size, nodeId * 2 + 1, nullNode);
    return newNode;
}

template <typename T>
void Tree<T>::preOrderTraversal() {
    preOrder(root);
}

template <typename T>
void Tree<T>::inOrderTraversal() {
    inOrder(root);
}

template <typename T>
void Tree<T>::postOrderTraversal() {
    postOrder(root);
}

template <typename T>
void Tree<T>::levelOrderTraversal() {
    levelOrder(root);
}

template <typename T>
void Tree<T>::levelOrder(TreeNode<T> *node) {
    if (!node) return;
    queue<TreeNode<T>*> q;
    q.push(node);
    while (!q.empty()) {
        TreeNode<T> *current = q.front();
        q.pop();
        visit(current);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

int main(void) {
    const char nullNode = '-';
    char a[15] = {
        nullNode, 'a', 'b', 'c', 'd',
        nullNode, 'e', 'f', 'g', 'h',
        nullNode, nullNode, nullNode, nullNode, 'i'
    };

    Tree<char> T(15);
    T.CreateTree(a, 15, nullNode);
    T.preOrderTraversal();
    cout << endl;
    T.inOrderTraversal();
    cout << endl;
    T.postOrderTraversal();
    cout << endl;
    T.levelOrderTraversal();  // 调用层次遍历
    cout << endl;

    return 0;
}
