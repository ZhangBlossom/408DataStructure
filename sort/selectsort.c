#include <stdio.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = arr[i];  // 初始化最小值为当前元素
        int p = i;  // 用于记录最小值的索引

        // 在未排序部分查找最小值
        for (int j = i + 1; j < n; j++) {
            if (min > arr[j]) {
                min = arr[j];
                p = j;
            }
        }

        // 如果找到更小的值，交换它们
        if (p != i) {
            int temp = arr[p];
            arr[p] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    selectionSort(arr, n);

    printf("排序后的数组:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
