#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义树节点的结构
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 计算树的高度
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

// 判断是否是平衡二叉树
bool isBalanced(TreeNode* root) {
    if (root == NULL) {
        return true;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
}

// 定义返回值的结构
typedef struct ReturnType {
    bool isBalanced;
    int height;
} ReturnType;

// 计算树的高度和平衡性
ReturnType process(TreeNode* head) {
    if (head == NULL) {
        return (ReturnType){true, 0};
    }
    
    ReturnType leftData = process(head->left);
    ReturnType rightData = process(head->right);
    
    int height = (leftData.height > rightData.height) ? leftData.height + 1 : rightData.height + 1;
    bool isBalanced = leftData.isBalanced && rightData.isBalanced && abs(leftData.height - rightData.height) < 2;
    
    return (ReturnType){isBalanced, height};
}

// 判断是否是平衡二叉树
bool isBalancedX(TreeNode* root) {
    if (root == NULL) {
        return true;
    } else {
        ReturnType result = process(root);
        return result.isBalanced;
    }
}