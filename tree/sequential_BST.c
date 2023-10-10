#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxSize 100

typedef int TreeNodeType;

// 二叉树结构
typedef struct
{
    TreeNodeType data[MaxSize];
    int BiTreeNum;
} BinaryTree;

// 声明队列数据结构
typedef struct
{
    int front, rear;
    int size;
    int capacity;
    int *array;
} Queue;

void initTree(BinaryTree *T);
void createTree(BinaryTree *T, int n);
TreeNodeType rootTree(BinaryTree *T);
int countTree(BinaryTree *T);
int maxDepthOfTree(BinaryTree *T, int n);
void preOrderTraverse(BinaryTree *T, int n);
void inOrderTraverse(BinaryTree *T, int n);
void postOrderTraverse(BinaryTree *T, int n);
void levelOrderTraverse(BinaryTree *T); // 层序遍历
bool destoryTree(BinaryTree *T);
void traverseArray(BinaryTree *T); // 遍历数组
bool isBSTUtil(BinaryTree *T, int n, TreeNodeType minVal, TreeNodeType maxVal);

// 队列相关函数
Queue *createQueue(int capacity);
bool isQueueEmpty(Queue *queue);
bool isQueueFull(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);

int main()
{
    BinaryTree T;
    // 开始构造二叉树 其中使用1作为根节点下标
    // 而不是使用0，使用0的问题在于不好表示数据在数组中的位置
    // 我们知道二叉树满足 当前节点n的左子树和右子树的序列号应该为 2n和2n+1
    initTree(&T);
    printf("请输入根结点(输入#表示该结点为空):");
    createTree(&T, 1);

    traverseArray(&T);

    printf("当前二叉树的最大深度为：%d\n", maxDepthOfTree(&T, 1));

    printf("先序遍历：");
    preOrderTraverse(&T, 1);
    printf("\n");

    printf("中序遍历：");
    inOrderTraverse(&T, 1);
    printf("\n");

    printf("后序遍历：");
    postOrderTraverse(&T, 1);
    printf("\n");

    printf("层序遍历：");
    levelOrderTraverse(&T);
    printf("\n");

    if (isBSTUtil(&T, 1, -10000, 10000))
    {
        printf("this is a BST");
    }
    else
    {
        printf("this is not a BST");
    }

    return 0;
}

void initTree(BinaryTree *T)
{
    int i;
    for (i = 0; i < MaxSize; ++i)
    {
        T->data[i] = '\0';
    }

    T->BiTreeNum = 0;
    return;
}

void createTree(BinaryTree *T, int n)
{
    char ch;
    // 刷新（清空）标准输入流（stdin）
    // 主打一个求稳
    fflush(stdin);
    // 输入当前节点信息 # 代表当前节点为空
    // 先构造过字数
    scanf(" %c", &ch);
    if (ch == '#')
    { // 空直接返回
        return;
    }
    else
    {
        T->data[n] = ch;
        T->BiTreeNum++;
        printf("输入 %c 的左子树数据（输入#表示当前左子树为空: ", ch);
        // 这里有一个技巧
        createTree(T, 2 * n);
        printf("输入 %c 的右子树数据（输入#表示当前右边子树为空）: ", ch);
        createTree(T, (2 * n + 1));
    }
}

// 计算二叉树的最大深度
// 从根节点到叶子节点的最长路径的长度
// 由于是顺序结构 因此这里从第一层也就是n=1开始向下遍历
// 然后不断的判断左子树和右子树的高度
// 最后取最大值
int maxDepthOfTree(BinaryTree *T, int n)
{
    if (n <= T->BiTreeNum && T->data[n] != '\0')
    {
        int leftDepth = maxDepthOfTree(T, 2 * n);
        int rightDepth = maxDepthOfTree(T, 2 * n + 1);

        return 1 + fmax(leftDepth, rightDepth);
    }
    else
    {
        return 0;
    }
}

// 先序遍历 根左右
void preOrderTraverse(BinaryTree *T, int n)
{
    if (T->data[n] == '\0')
        return;
    else
    {
        printf("%c ", T->data[n]);
        preOrderTraverse(T, 2 * n);
        preOrderTraverse(T, (2 * n + 1));
    }
}
// 中序遍历 左根由7
void inOrderTraverse(BinaryTree *T, int n)
{
    if (T->data[n] == '\0')
        return;
    else
    {
        inOrderTraverse(T, 2 * n);
        printf("%c ", T->data[n]);
        inOrderTraverse(T, (2 * n + 1));
    }
}
// 后序遍历  左右根
void postOrderTraverse(BinaryTree *T, int n)
{
    if (T->data[n] == '\0')
        return;
    else
    {
        postOrderTraverse(T, 2 * n);
        postOrderTraverse(T, (2 * n + 1));
        printf("%c ", T->data[n]);
    }
}
void traverseArray(BinaryTree *T)
{
    for (int i = 1; i <= T->BiTreeNum; i++)
    {
        printf("%c  ", T->data[i]);
    }
    printf("\n");
}

// 层序遍历二叉树
void levelOrderTraverse(BinaryTree *T)
{
    if (T->BiTreeNum == 0)
    {
        printf("二叉树为空\n");
        return;
    }

    Queue *queue = createQueue(T->BiTreeNum);
    int current = 1; // 从根节点开始

    while (current <= T->BiTreeNum)
    {
        printf("%c ", T->data[current]);

        if (2 * current <= T->BiTreeNum && T->data[2 * current] != '\0')
        {
            enqueue(queue, 2 * current);
        }

        if (2 * current + 1 <= T->BiTreeNum && T->data[2 * current + 1] != '\0')
        {
            enqueue(queue, 2 * current + 1);
        }

        if (!isQueueEmpty(queue))
        {
            current = dequeue(queue);
        }
        else
        {
            break;
        }
    }

    free(queue->array);
    free(queue);
}

// 创建队列
Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }

    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (int *)malloc(capacity * sizeof(int));
    if (!queue->array)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }

    return queue;
}

// 检查队列是否为空
bool isQueueEmpty(Queue *queue)
{
    return (queue->size == 0);
}

// 检查队列是否已满
bool isQueueFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

// 入队列
void enqueue(Queue *queue, int item)
{
    if (isQueueFull(queue))
    {
        printf("队列已满\n");
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

// 出队列
int dequeue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("队列为空\n");
        return -1;
    }

    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return item;
}

// 递归函数，判断以n为根的二叉树是否是BST
bool isBSTUtil(BinaryTree *T, int n, TreeNodeType minVal, TreeNodeType maxVal)
{
    if (T->data[n] == '\0')
        return true;

    TreeNodeType nodeValue = T->data[n];

    // 检查当前节点的值是否在[minVal, maxVal]的范围内
    if ((nodeValue <= minVal) || ( maxVal <= nodeValue))
        return false;

    // 递归检查左子树和右子树，更新范围
    return isBSTUtil(T, 2 * n, minVal, nodeValue) && isBSTUtil(T, 2 * n + 1, nodeValue, maxVal);
}

// 当前方法用于判断输入的树是否是二叉搜索树
bool isBST(BinaryTree *T, int n, TreeNodeType *prev)
{
    if (n <= T->BiTreeNum && T->data[n] != '\0')
    {
        // 递归判断左子树
        if (!isBST(T, 2 * n, prev))
            return false;

        // 判断当前节点的值是否大于前一节点
        if (T->data[n] <= *prev)
            return false;

        // 更新前一节点的值
        *prev = T->data[n];

        // 递归判断右子树
        return isBST(T, 2 * n + 1, prev);
    }
    return true;
}