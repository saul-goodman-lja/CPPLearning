#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <vector>

using std::cin, std::cout, std::string, std::istringstream;
using std::unordered_map;
using std::vector, std::queue;

struct TreeNode{
    char _val;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode(char val) : _val(val), _left(nullptr), _right(nullptr) {}
};

TreeNode *buildTreeRecursive(string& preorder, string& inorder, int preStart, int inStart, int inEnd, 
    unordered_map<int, int>& indexMap){
        
}

int main(void){



    return 0;
}