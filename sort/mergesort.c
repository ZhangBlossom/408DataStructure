#include <stdio.h>

// 提前声明merge函数
void merge(int arr[], int left, int middle, int right);
void mergeSort(int arr[], int left, int right);

void mergeSort(int arr[], int left, int right)
{
    if (left == right)
    {
        return;
    }
    int mid = ((right - left) >> 1) + left;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right)
{
    // 创建一个辅助空间 left--right上有多少个数就开多大的空间
    int help[right - left + 1];
    int i = 0;        // 提供给help使用的变量
    int p1 = left;    // 左侧数据的下标
    int p2 = mid + 1; // 指向mid+1位置
    // 判断p1和p2是否越界，如果都不越界
    // 那么谁小谁就拷贝到数组help中去
    while (p1 <= mid && p2 <= right)
    {
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    // 继续判断是否有没有拷贝完毕的数据
    // 可能是左半部分的p1没有拷贝完毕
    while (p1 <= mid)
    {
        help[i++] = arr[p1++];
    }
    // 也可能是右侧的p2没有拷贝完毕
    while (p2 <= right)
    {
        help[i++] = arr[p2++];
    }
    // 将help上面有序的数据拷贝到原数组上去，就得到了区间上有序数据
    for (i = 0; i < (sizeof(help) / sizeof(help[0])); i++)
    {
        arr[left + i] = help[i];
    }
}

int main()
{
    int arr[] = {12, 11, 13,2312,123,556,887, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组:\n");
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, 0, arr_size - 1);

    printf("排序后的数组:\n");
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
