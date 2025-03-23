#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

// 首次编译运行需要在命令窗等待五秒左右

typedef struct LNode                            // 带头结点链表定义
{
    double data;                                 // data数据域，改为double类型以支持小数
    struct LNode * next;                         // next指针域
} LNode,*LinkList;                               // 为结构体定义别名LNode和LinkList

int Priority(char op);                           // 运算符优先级判断
bool isOperator(char c);                         // 运算符验证
bool MidToRPolish(const char *mid, char *RPolish); // 中缀转后缀
double EvaluateRPolish(const char *RPolish);     // 后缀表达式求值，返回值改为double

bool List_Init(LinkList *pHead)                  // 初始化链表（C风格指针传递）
{
    *pHead = (LNode *)malloc(sizeof(LNode));     // 为头结点分配内存
    if (*pHead == NULL) return false;            // 内存分配失败检查
    (*pHead)->next = NULL;                       // 初始化头节点指针
    return true;
}

bool List_Empty(LinkList pHead)                  // 判断链表是否为空
{
    return pHead->next == NULL;                  // 检查头结点指针状态
}

// 栈的入栈操作push
bool Stack_Push(LinkList *pHead, double e)
{
    LNode *pTemp = (LNode *)malloc(sizeof(LNode));
    if (!pTemp) return false;
    pTemp->data = e;
    pTemp->next = (*pHead)->next;               // 新节点插入链表头部
    (*pHead)->next = pTemp;
    return true;
}

// 栈的出栈操作pop
bool Stack_Pop(LinkList *pHead, double *e)
{
    if (List_Empty(*pHead)) return false;
    LNode *pTemp = (*pHead)->next;               // 获取栈顶元素
    *e = pTemp->data;                            // 保存数据值
    (*pHead)->next = pTemp->next;                // 更新头指针
    free(pTemp);                                 // 释放节点内存
    return true;
}

// 获取栈顶元素
bool Stack_Peek(LinkList pHead, double *e)
{
    if (List_Empty(pHead)) return false;
    *e = pHead->next->data;                      // 直接获取栈顶数据
    return true;
}

int Priority(char op)                             // 运算符优先级判断
{
    if (op == '+' || op == '-') return 1;        // 低级优先级
    if (op == '*' || op == '/') return 2;        // 高级优先级
    return 0;                                    // 默认优先级
}

bool isOperator(char c)                           // 运算符验证
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 中缀转后缀表达式
bool MidToRPolish(const char *mid, char *RPolish)
{
    LinkList opStack;                             // 运算符栈
    List_Init(&opStack);
    int i = 0, k = 0;
    
    while (mid[i] != '\0') 
	{
        // 跳过空格
        while (mid[i] == ' ') i++;
        if (mid[i] == '\0') break;

        // 处理数字（支持小数）
        if (isdigit(mid[i]) || mid[i] == '.') 
		{
            while (isdigit(mid[i]) || mid[i] == '.') 
			{            
                RPolish[k++] = mid[i++];
            }
            RPolish[k++] = ' ';                 // 数字间添加空格分隔
            i--;                                // 回退外层循环的i++
        }
        // 处理左括号
        else if (mid[i] == '(') 
		{
            Stack_Push(&opStack, mid[i]);
        }
        // 处理右括号
        else if (mid[i] == ')') 
		{
            double op;
            bool found = false;
            while (Stack_Pop(&opStack, &op)) 
			{
                if (op == '(') 
				{                 				// 找到匹配左括号
                    found = true;
                    break;
                }
                RPolish[k++] = op;              // 添加运算符
                RPolish[k++] = ' ';
            }
            if (!found) 
			{                       			// 括号不匹配检测
                printf("错误：括号不匹配\n");
                return false;
            }
        }
        // 处理运算符
        else if (isOperator(mid[i]))
		{
            while (!List_Empty(opStack)) 
			{
                double topOp;
                Stack_Peek(opStack, &topOp);
                if (Priority(mid[i]) <= Priority(topOp)) 
				{
                    Stack_Pop(&opStack, &topOp);
                    RPolish[k++] = topOp;
                    RPolish[k++] = ' ';
                } 
				else 
				{
                    break;
                }
            }
            Stack_Push(&opStack, mid[i]);
        }
        else 
		{                                   		// 无效字符处理
            printf("错误：非法字符 '%c'\n", mid[i]);
            return false;
        }
        i++;                                     	// 移动至下一个字符
    }

    // 弹出剩余运算符
    while (!List_Empty(opStack)) 
	{
        double op;
        Stack_Pop(&opStack, &op);
        if (op == '(') 							// 检测未闭合括号
		{                         				
            printf("错误：括号不匹配\n");
            return false;
        }
        RPolish[k++] = op;
        RPolish[k++] = ' ';
    }
    RPolish[k] = '\0';                           // 字符串结束符
    return true;
}

// 后缀表达式求值（支持小数）
double EvaluateRPolish(const char *RPolish)
{
    LinkList numStack;                           // 操作数栈
    List_Init(&numStack);
    int i = 0;

    while (RPolish[i] != '\0') 
	{
        if (isspace(RPolish[i])) 				// 跳过空格
		{               
            i++;
            continue;
        }

        // 处理数字（支持小数）
        if (isdigit(RPolish[i]) || RPolish[i] == '.') 
		{
            double num = 0.0;
            int pointFlag = 0;                   // 小数点标志
            int pointPosition = 0;               // 小数点位置

            while (isdigit(RPolish[i]) || RPolish[i] == '.') 
			{
                if (RPolish[i] == '.') 
				{
                    pointFlag = 1;
                    pointPosition = i;
                } 
				else 
				{
                    if (pointFlag == 0) 
					{
                        num = num * 10 + (RPolish[i] - '0');
                    } 
					else 
					{
                        num = num + (RPolish[i] - '0') * pow(10, -(i - pointPosition));
                    }
                }
                i++;
            }
            Stack_Push(&numStack, num);
        }
        // 处理运算符
        else if (isOperator(RPolish[i])) 
		{
            double b, a;
            if (!Stack_Pop(&numStack, &b) || !Stack_Pop(&numStack, &a)) 
			{
                printf("错误：操作数不足\n");
                return 0.0;
            }
            switch (RPolish[i]) 				// 执行运算
			{                
                case '+': Stack_Push(&numStack, a + b); break;
                case '-': Stack_Push(&numStack, a - b); break;
                case '*': Stack_Push(&numStack, a * b); break;
                case '/':
                    if (b == 0) 
					{
                        printf("错误：除零错误\n");
                        return 0.0;
                    }
                    Stack_Push(&numStack, a / b);
                    break;
            }
        }
        i++;
    }

    double result;
    if (!Stack_Pop(&numStack, &result) || !List_Empty(numStack)) 
	{
        printf("错误：表达式不合法\n");
        return 0.0;
    }
    return result;
}

int main()
{
    LinkList pHead;
    List_Init(&pHead);                           // 初始化链表
    printf("计算器初始化完成。\n");

    int choice;
    bool continueOperation = true;

    while (continueOperation) 
	{
        printf("\n请选择操作：\n");
        printf("1. 四则运算计算\n");
        printf("2. 退出\n");
        printf("请输入选择：");
        
        if (scanf("%d", &choice) != 1) 
		{
            printf("输入错误，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) 
		{
            case 1: 
			{
                char expr[100], polish[200];
                printf("请输入表达式(均为英文符号)：");
                getchar(); // 清除缓冲区
                if (fgets(expr, sizeof(expr), stdin) == NULL) 
				{ // 输入错误处理
                    printf("输入读取失败\n");
                    break;
                }
                expr[strcspn(expr, "\n")] = '\0'; // 去除换行符
                if (strlen(expr) == 0) 
				{
                    printf("错误：不能输入空表达式\n");
                    break;
                }
    
                if (MidToRPolish(expr, polish)) 
				{
                    printf("后缀表达式：%s\n", polish);
                    double result = EvaluateRPolish(polish);
                    printf("计算结果：%.2f\n", result);
                } 
				else
				{
                    printf("表达式转换失败\n");
                }
                break;
            }
            case 2: 
			{
                printf("程序退出\n");
                return 0;
            }
            default:
                printf("无效选择\n");
        }

        // 继续操作确认
        if (choice != 2) 
		{
            printf("继续操作？(y/n): ");
            char cmd;
            scanf(" %c", &cmd);
            continueOperation = (tolower(cmd) == 'y');
        }
    }
    return 0;
}