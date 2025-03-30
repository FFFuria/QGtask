#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    // 数据规模
    int sizes[] = {10000, 50000, 200000};
    int numSizes = sizeof(sizes) / sizeof(int);

    // 随机种子
    srand(time(NULL));

    // 生成每种数据规模的测试数据并保存到文件
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // 生成随机数据
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000000; // 随机数范围0到999999
        }

        // 保存到文件
        char filename[50];
        sprintf(filename, "testdata_%d.txt", n);
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            printf("Failed to create file for size %d.\n", n);
            free(arr);
            continue;
        }

        for (int j = 0; j < n; j++) {
            fprintf(file, "%d\n", arr[j]);
        }

        fclose(file);
        printf("Generated test data for size %d and saved to %s\n", n, filename);
        free(arr);
    }

    return 0;
}