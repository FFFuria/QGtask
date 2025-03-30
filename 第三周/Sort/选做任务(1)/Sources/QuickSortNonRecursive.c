#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//快速排序非递归版
typedef struct {
    int left;
    int right;
} StackNode;

void QuickSortNonRecursive(int* a, int n) {
    if (n <= 0) {
        return;
    }

    StackNode* stack = (StackNode*)malloc(n * sizeof(StackNode));
    if (stack == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int top = -1;
    stack[++top].left = 0;
    stack[top].right = n - 1;

    while (top >= 0) {
        int left = stack[top].left;
        int right = stack[top].right;
        top--;

        if (left >= right) {
            continue;
        }

        int begin = left, end = right;
        int key = a[begin]; // 选择第一个元素作为基准值
        int pivot = begin; // 挖坑的位置

        while (begin < end) {
            // 右边找小
            while (begin < end && a[end] >= key) {
                end--;
            }
            // 小的放在左边的坑里
            a[pivot] = a[end];
            pivot = end;

            // 左边找大
            while (begin < end && a[begin] <= key) {
                begin++;
            }
            // 大的放在右边的坑里
            a[pivot] = a[begin];
            pivot = begin;
        }

        // 最终将基准值放回正确的位置
        a[pivot] = key;

        // 将左右子区间压入栈中
        stack[++top].left = left;
        stack[top].right = pivot - 1;
        stack[++top].left = pivot + 1;
        stack[top].right = right;
    }

    free(stack);
}

// 测试函数
int main() {
    int arr[] = {9, 35, 27, 10, 12, 5, 20, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    printArray(arr, n);

    QuickSortNonRecursive(arr, n);

    printf("排序后数组: ");
    printArray(arr, n);

    return 0;
}