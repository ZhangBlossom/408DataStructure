#include <stdio.h>
#include <stdlib.h>

// 结构体表示小顶堆
typedef struct PriorityQueue {
    int* heap;
    int capacity;
    int size;
} PriorityQueue;

// 创建小顶堆，初始化容量
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->heap = (int*)malloc(capacity * sizeof(int));
    return pq;
}

// 交换两个整数的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 向小顶堆中插入元素
void offer(PriorityQueue* pq, int element) {
    if (pq->size == pq->capacity) {
        // 队列已满，需要扩展
        pq->capacity *= 2;
        pq->heap = (int*)realloc(pq->heap, pq->capacity * sizeof(int));
    }

    int currentIndex = pq->size;
    pq->heap[currentIndex] = element;

    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (pq->heap[currentIndex] >= pq->heap[parentIndex]) {
            break;
        }
        swap(&pq->heap[currentIndex], &pq->heap[parentIndex]);
        currentIndex = parentIndex;
    }

    pq->size++;
}

// 从小顶堆中移除并返回最小值
int poll(PriorityQueue* pq) {
    if (pq->size == 0) {
        // 队列为空
        exit(1); // 或者返回一个错误值，具体情况而定
    }

    int min = pq->heap[0];
    int last = pq->heap[pq->size - 1];
    pq->size--;

    if (pq->size > 0) {
        pq->heap[0] = last;
        int currentIndex = 0;

        while (1) {
            int leftChildIndex = 2 * currentIndex + 1;
            int rightChildIndex = 2 * currentIndex + 2;
            int smallest = currentIndex;

            if (leftChildIndex < pq->size && pq->heap[leftChildIndex] < pq->heap[smallest]) {
                smallest = leftChildIndex;
            }

            if (rightChildIndex < pq->size && pq->heap[rightChildIndex] < pq->heap[smallest]) {
                smallest = rightChildIndex;
            }

            if (smallest == currentIndex) {
                break;
            }

            swap(&pq->heap[currentIndex], &pq->heap[smallest]);
            currentIndex = smallest;
        }
    }

    return min;
}

// 返回小顶堆中的最小值，不移除
int peek(PriorityQueue* pq) {
    if (pq->size == 0) {
        // 队列为空
        exit(1); // 或者返回一个错误值，具体情况而定
    }
    return pq->heap[0];
}

// 检查小顶堆是否为空
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// 返回小顶堆的大小
int size(PriorityQueue* pq) {
    return pq->size;
}

// 销毁小顶堆并释放内存
void destroyPriorityQueue(PriorityQueue* pq) {
    free(pq->heap);
    free(pq);
}

int main() {
    int capacity = 10;
    PriorityQueue* minHeap = createPriorityQueue(capacity);

    int userInput;
    printf("输入元素（输入-1结束）:\n");

    while (1) {
        scanf("%d", &userInput);
        if (userInput == -1) {
            break;
        }
        offer(minHeap, userInput);
    }

    printf("大小: %d\n", size(minHeap));
    printf("堆顶元素: %d\n", peek(minHeap));

    printf("出堆并打印元素:\n");
    while (!isEmpty(minHeap)) {
        printf("%d ", poll(minHeap));
    }
    printf("\n");

    destroyPriorityQueue(minHeap);
    return 0;
}
