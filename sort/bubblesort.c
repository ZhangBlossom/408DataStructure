#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    if (arr == NULL || n < 2)
    {
        return;
    }
    int flag = 0;
    // 这是第几轮
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        // 这一层的for循环的意思就是当前轮需要包含的数据的个数
        // 因为每一次冒泡，都会有一个最大的数据到末尾去
        // 所以需要不断的减少需要参与计算的数据量
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // 使用异或交换
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
                flag = 1;
            }
        }
        //如果此时已经没有数据更新，那么说明已经有序，直接跳出循环
        if (flag == 0)
        {
            break;
        }
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubbleSort(arr, n);

    printf("排序后的数组:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
