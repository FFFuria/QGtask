#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 随机选择基准值并进行划分
int DiviseInto(int* arr, int left, int right) {
    int randomIndex = left + rand() % (right - left + 1);
    int pivot = arr[randomIndex];
    int temp;

    // 将基准值交换到左边
    temp = arr[left];
    arr[left] = arr[randomIndex];
    arr[randomIndex] = temp;

    int low = left;
    int high = right;

    while (low < high) {
        while (low < high && arr[high] >= pivot) {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

// 查找第K小的数
int KFind(int* arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = DiviseInto(arr, left, right);

    if (pivotIndex == k - 1) {
        return arr[pivotIndex];
    } else if (pivotIndex > k - 1) {
        return KFind(arr, left, pivotIndex - 1, k);
    } else {
        return KFind(arr, pivotIndex + 1, right, k);
    }
}

int main() {
    srand(time(NULL));

    // 示例数组
    int arr[] = {5, 2, 8, 4, 3, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; // 找第3小的数

    // 打印原始数组
    printf("原始数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 查找第K小的数
    int result = KFind(arr, 0, n - 1, k);

    // 打印结果
    printf("第%d小的数是: %d\n", k, result);

    return 0;
}