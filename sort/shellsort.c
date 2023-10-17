#include <stdio.h>

void shellSort(int arr[], int n) {
    int i, j, increment;
    
    // 初始增量为数组长度的一半
    increment = n / 2;
    
    // 逐渐缩小增量，直到增量为1
    while (increment > 0) {
        for (i = increment; i < n; i++) {
            int temp = arr[i];
            // 对间隔increment的元素进行插入排序
            for (j = i; j >= increment && arr[j - increment] > temp; j -= increment) {
                arr[j] = arr[j - increment];
            }
            arr[j] = temp;
        }
        // 缩小增量
        increment = (increment + 1) / 2;
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

    shellSort(arr, n);

    printf("排序后的数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
