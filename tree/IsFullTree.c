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
int getHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

// 判断是否是满二叉树
bool isFullBinaryTree(TreeNode* root) {
    if (root == NULL) {
        return true; // 空树也是满二叉树
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    if (leftHeight == rightHeight) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    } else {
        return false;
    }
}

int main() {
    // 创建一颗满二叉树
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->right->val = 3;

    if (isFullBinaryTree(root)) {
        printf("是满二叉树\n");
    } else {
        printf("不是满二叉树\n");
    }

    // 释放内存
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
