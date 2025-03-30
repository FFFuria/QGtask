#include <stdio.h>

// 单层for循环排序0、1、2数组
// 三指针解决（荷兰国旗问题）
void sort012(int* arr, int n) {
    int left = 0;    // 指向0的右边界即最后一个0
    int mid = 0;    // 当前遍历位置
    int right = n - 1; // 指向2的左边界即第一个2

    while (mid <= right) {
        if (arr[mid] == 0) {
            // 当前元素是0，交换到左边
            int temp = arr[left];
            arr[left] = arr[mid];
            arr[mid] = temp;
            left++;
            mid++;
        } else if (arr[mid] == 1) {
            // 当前元素是1，直接跳过
            mid++;
        } else {
            // 当前元素是2，交换到右边
            int temp = arr[mid];
            arr[mid] = arr[right];
            arr[right] = temp;
            right--;
        }
    }
}

int main() {
    // 示例数组
    int arr[] = {1, 0, 2, 1, 1, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 打印原始数组
    printf("原始数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 调用排序函数
    sort012(arr, n);

    // 打印排序后的数组
    printf("排序后的数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}