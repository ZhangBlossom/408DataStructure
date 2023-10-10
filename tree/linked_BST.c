#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxSize 100
// 定义二叉树结点结构
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 函数声明
TreeNode *createNode(int data);
TreeNode *insert(TreeNode *root, int data);
TreeNode *search(TreeNode *root, int data);
TreeNode *findMin(TreeNode *root);
TreeNode *deleteNode(TreeNode *root, int data);
void preorderTraversal(TreeNode *root);
void inorderTraversal(TreeNode *root);
void postorderTraversal(TreeNode *root);
int maxDepthOfTree(TreeNode *root);
void levelOrderTraversal(TreeNode *root);

TreeNode *root = NULL;

int main()
{
    int choice, data;

    printf("基于链式存储结构的二叉树操作：\n");

    while (1)
    {
        printf("\n请选择操作：\n");
        printf("1. 插入\n");
        printf("2. 删除\n");
        printf("3. 查找\n");
        printf("4. 层序遍历\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("输入要插入的数据: ");
            scanf("%d", &data);
            root = insert(root, data);
            printf("前序遍历结果为：");
            preorderTraversal(root);
            printf("中序遍历结果为：");
            inorderTraversal(root);
            printf("后序遍历结果为：");
            postorderTraversal(root);
            printf("二叉树最大深度为：%d\n", maxDepthOfTree(root));
            break;

        case 2:
            printf("输入要删除的数据: ");
            scanf("%d", &data);
            root = deleteNode(root, data);
            printf("前序遍历结果为：");
            preorderTraversal(root);
            printf("中序遍历结果为：");
            inorderTraversal(root);
            printf("后序遍历结果为：");
            postorderTraversal(root);
            printf("二叉树最大深度为：%d\n", maxDepthOfTree(root));
            break;

        case 3:
            printf("输入要查找的数据: ");
            scanf("%d", &data);
            TreeNode *result = search(root, data);
            if (result != NULL)
            {
                printf("找到了 %d\n", result->data);
            }
            else
            {
                printf("未找到 %d\n", data);
            }
            printf("前序遍历结果为：");
            preorderTraversal(root);
            printf("中序遍历结果为：");
            inorderTraversal(root);
            printf("后序遍历结果为：");
            postorderTraversal(root);
            printf("二叉树最大深度为：%d\n", maxDepthOfTree(root));
            break;

        case 4:
            printf("层序遍历结果为：");
            levelOrderTraversal(root);
            printf("\n");
            break;
        }
    }

    return 0;
}

// 创建新的二叉树结点
TreeNode *createNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入结点
TreeNode *insert(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    return root;
}

// 查找结点
TreeNode *search(TreeNode *root, int data)
{
    if (root == NULL || root->data == data)
    {
        return root;
    }

    if (data < root->data)
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}

// 找到最小值结点
TreeNode *findMin(TreeNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// 删除结点
TreeNode *deleteNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return root;
    }

    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        // 结点有一个子结点或没有子结点
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // 结点有两个子结点，找到中序遍历的后继结点（右子树中的最小值）
        TreeNode *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// 前序遍历
void preorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 中序遍历
void inorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 后序遍历
void postorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// 计算二叉树的最大深度
int maxDepthOfTree(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = maxDepthOfTree(root->left);
        int rightHeight = maxDepthOfTree(root->right);
        return fmax(leftHeight, rightHeight) + 1;
    }
}

// 层序遍历
void levelOrderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // 创建一个队列用于层序遍历
    TreeNode *queue[MaxSize];
    int front = 0, rear = 0;

    queue[rear++] = root; // 根结点入队

    while (front < rear)
    {
        TreeNode *current = queue[front++];
        printf("%d ", current->data);

        // 左子结点入队
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }

        // 右子结点入队
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}
