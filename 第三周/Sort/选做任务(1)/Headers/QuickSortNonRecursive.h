#ifndef __QSORT_NON_RECURSIVE_H
#define __QSORT_NON_RECURSIVE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j);

// 打印数组函数
void printArray(int arr[], int n);

// 栈节点结构体，用于非递归快速排序
typedef struct {
    int left;
    int right;
} StackNode;

// 快速排序非递归版
void QuickSortNonRecursive(int* a, int n);

#endif // __QSORT_NON_RECURSIVE_H