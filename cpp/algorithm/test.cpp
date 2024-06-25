#include <iostream>
#include <sstream>
#include <string>

using std::cin, std::cout, std::string, std::istringstream;

template <typename T>
class TreeNode{
public:
    T data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree{
private:
    TreeNode<T> *root;

    void destroyTree(TreeNode<T> *node){
        if(node){
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree(){
        destroyTree(root);
    }

    void insert(T val){
        TreeNode<T> *node = new TreeNode<T>(val);
        if(!root){
            root = node;
            return;
        }

        TreeNode<T> *cur = root;
        TreeNode<T> *parent = nullptr;

        while(cur){
            parent = cur;
            if(val < cur->data){
                cur = cur->left;
            }else{
                cur = cur->right;
            }   
        }
        if(val < cur->data){
            parent->left = node;
        }else{
            parent->right = node;
        }

    }

};

int main(void){

    return 0;
}