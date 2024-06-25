#include <iostream>

using namespace std;

template <typename T>
struct TreeNode{
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree{
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();

    void insert(T value){
        root = insertNode(root, value);
    }

    void remove(T value){
        root = removeNode(root, value);
    }

    bool search(T value){
        return searchNode(root, value);
    }

    void inOrderTraversal(){
        inOrder(root);
        cout << endl;
    }


private:
    TreeNode<T> *root;

    TreeNode<T>* insertNode(TreeNode<T> *node, T value);
    TreeNode<T>* removeNode(TreeNode<T> *node, T value);
    bool searchNode(TreeNode<T> *node, T value);
    void inOrder(TreeNode<T> *node);
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    while(root){
        remove(root->val);
    }
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insertNode(TreeNode<T> *node, T value){
    if(node == nullptr){
        return new TreeNode<T>(value);
    }
    if(value < node->val){
        node->left = insertNode(node->left, value);
    }else if(value > node->val){
        node->right = insertNode(node->right, value);
    }
    return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T> *node, T value){
    if(node == nullptr){
        return nullptr;
    }
    if(value < node->val){
        node->left = removeNode(node->left, value);
    }else if(value > node->val){
        node->right = removeNode(node->right, value);
    }else{
        if(node->left == nullptr && node->right == nullptr){
            delete node;
            return nullptr;
        }else if(node->left == nullptr){
            TreeNode<T> *rightChild = node->right;
            delete node;
            return rightChild;
        }else if(node->right == nullptr){
            TreeNode<T> *leftChild = node->left;
            delete node;
            return leftChild;
        }else{
            TreeNode<T> *replancement = node->right;
            while(replancement->left){
                replancement = replancement->left;
            }
            node->val = replancement->val;
            node->right = removeNode(node->right, replancement->val);
        }
    }
    return node;
}

template <typename T>
bool BinarySearchTree<T>::searchNode(TreeNode<T> *node, T value){
    if(node == nullptr){
        return false;
    }
    if(value < node->val){
        return searchNode(node->left, value);
    }else if(value > node->val){
        return searchNode(node->right, value);
    }
    return true;
}

template <typename T>
void BinarySearchTree<T>::inOrder(TreeNode<T> *node){
    if(node){
        inOrder(node->left);
        cout << node->val << ',';
        inOrder(node->right);
    }
}

int main(void){

    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(40);
    bst.insert(80);
    bst.insert(80);
    bst.insert(80);
    bst.insert(60);
    bst.insert(100);
    bst.inOrderTraversal();
    

    cout << bst.search(9090) << endl;
    cout << bst.search(100) << endl;

    bst.remove(70);
    bst.inOrderTraversal();
    bst.insert(65);
    bst.inOrderTraversal();

    return 0;   
}