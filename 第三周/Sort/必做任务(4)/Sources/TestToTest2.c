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

//	插入排序
void InsertSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) { // 如果当前元素小于前一个元素，需要插入
            int tmp = a[i];
            int j;
            for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
                a[j + 1] = a[j]; // 向后移动元素
            }
            a[j + 1] = tmp; // 插入当前元素
        }
    }
}

//快速排序(递归版)
void QuickSortRecursive(int* a, int left, int right) {
    if (left >= right) {
        return;
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

    // 递归排序左右子区间
    QuickSortRecursive(a, left, pivot - 1);
    QuickSortRecursive(a, pivot + 1, right);
}

// 快速排序包装函数
void QuickSortWrapper(int* a, int n) {
    QuickSortRecursive(a, 0, n - 1);
}

//计数排序
int *countingSort(int arr[], int n) {
    if (n <= 0) {
        return NULL;
    }

    // 找到数组中的最大值和最小值
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

    // 计算范围
    int range = max - min + 1;

    // 分配临时数组和结果数组
    int *tmpArr = (int *)malloc(range * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    if (tmpArr == NULL || result == NULL) {
        // 如果分配失败，释放已分配的内存并返回NULL
        free(tmpArr);
        free(result);
        return NULL;
    }

    // 初始化临时数组
    for (int k = 0; k < range; k++) {
        tmpArr[k] = 0;
    }

    // 计数阶段
    for (int i = 0; i < n; i++) {
        tmpArr[arr[i] - min]++;
    }

    // 构建结果数组
    int index = 0;
    for (int j = 0; j < range; j++) {
        while (tmpArr[j] > 0) {
            result[index++] = j + min;
            tmpArr[j]--;
        }
    }

    // 释放临时数组
    free(tmpArr);
    return result;
}

//基数排序
void radixSort(int *arr, int n) {
    if (n <= 0) {
        return;
    }

    // 找到数组中的最大值
    int maxNum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }

    // 计算最大值的位数
    int loopTimes = (maxNum == 0) ? 1 : (int)log10(maxNum) + 1;

    // 对每一位进行排序
    for (int i = 1; i <= loopTimes; i++) {
        // 创建桶和计数数组
        int **buckets = (int **)malloc(sizeof(int *) * 10);
        for (int j = 0; j < 10; j++) {
            buckets[j] = (int *)malloc(sizeof(int) * n);
        }
        int bucketCounts[10] = {0};

        // 计算当前位的权值
        int tempNum = (int)pow(10, i - 1);

        // 将元素分配到桶中
        for (int j = 0; j < n; j++) {
            int row_index = (arr[j] / tempNum) % 10;
            buckets[row_index][bucketCounts[row_index]++] = arr[j];
        }

        // 将桶中的元素收集回原数组
        int k = 0;
        for (int j = 0; j < 10; j++) {
            for (int m = 0; m < bucketCounts[j]; m++) {
                arr[k++] = buckets[j][m];
            }
            free(buckets[j]); // 释放桶的内存
        }
        free(buckets); // 释放桶数组的内存
    }
}

//归并排序
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

void merge(int arr[], int tempArr[], int left, int mid, int right) {
    int l_pos = left;
    int r_pos = mid + 1;
    int pos = left;

    while (l_pos <= mid && r_pos <= right) {
        if (arr[l_pos] < arr[r_pos]) {
            tempArr[pos++] = arr[l_pos++];
        } else {
            tempArr[pos++] = arr[r_pos++];
        }
    }

    while (l_pos <= mid) {
        tempArr[pos++] = arr[l_pos++];
    }

    while (r_pos <= right) {
        tempArr[pos++] = arr[r_pos++];
    }

    for (int j = left; j <= right; j++) {
        arr[j] = tempArr[j];
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

// 测试函数
void testSortFunction(void (*sortFunc)(int*, int), int* arr, int n, const char* name) {
    // 复制数组
    int* copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    // 记录开始时间
    clock_t start = clock();

    // 调用排序函数
    sortFunc(copy, n);

    // 记录结束时间
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // 打印结果
    printf("%s排序用时: %.6f秒\n", name, time_spent);

    // 释放内存
    free(copy);
}

// 测试计数排序
void testCountingSort(int* arr, int n) {
    // 复制数组
    int* copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    // 记录开始时间
    clock_t start = clock();

    // 调用计数排序
    int* sorted = countingSort(copy, n);

    // 记录结束时间
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // 打印结果
    printf("计数排序用时: %.6f秒\n", time_spent);

    // 释放内存
    free(copy);
    free(sorted);
}

int main() {
    // 数据规模
    int sizes[] = {10000, 50000, 200000};
    int numSizes = sizeof(sizes) / sizeof(int);

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        char filename[50];
        sprintf(filename, "testdata_%d.txt", n);

        // 读取文件
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("Failed to open file for size %d.\n", n);
            continue;
        }

        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            continue;
        }

        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &arr[j]);
        }
        fclose(file);

        printf("数据规模: %d\n", n);

        // 测试插入排序
        testSortFunction(InsertSort, arr, n, "插入");

        // 测试快速排序
        testSortFunction(QuickSortWrapper, arr, n, "快速");

        // 测试计数排序
        testCountingSort(arr, n);

        // 测试基数排序
        testSortFunction(radixSort, arr, n, "基数");

        // 测试归并排序
        testSortFunction(MergeSort, arr, n, "归并");

        // 释放内存
        free(arr);
        printf("\n");
    }

    return 0;
}