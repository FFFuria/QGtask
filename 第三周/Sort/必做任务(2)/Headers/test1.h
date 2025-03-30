#ifndef __SORTING_ALGORITHMS_H
#define __SORTING_ALGORITHMS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef int Status;

// 定义状态码
#define OK 1
#define ERROR -1

// 栈节点结构体，用于非递归快速排序
typedef struct {
    int left;
    int right;
} StackNode;

// 数组打印工具
void showNumbers(int nums[], int count);

// 交换两个数字的位置
void swapNumbers(int* data, int x, int y);

// 经典插入排序
void insertion(int* data, int size);

// 快排核心逻辑
void quickSort(int* data, int L, int R);

// 快排入口
void runQuickSort(int* data, int size);

// 计数排序实现
int* countSort(int numbers[], int count);

// 基数排序实现
void digitSort(int* nums, int count);

// 归并排序辅助函数
void mergeCore(int* data, int L, int R, int* temp);

// 归并排序入口
void mergeSort(int* data, int size);

// 优化版冒泡排序函数
void NewBubbleSort(int arr[], int n);

// 快速排序非递归版
void QuickSortNonRecursive(int* a, int n);

// 快速排序递归版（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right);

// 快速排序包装函数
void QuickSortWrapper(int* a, int n);

// 性能测试工具
void checkPerformance(void (*sorter)(int*, int), int* origin, int size, char* name);

// 特殊处理计数排序的测试
void testCountSort(int* origin, int size);

// 特殊处理非递归快速排序的测试
void testQuickSortNonRecursive(int* origin, int size);

// 特殊处理递归快速排序的测试
void testQQuickSortRecursive(int* origin, int size);

#endif // __SORTING_ALGORITHMS_H