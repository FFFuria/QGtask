#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// 快速排序递归版（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right) {
    if (left >= right) {
        return;
    }

    // 随机选择基准值
    int randomIndex = left + rand() % (right - left + 1);
    swap(a, left, randomIndex);

    int key = a[left];
    int lt = left;    // 小于基准值的区域右边界
    int gt = right;   // 大于基准值的区域左边界
    int i = left + 1; // 当前遍历位置

    // 三枢纽分区
    while (i <= gt) {
        if (a[i] < key) {
            // 当前元素小于基准值，交换到左边区域
            swap(a, i, lt + 1);
            lt++;
            i++;
        } else if (a[i] > key) {
            // 当前元素大于基准值，交换到右边区域
            swap(a, i, gt);
            gt--;
        } else {
            // 当前元素等于基准值，直接跳过
            i++;
        }
    }

    // 将基准值放置到正确的位置
    swap(a, left, lt);

    // 递归排序小于和大于基准值的区域
    QQuickSortRecursive(a, left, lt - 1);
    QQuickSortRecursive(a, gt + 1, right);
}

// 快速排序包装函数
void QuickSortWrapper(int* a, int n) {
    QQuickSortRecursive(a, 0, n - 1);
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

    // 调用包装函数
    QuickSortWrapper(arr, n);

    printf("排序后数组: ");
    printArray(arr, n);

    return 0;
}