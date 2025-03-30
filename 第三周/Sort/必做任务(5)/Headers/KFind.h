#ifndef __QUICKSELECT_H
#define __QUICKSELECT_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Status;

// 定义状态码
#define OK 1
#define ERROR -1

// 函数声明
int DiviseInto(int* arr, int left, int right);
int KFind(int* arr, int left, int right, int k);

#endif // __QUICKSELECT_H