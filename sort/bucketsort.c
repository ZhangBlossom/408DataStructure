#include <stdio.h>

// 定义桶的数量（这里使用固定数量的桶，也可以根据实际情况动态分配）
#define BUCKET_COUNT 10

// 桶排序函数
void bucketSort(int arr[], int n) {
    // 创建桶，每个桶是一个数组
    int buckets[BUCKET_COUNT][n];
    // 每个桶的元素数量初始化为0
    int bucketSize[BUCKET_COUNT] = {0};
    
    // 找到最大值和最小值以确定数据范围
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    // 计算桶的范围和尺寸
    double range = (double)(max - min + 1) / BUCKET_COUNT;
    
    // 将元素放入桶中
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)((arr[i] - min) / range);
        buckets[bucketIndex][bucketSize[bucketIndex]++] = arr[i];
    }

    // 对每个桶中的元素进行排序（这里使用插入排序）
    for (int i = 0; i < BUCKET_COUNT; i++) {
        for (int j = 1; j < bucketSize[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }

    // 将排序后的元素从桶中提取到原数组
    int index = 0;
    for (int i = 0; i < BUCKET_COUNT; i++) {
        for (int j = 0; j < bucketSize[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

int main() {
    int n;
    printf("请输入数组的大小: ");
    scanf("%d", &n);
    int arr[n];

    printf("请输入 %d 个整数:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("原始数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bucketSort(arr, n);

    printf("排序后的数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}