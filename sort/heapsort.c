#include <stdio.h>

// 升序排序堆排序 --- 使用大顶堆
void adjustHeap(int arr[], int i, int length) {
    int temp = arr[i]; // 将当前非叶子结点保存
    for (int k = 2 * i + 1; k < length; k = k * 2 + 1) {
        if (k + 1 < length && arr[k] < arr[k + 1]) { // 判断左孩子大还是右孩子大
            k++; // 如果右孩子大就++获得右孩子的索引
        }
        if (arr[k] > temp) { // 判断孩子大还是当前节点大
            arr[i] = arr[k]; // 将更大的向上排
            i = k; // 大的元素就跑到了非叶子结点的索引去，然后让 i 去更小数据的索引
        } else {
            break;
        }
    }
    arr[i] = temp; // 大的数据被移上去了，但是其原有位置的数据还没有被修改
}

// 降序排序堆排序 --- 使用小顶堆
void adjustHeapDesc(int arr[], int i, int length) {
    int temp = arr[i]; // 将当前非叶子结点保存
    for (int k = 2 * i + 1; k < length; k = k * 2 + 1) {
        if (k + 1 < length && arr[k] > arr[k + 1]) { // 判断左孩子大还是右孩子大
            k++; // 如果右孩子小就++获得右孩子的索引
        }
        if (arr[k] < temp) { // 判断孩子小还是当前节点小
            arr[i] = arr[k]; // 将更小的向上排
            i = k; // 小的元素跑到了非叶子结点的索引，然后让 i 去更大数据的索引
        } else {
            break;
        }
    }
    arr[i] = temp; // 小的数据被移上去了，但是其原有位置的数据还没有被修改
}

void heapSort(int arr[], int length) {
    // 构建小顶堆
    for (int i = length / 2 - 1; i >= 0; i--) {
        adjustHeapDesc(arr, i, length);
    }
    
    printf("初始构造小顶堆: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 将堆顶元素与末尾元素进行交换，将最小数据沉到末尾
    // 重新调整结构，使其继续满足小顶堆性质
    for (int j = length - 1; j > 0; j--) {
        int temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;

        // 重新调整堆，排除已排序部分，使其继续满足小顶堆性质
        adjustHeapDesc(arr, 0, j);
    }
    
    printf("小顶堆排序后的数组（降序排列）: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int length = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    heapSort(arr, length);

    return 0;
}
