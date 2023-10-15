#include <stdio.h>

void insertSort(int arr[], int n) {
	//从第一个元素开始遍历，然后内循环比较当前元素的前面一个元素和当前元素的关系
    for (int i = 1; i < n; i++) {
        // 这里的条件判断就是 j 前面还有数据，并且前面的 j 比后面的数据大
        // 那么就需要进行一次交换
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
            // 使用异或交换
            arr[j] = arr[j] ^ arr[j + 1];
            arr[j + 1] = arr[j] ^ arr[j + 1];
            arr[j] = arr[j] ^ arr[j + 1];
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

    insertSort(arr, n);

    printf("排序后的数组:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
