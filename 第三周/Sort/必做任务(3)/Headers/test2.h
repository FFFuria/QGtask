#ifndef __SORT_ALGORITHMS_H
#define __SORT_ALGORITHMS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 打印数组函数
void printArray(int arr[], int n);

// 交换数组中两个元素的函数
void swap(int* a, int i, int j);

// 经典插入排序
void InsertSort(int* a, int n);

// 快速排序递归版
void QuickSortRecursive(int* a, int left, int right);

// 快速排序包装函数
void QuickSortWrapper(int* a, int n);

// 计数排序
int* countingSort(int arr[], int n);

// 基数排序
void radixSort(int* arr, int n);

// 归并排序辅助函数
void _MergeSort(int* a, int left, int right, int* tmp);

// 归并排序包装函数
void MergeSort(int* a, int n);

// 优化冒泡排序
void NewBubbleSort(int arr[], int n);

// 非递归快速排序
typedef struct {
    int left;
    int right;
} StackNode;

void QuickSortNonRecursive(int* a, int n);

// 递归快速排序（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right);

// 递归快速排序包装函数
void QQuickSortWrapper(int* a, int n);

// 测试排序函数
void testSortFunction(void (*sorter)(int*, int), int* arr, int n, const char* name, int iterations);

// 测试计数排序
void testCountingSort(int* arr, int n, int iterations);

// 测试优化冒泡排序
void testNewBubbleSort(int* arr, int n, int iterations);

// 测试非递归快速排序
void testQuickSortNonRecursive(int* arr, int n, int iterations);

// 测试递归快速排序
void testQQuickSortRecursive(int* arr, int n, int iterations);

#endif // __SORT_ALGORITHMS_H