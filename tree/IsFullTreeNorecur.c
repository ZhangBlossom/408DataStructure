#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 定义树节点的结构
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 使用队列进行非递归遍历的辅助结构
typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

TreeNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    TreeNode* node = temp->node;
    queue->front = temp->next;
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return node;
}

bool queueIsEmpty(Queue* queue) {
    return queue->front == NULL;
}

int queueSize(Queue* queue) {
    int size = 0;
    QueueNode* current = queue->front;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void freeQueue(Queue* queue) {
    while (queue->front != NULL) {
        QueueNode* temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
    free(queue);
}

// 判断是否是满二叉树
bool isFullBinaryTree(TreeNode* root) {
    if (root == NULL) {
        return true; // 空树也是满二叉树
    }

    Queue* queue = createQueue();
    int currentLevel = 0;

    enqueue(queue, root);

    while (!queueIsEmpty(queue)) {
        int size = queueSize(queue);
        currentLevel++;

        for (int i = 0; i < size; i++) {
            TreeNode* node = dequeue(queue);

            if (node->left == NULL && node->right != NULL) {
                return false;
            }

            if ((node->left != NULL || node->right != NULL) && currentLevel > 1) {
                return false;
            }

            if (node->left) {
                enqueue(queue, node->left);
            }

            if (node->right) {
                enqueue(queue, node->right);
            }
        }

        if (size != (int)pow(2, currentLevel - 1)) {
            return false;
        }
    }

    return true;
}

int main() {
    // 创建一个样本满二叉树
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->right->val = 3;
    root->left->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->left->val = 4;
    root->left->right->val = 5;
    root->right->left->val = 6;
    root->right->right->val = 7;

    if (isFullBinaryTree(root)) {
        printf("是满二叉树\n");
    } else {
        printf("不是满二叉树\n");
    }


    return 0;
}
