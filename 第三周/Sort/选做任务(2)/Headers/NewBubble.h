#ifndef __NEW_BUBBLE_SORT_H
#define __NEW_BUBBLE_SORT_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 交换数组中两个元素的函数
void swap(int* a, int i, int j);

// 打印数组函数
void printArray(int arr[], int n);

// 优化版冒泡排序函数
void NewBubbleSort(int arr[], int n);

#endif // __NEW_BUBBLE_SORT_H