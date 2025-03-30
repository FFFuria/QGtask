#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// 优化版冒泡排序函数
void NewBubbleSort(int arr[], int n) {
    int left = 0;          // 左边界
    int right = n - 1;     // 右边界
    int lastSwapIndex = 0; // 记录最后一次交换的位置
    int i;
    int newRight, newLeft;
    int hasSwap = 0;       // 标志位，0表示没有交换，1表示有交换

    while (left < right) {
        // 正向冒泡：从左到右，找到最大值放到右边界
        hasSwap = 0;
        newRight = left;
        for (i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                hasSwap = 1;
                newRight = i;
            }
        }
        right = newRight; // 更新右边界

        // 如果没有发生交换，提前终止
        if (!hasSwap) {
            break;
        }

        // 反向冒泡：从右到左，找到最小值放到左边界
        hasSwap = 0;
        newLeft = right;
        for (i = right; i > left; i--) {
            if (arr[i - 1] > arr[i]) {
                swap(arr, i - 1, i);
                hasSwap = 1;
                newLeft = i;
            }
        }
        left = newLeft; // 更新左边界

        // 如果没有发生交换，提前终止
        if (!hasSwap) {
            break;
        }
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 测试函数
int main() {
    int arr[] = {9, 35, 27, 10, 12, 5, 20, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    printArray(arr, n);

    NewBubbleSort(arr, n);

    printf("排序后数组: ");
    printArray(arr, n);

    return 0;
}