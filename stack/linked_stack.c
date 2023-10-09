#include <stdio.h>
#include <stdlib.h>

// 定义节点结构
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 定义栈结构
typedef struct Stack {
    Node *top;
    int size;
} Stack;

// 初始化栈
void initStack(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

// 入栈操作
void push(Stack *stack, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// 出栈操作
int pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("栈为空\n");
        return -1; // 返回一个特殊值表示栈为空
    }
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

// 查看栈顶元素
int peek(Stack *stack) {
    if (stack->top == NULL) {
        printf("栈为空\n");
        return -1; // 返回一个特殊值表示栈为空
    }
    return stack->top->data;
}

// 打印栈中的元素
void printStack(Stack *stack) {
    Node *current = stack->top;
    printf("栈中的元素: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Stack stack;
    initStack(&stack);

    int choice, data;

    while (1) {
        printf("1. 入栈  2. 出栈  3. 查看栈顶元素  4. 打印栈  5. 退出\n");
        printf("请输入选项: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要入栈的数据: ");
                scanf("%d", &data);
                push(&stack, data);
                break;
            case 2:
                data = pop(&stack);
                if (data != -1)
                    printf("出栈的元素是: %d\n", data);
                break;
            case 3:
                data = peek(&stack);
                if (data != -1)
                    printf("栈顶元素是: %d\n", data);
                break;
            case 4:
                printStack(&stack);
                break;
            case 5:
                exit(0);
            default:
                printf("无效选项\n");
        }
    }

    return 0;
}
