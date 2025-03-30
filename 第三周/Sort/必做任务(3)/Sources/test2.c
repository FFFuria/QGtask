#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 交换数组中两个元素的函数
void swap(int* a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// 经典插入排序
void InsertSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) { 
            int tmp = a[i];
            int j;
            for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
                a[j + 1] = a[j]; 
            }
            a[j + 1] = tmp; 
        }
    }
}

// 快速排序递归版
void QuickSortRecursive(int* a, int left, int right) {
    if (left >= right) {
        return;
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

    QuickSortRecursive(a, left, pivot - 1);
    QuickSortRecursive(a, pivot + 1, right);
}

// 快速排序包装函数
void QuickSortWrapper(int* a, int n) {
    QuickSortRecursive(a, 0, n - 1);
}

// 计数排序
int *countingSort(int arr[], int n) {
    if (n <= 0) {
        return NULL;
    }

    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int range = max - min + 1;
    int *tmpArr = (int *)malloc(range * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    if (tmpArr == NULL || result == NULL) {
        free(tmpArr);
        free(result);
        return NULL;
    }

    for (int k = 0; k < range; k++) {
        tmpArr[k] = 0;
    }

    for (int i = 0; i < n; i++) {
        tmpArr[arr[i] - min]++;
    }

    int index = 0;
    for (int j = 0; j < range; j++) {
        while (tmpArr[j] > 0) {
            result[index++] = j + min;
            tmpArr[j]--;
        }
    }

    free(tmpArr);
    return result;
}

// 基数排序
void radixSort(int *arr, int n) {
    if (n <= 0) {
        return;
    }

    int maxNum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }

    int loopTimes = (maxNum == 0) ? 1 : (int)log10(maxNum) + 1;

    for (int i = 1; i <= loopTimes; i++) {
        int **buckets = (int **)malloc(sizeof(int *) * 10);
        for (int j = 0; j < 10; j++) {
            buckets[j] = (int *)malloc(sizeof(int) * n);
        }
        int bucketCounts[10] = {0};

        int tempNum = (int)pow(10, i - 1);

        for (int j = 0; j < n; j++) {
            int row_index = (arr[j] / tempNum) % 10;
            buckets[row_index][bucketCounts[row_index]++] = arr[j];
        }

        int k = 0;
        for (int j = 0; j < 10; j++) {
            for (int m = 0; m < bucketCounts[j]; m++) {
                arr[k++] = buckets[j][m];
            }
            free(buckets[j]);
        }
        free(buckets);
    }
}

// 归并排序
void _MergeSort(int* a, int left, int right, int* tmp) {
    if (left >= right) {
        return;
    }
    int mid = left + ((right - left) >> 1);
    _MergeSort(a, left, mid, tmp);
    _MergeSort(a, mid + 1, right, tmp);

    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    int i = left;
    while (begin1 <= end1 && begin2 <= end2) {
        if (a[begin1] <= a[begin2]) {
            tmp[i++] = a[begin1++];
        } else {
            tmp[i++] = a[begin2++];
        }
    }
    while (begin1 <= end1) {
        tmp[i++] = a[begin1++];
    }
    while (begin2 <= end2) {
        tmp[i++] = a[begin2++];
    }
    for (int j = left; j <= right; j++) {
        a[j] = tmp[j];
    }
}

void MergeSort(int* a, int n) {
    if (n <= 0) {
        return;
    }
    int* tmp = (int*)malloc(n * sizeof(int));
    if (tmp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    _MergeSort(a, 0, n - 1, tmp);
    free(tmp);
}

// 优化冒泡排序
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
                swap(arr, i, i + 1);
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
                swap(arr, i - 1, i);
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

// 非递归快速排序
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

// 递归快速排序（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right) {
    if (left >= right) {
        return;
    }

    int randomIndex = left + rand() % (right - left + 1);
    swap(a, left, randomIndex);

    int key = a[left];
    int lt = left;    
    int gt = right;   
    int i = left + 1; 

    while (i <= gt) {
        if (a[i] < key) {
            swap(a, i, lt + 1);
            lt++;
            i++;
        } else if (a[i] > key) {
            swap(a, i, gt);
            gt--;
        } else {
            i++;
        }
    }

    swap(a, left, lt);

    QQuickSortRecursive(a, left, lt - 1);
    QQuickSortRecursive(a, gt + 1, right);
}

// 递归快速排序包装函数
void QQuickSortWrapper(int* a, int n) {
    QQuickSortRecursive(a, 0, n - 1);
}

// 测试函数
void testSortFunction(void (*sorter)(int*, int), int* arr, int n, const char* name, int iterations) {
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        int* copy = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[i];
        }

        clock_t start = clock();
        sorter(copy, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        total_time += time_spent;
        free(copy);
    }

    printf("%s排序用时: %.6f秒\n", name, total_time / iterations);
}

// 测试计数排序
void testCountingSort(int* arr, int n, int iterations) {
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        int* copy = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[i];
        }

        clock_t start = clock();
        int* sorted = countingSort(copy, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        total_time += time_spent;
        free(copy);
        free(sorted);
    }

    printf("计数排序用时: %.6f秒\n", total_time / iterations);
}

// 测试优化冒泡排序
void testNewBubbleSort(int* arr, int n, int iterations) {
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        int* copy = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[i];
        }

        clock_t start = clock();
        NewBubbleSort(copy, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        total_time += time_spent;
        free(copy);
    }

    printf("优化冒泡排序用时: %.6f秒\n", total_time / iterations);
}

// 测试非递归快速排序
void testQuickSortNonRecursive(int* arr, int n, int iterations) {
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        int* copy = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[i];
        }

        clock_t start = clock();
        QuickSortNonRecursive(copy, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        total_time += time_spent;
        free(copy);
    }

    printf("非递归快速排序用时: %.6f秒\n", total_time / iterations);
}

// 测试递归快速排序
void testQQuickSortRecursive(int* arr, int n, int iterations) {
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        int* copy = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[i];
        }

        clock_t start = clock();
        QQuickSortWrapper(copy, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        total_time += time_spent;
        free(copy);
    }

    printf("递归快速排序用时: %.6f秒\n", total_time / iterations);
}

int main() {
    int n = 100;
    int iterations = 100000;

    srand(time(NULL));

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }

    printf("数据规模: %d，迭代次数: %d\n", n, iterations);

    testSortFunction(InsertSort, arr, n, "插入", iterations);
    testSortFunction(QuickSortWrapper, arr, n, "快速", iterations);
    testCountingSort(arr, n, iterations);
    testSortFunction(radixSort, arr, n, "基数", iterations);
    testSortFunction(MergeSort, arr, n, "归并", iterations);
    testNewBubbleSort(arr, n, iterations);
    testQuickSortNonRecursive(arr, n, iterations);
    testQQuickSortRecursive(arr, n, iterations);

    free(arr);

    return 0;
}