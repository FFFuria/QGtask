#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// 数组打印工具
void showNumbers(int nums[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

// 交换两个数字的位置
void swapNumbers(int* data, int x, int y) {
    int t = data[x];
    data[x] = data[y];
    data[y] = t;
}

// 经典插入排序
void insertion(int* data, int size) {
    for (int i = 1; i < size; i++) {
        if (data[i] < data[i - 1]) { 
            int current = data[i];
            int j;
            for (j = i - 1; j >= 0 && data[j] > current; j--) {
                data[j + 1] = data[j]; 
            }
            data[j + 1] = current; 
        }
    }
}

// 快排核心逻辑
void quickSort(int* data, int L, int R) {
    if (L >= R) return;
    
    int left = L, right = R;
    int pivotValue = data[left];
    int hole = left;

    while (left < right) {
        while (left < right && data[right] >= pivotValue) {
            right--;
        }
        data[hole] = data[right];
        hole = right;

        while (left < right && data[left] <= pivotValue) {
            left++;
        }
        data[hole] = data[left];
        hole = left;
    }

    data[hole] = pivotValue;

    quickSort(data, L, hole - 1);
    quickSort(data, hole + 1, R);
}

// 快排入口
void runQuickSort(int* data, int size) {
    quickSort(data, 0, size - 1);
}

// 计数排序实现
int* countSort(int numbers[], int count) {
    if (count < 1) return NULL;

    int maxNum = numbers[0], minNum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > maxNum) maxNum = numbers[i];
        if (numbers[i] < minNum) minNum = numbers[i];
    }

    int range = maxNum - minNum + 1;
    int* counter = calloc(range, sizeof(int));
    int* output = malloc(count * sizeof(int));

    if (!counter || !output) {
        free(counter);
        free(output);
        return NULL;
    }

    for (int i = 0; i < count; i++) 
        counter[numbers[i] - minNum]++;

    int idx = 0;
    for (int j = 0; j < range; j++) {
        while (counter[j]-- > 0) {
            output[idx++] = j + minNum;
        }
    }

    free(counter);
    return output;
}

// 基数排序实现
void digitSort(int* nums, int count) {
    if (count < 1) return;

    int maxVal = nums[0];
    for (int i = 1; i < count; i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    int digits = (maxVal == 0) ? 1 : (int)log10(maxVal) + 1;

    for (int d = 0; d < digits; d++) {
        int** buckets = malloc(10 * sizeof(int*));
        for (int k = 0; k < 10; k++) {
            buckets[k] = malloc(count * sizeof(int));
        }
        int counts[10] = {0};
        int divisor = (int)pow(10, d);

        for (int j = 0; j < count; j++) {
            int digit = (nums[j] / divisor) % 10;
            buckets[digit][counts[digit]++] = nums[j];
        }

        int pos = 0;
        for (int k = 0; k < 10; k++) {
            for (int m = 0; m < counts[k]; m++) {
                nums[pos++] = buckets[k][m];
            }
            free(buckets[k]);
        }
        free(buckets);
    }
}

// 归并排序辅助函数
void mergeCore(int* data, int L, int R, int* temp) {
    if (L >= R) return;
    
    int mid = L + (R - L)/2;
    mergeCore(data, L, mid, temp);
    mergeCore(data, mid+1, R, temp);

    int i = L, l = L, r = mid+1;
    while (l <= mid && r <= R) {
        temp[i++] = data[l] <= data[r] ? data[l++] : data[r++];
    }
    while (l <= mid) temp[i++] = data[l++];
    while (r <= R) temp[i++] = data[r++];
    
    for (int j = L; j <= R; j++) 
        data[j] = temp[j];
}

// 归并排序入口
void mergeSort(int* data, int size) {
    int* temp = malloc(size * sizeof(int));
    if (!temp) {
        fprintf(stderr, "归并排序内存分配失败!\n");
        return;
    }
    mergeCore(data, 0, size-1, temp);
    free(temp);
}

// 优化版冒泡排序函数
void NewBubbleSort(int arr[], int n) {
    int left = 0;          
    int right = n - 1;     
    int lastSwapIndex = 0;  
    int i;
    int newRight, newLeft;
    int hasSwap = 0;       

    while (left < right) {
        hasSwap = 0;
        newRight = left;
        for (i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swapNumbers(arr, i, i + 1);
                hasSwap = 1;
                newRight = i;
            }
        }
        right = newRight; 

        if (!hasSwap) {
            break;
        }

        hasSwap = 0;
        newLeft = right;
        for (i = right; i > left; i--) {
            if (arr[i - 1] > arr[i]) {
                swapNumbers(arr, i - 1, i);
                hasSwap = 1;
                newLeft = i;
            }
        }
        left = newLeft; 

        if (!hasSwap) {
            break;
        }
    }
}

// 快速排序非递归版
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
        int key = a[begin]; 
        int pivot = begin; 

        while (begin < end) {
            while (begin < end && a[end] >= key) {
                end--;
            }
            a[pivot] = a[end];
            pivot = end;

            while (begin < end && a[begin] <= key) {
                begin++;
            }
            a[pivot] = a[begin];
            pivot = begin;
        }

        a[pivot] = key;

        stack[++top].left = left;
        stack[top].right = pivot - 1;
        stack[++top].left = pivot + 1;
        stack[top].right = right;
    }

    free(stack);
}

// 快速排序递归版（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right) {
    if (left >= right) {
        return;
    }

    int randomIndex = left + rand() % (right - left + 1);
    swapNumbers(a, left, randomIndex);

    int key = a[left];
    int lt = left;    
    int gt = right;   
    int i = left + 1; 

    while (i <= gt) {
        if (a[i] < key) {
            swapNumbers(a, i, lt + 1);
            lt++;
            i++;
        } else if (a[i] > key) {
            swapNumbers(a, i, gt);
            gt--;
        } else {
            i++;
        }
    }

    swapNumbers(a, left, lt);

    QQuickSortRecursive(a, left, lt - 1);
    QQuickSortRecursive(a, gt + 1, right);
}

// 快速排序包装函数
void QQuickSortWrapper(int* a, int n) {
    QQuickSortRecursive(a, 0, n - 1);
}

// 演示函数
void demonstrateSortingAlgorithms(int* arr, int size) {
    // 复制数组用于演示
    int* arr1 = malloc(size * sizeof(int));
    int* arr2 = malloc(size * sizeof(int));
    int* arr3 = malloc(size * sizeof(int));
    int* arr4 = malloc(size * sizeof(int));
    int* arr5 = malloc(size * sizeof(int));
    int* arr6 = malloc(size * sizeof(int));
    int* arr7 = malloc(size * sizeof(int));
    int* arr8 = malloc(size * sizeof(int));

    memcpy(arr1, arr, size * sizeof(int));
    memcpy(arr2, arr, size * sizeof(int));
    memcpy(arr3, arr, size * sizeof(int));
    memcpy(arr4, arr, size * sizeof(int));
    memcpy(arr5, arr, size * sizeof(int));
    memcpy(arr6, arr, size * sizeof(int));
    memcpy(arr7, arr, size * sizeof(int));
    memcpy(arr8, arr, size * sizeof(int));

    // 演示插入排序
    printf("插入排序:\n");
    printf("原始数组: ");
    showNumbers(arr1, size);
    insertion(arr1, size);
    printf("排序后数组: ");
    showNumbers(arr1, size);
    printf("\n");

    // 演示快速排序
    printf("快速排序:\n");
    printf("原始数组: ");
    showNumbers(arr2, size);
    runQuickSort(arr2, size);
    printf("排序后数组: ");
    showNumbers(arr2, size);
    printf("\n");

    // 演示计数排序
    printf("计数排序:\n");
    printf("原始数组: ");
    showNumbers(arr3, size);
    int* sorted3 = countSort(arr3, size);
    printf("排序后数组: ");
    showNumbers(sorted3, size);
    printf("\n");
    free(sorted3);

    // 演示基数排序
    printf("基数排序:\n");
    printf("原始数组: ");
    showNumbers(arr4, size);
    digitSort(arr4, size);
    printf("排序后数组: ");
    showNumbers(arr4, size);
    printf("\n");

    // 演示归并排序
    printf("归并排序:\n");
    printf("原始数组: ");
    showNumbers(arr5, size);
    mergeSort(arr5, size);
    printf("排序后数组: ");
    showNumbers(arr5, size);
    printf("\n");

    // 演示优化冒泡排序
    printf("优化冒泡排序:\n");
    printf("原始数组: ");
    showNumbers(arr6, size);
    NewBubbleSort(arr6, size);
    printf("排序后数组: ");
    showNumbers(arr6, size);
    printf("\n");

    // 演示非递归快速排序
    printf("非递归快速排序:\n");
    printf("原始数组: ");
    showNumbers(arr7, size);
    QuickSortNonRecursive(arr7, size);
    printf("排序后数组: ");
    showNumbers(arr7, size);
    printf("\n");

    // 演示递归快速排序
    printf("递归快速排序:\n");
    printf("原始数组: ");
    showNumbers(arr8, size);
    QQuickSortWrapper(arr8, size);
    printf("排序后数组: ");
    showNumbers(arr8, size);
    printf("\n");

    // 释放内存
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
    free(arr7);
    free(arr8);
}

int main() {
    // 演示数组
    int arr[] = {9, 35, 27, 10, 12, 5, 20, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    demonstrateSortingAlgorithms(arr, size);

    return 0;
}