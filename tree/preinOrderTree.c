#include <stdio.h>
#include <stdlib.h>

// 定义一个树
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* buildTree(int* preorder, int pStart, int pEnd, int* inorder, int iStart, int iEnd) {
    if (pStart == pEnd) {
        return NULL;
    }

    // 前序遍历的第一个节点就是根节点
    int rootVal = preorder[pStart];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;
    root->left = NULL;
    root->right = NULL;

    int root_in_index = 0;
    // 中序遍历中第一次等于根节点的值就是左子树
    for (int i = iStart; i < iEnd; i++) {
        // 得到中序遍历中根节点的位置
        if (inorder[i] == rootVal) {
            root_in_index = i;
            break;
        }
    }

    // 得到左子树的长度
    int leftTreeLength = root_in_index - iStart;

    // 构建左右子树（前闭后开区间）
    root->left = buildTree(preorder, pStart + 1, pStart + 1 + leftTreeLength, inorder, iStart, root_in_index);
    root->right = buildTree(preorder, pStart + 1 + leftTreeLength, pEnd, inorder, root_in_index + 1, iEnd);

    return root;
}

struct TreeNode* createTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    return buildTree(preorder, 0, preorderSize, inorder, 0, inorderSize);
}

// Helper function to print the tree (for testing)
void printTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};
    int preorderSize = sizeof(preorder) / sizeof(preorder[0]);
    int inorderSize = sizeof(inorder) / sizeof(inorder[0]);

    struct TreeNode* root = createTree(preorder, preorderSize, inorder, inorderSize);

    printf("Preorder traversal of the constructed tree: ");
    printTree(root);
    printf("\n");

    return 0;
}
