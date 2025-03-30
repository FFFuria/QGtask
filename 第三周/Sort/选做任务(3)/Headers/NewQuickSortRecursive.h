#ifndef __QSORT_H
#define __QSORT_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j);

// 快速排序递归版（随机优化 + 三枢纽优化）
void QQuickSortRecursive(int* a, int left, int right);

// 快速排序包装函数
void QuickSortWrapper(int* a, int n);

// 打印数组函数
void printArray(int arr[], int n);

#endif // __QSORT_H