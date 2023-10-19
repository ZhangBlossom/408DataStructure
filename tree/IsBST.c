#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// 定义树节点的结构
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 递归方式判断是否是二叉搜索树
bool isBST(TreeNode* head, int low, int high) {
    if (head == NULL) {
        return true;
    }
    if (head->val > high || head->val < low) {
        return false;
    }
    return isBST(head->left, low, head->val) && isBST(head->right, head->val, high);
}

// 基于中序遍历判断是否是二叉搜索树
int preVal = INT_MIN;

bool isBstX(TreeNode* head) {
    if (head == NULL) {
        return true;
    }
    bool leftBST = isBstX(head->left);
    if (!leftBST) {
        return false;
    }
    if (preVal >= head->val) {
        return false;
    } else {
        preVal = head->val;
    }
    return isBstX(head->right);
}


// 非递归方式判断是否是二叉搜索树
bool isBstNoRecur(TreeNode* head) {
    if (head == NULL) {
        return true;
    }
    int pre = INT_MIN;
    // 创建栈
    struct TreeNode* stack[100]; // 假设栈的最大大小为100，根据实际情况调整
    int top = -1; // 栈顶指针

    while (top != -1 || head != NULL) {
        if (head != NULL) {
            // 入栈
            stack[++top] = head;
            head = head->left;
        } else {
            // 出栈
            head = stack[top--];
            if (pre >= head->val) {
                return false;
            } else {
                pre = head->val;
            }
            head = head->right;
        }
    }
    return true;
}

int main() {
    TreeNode* head = (TreeNode*)malloc(sizeof(TreeNode));
    head->val = 5;
    head->left = (TreeNode*)malloc(sizeof(TreeNode));
    head->right = (TreeNode*)malloc(sizeof(TreeNode));
    head->left->val = 4;
    head->right->val = 6;
    head->left->left = (TreeNode*)malloc(sizeof(TreeNode));
    head->left->left->val = 3;
    head->right->right = (TreeNode*)malloc(sizeof(TreeNode));
    head->right->right->val = 123;

    printf("使用中序遍历判断是否是二叉搜索树：\n");
    if (isBstX(head)) {
        printf("是二叉搜索树\n");
    } else {
        printf("不是二叉搜索树\n");
    }

    printf("使用递归方式判断是否是二叉搜索树：\n");
    if (isBST(head, INT_MIN, INT_MAX)) {
        printf("是二叉搜索树\n");
    } else {
        printf("不是二叉搜索树\n");
    }

    printf("使用非递归方式判断是否是二叉搜索树：\n");
    if (isBstNoRecur(head)) {
        printf("是二叉搜索树\n");
    } else {
        printf("不是二叉搜索树\n");
    }

    // 释放内存
    free(head->left->left);
    free(head->left);
    free(head->right->right);
    free(head->right);
    free(head);

    return 0;
}
