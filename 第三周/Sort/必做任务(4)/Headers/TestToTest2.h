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

// 插入排序
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
void merge(int arr[], int tempArr[], int left, int mid, int right);

// 归并排序核心函数
void _MergeSort(int* a, int left, int right, int* tmp);

// 归并排序包装函数
void MergeSort(int* a, int n);

// 测试排序函数
void testSortFunction(void (*sortFunc)(int*, int), int* arr, int n, const char* name);

// 测试计数排序
void testCountingSort(int* arr, int n);

#endif // __SORT_ALGORITHMS_H