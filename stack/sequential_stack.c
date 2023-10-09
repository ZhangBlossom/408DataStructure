#include <stdio.h>
#include <stdlib.h>

// 定义栈结构
typedef struct Stack {
    int *array;  // 用于存储栈元素的数组
    int capacity; // 栈的容量
    int top;      // 栈顶索引
    int size;     // 当前栈中的元素个数
} Stack;

// 初始化栈
Stack* initStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    stack->capacity = capacity;
    stack->array = (int *)malloc(sizeof(int) * capacity);
    if (stack->array == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    stack->top = -1; // 初始化栈顶索引为-1，表示栈为空
    stack->size = 0; // 初始化栈中元素个数为0
    return stack;
}

// 入栈操作
void push(Stack *stack, int data) {
    if (stack->size >= stack->capacity) {
        printf("栈已满\n");
        return;
    }
    stack->array[++stack->top] = data;
    stack->size++;
}

// 出栈操作
int pop(Stack *stack) {
    if (stack->size <= 0) {
        printf("栈为空\n");
        return -1; // 返回一个特殊值表示栈为空
    }
    int data = stack->array[stack->top--];
    stack->size--;
    return data;
}

// 查看栈顶元素
int peek(Stack *stack) {
    if (stack->size <= 0) {
        printf("栈为空\n");
        return -1; // 返回一个特殊值表示栈为空
    }
    return stack->array[stack->top];
}

// 打印栈中的元素
void printStack(Stack *stack) {
    if (stack->size == 0) {
        printf("栈为空\n");
        return;
    }
    printf("栈中的元素: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main() {
    int capacity;
    printf("请输入栈的容量: ");
    scanf("%d", &capacity);

    Stack *stack = initStack(capacity);

    int choice, data;

    while (1) {
        printf("1. 入栈  2. 出栈  3. 查看栈顶元素  4. 打印栈  5. 退出\n");
        printf("请输入选项: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要入栈的数据: ");
                scanf("%d", &data);
                push(stack, data);
                break;
            case 2:
                data = pop(stack);
                if (data != -1)
                    printf("出栈的元素是: %d\n", data);
                break;
            case 3:
                data = peek(stack);
                if (data != -1)
                    printf("栈顶元素是: %d\n", data);
                break;
            case 4:
                printStack(stack);
                break;
            case 5:
                free(stack->array);
                free(stack);
                exit(0);
            default:
                printf("无效选项\n");
        }
    }

    return 0;
}
