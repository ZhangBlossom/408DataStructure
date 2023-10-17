#include <stdio.h>

void countingSort(int array[], int size) {
    // 找到数组中的最大值以确定计数数组的大小
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    // 创建计数数组并初始化为0
    int countArray[max + 1];
    for (int i = 0; i <= max; i++) {
        countArray[i] = 0;
    }

    // 计算每个元素出现的次数
    for (int i = 0; i < size; i++) {
        countArray[array[i]]++;
    }

    // 根据计数数组构建排序后的结果数组
    int resultArray[size];
    int resultIndex = 0;
    for (int i = 0; i <= max; i++) {
        while (countArray[i] > 0) {
            resultArray[resultIndex] = i;
            resultIndex++;
            countArray[i]--;
        }
    }

    // 将排序后的结果复制回原数组
    for (int i = 0; i < size; i++) {
        array[i] = resultArray[i];
    }
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    countingSort(arr, size);

    printf("排序后的数组：");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
