#include <stdio.h>
#include <stdlib.h>

// 定义树节点
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* buildTree(int* inorder, int iStart, int iEnd, int* postorder, int pStart, int pEnd) {
    if (iStart > iEnd || pStart > pEnd) {
        return NULL;
    }

    // 在后序遍历序列中，最后一个元素是树的根节点
    int rootVal = postorder[pEnd];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;
    root->left = NULL;
    root->right = NULL;

    int rootIndex = -1;
    // 在中序遍历序列中，根节点的左边是左子树，右边是右子树
    for (int i = iStart; i <= iEnd; i++) {
        if (rootVal == inorder[i]) {
            rootIndex = i;
            break;
        }
    }

    int leftTreeNum = rootIndex - iStart;
    root->left = buildTree(inorder, iStart, rootIndex - 1, postorder, pStart, pStart + leftTreeNum - 1);
    root->right = buildTree(inorder, rootIndex + 1, iEnd, postorder, pStart + leftTreeNum, pEnd - 1);

    return root;
}

struct TreeNode* createTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    return buildTree(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}

// 
void printTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};
    int inorderSize = sizeof(inorder) / sizeof(inorder[0]);
    int postorderSize = sizeof(postorder) / sizeof(postorder[0]);

    struct TreeNode* root = createTree(inorder, inorderSize, postorder, postorderSize);

    printf("前序遍历: ");
    printTree(root);
    printf("\n");

    return 0;
}
