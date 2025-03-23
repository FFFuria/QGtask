#include<stdio.h>
#include<stdlib.h>

//首次编译运行需要在命令窗等待五秒左右

typedef struct LNode                            //带头结点链表定义
{
    int data;                                    //data数据域
    struct LNode * next;                         //next指针域
}
LNode,*LinkList;                                 //为结构体定义别名LNode和LinkList


bool List_Init (LinkList &pHead)                 //初始化链表
{
    pHead = (LNode *) malloc(sizeof(LNode));     //为头结点分配内存并将地址存储在pHead中
    if (pHead == NULL)
    {
        return false;
    }                                            //检查内存分配是否成功（若成功则pHead不为NULL）
    pHead->next = NULL;                          //初始化头结点的'next'指针为NULL，因为它是目前链表中唯一的节点
    return true;
}


bool List_Empty (LinkList pHead)                 //判断链表是否为空的（LinkList先前typedef定义过，且pHead为指向头节点的指针
{                                                //bool返回true表示链表为空，返回false表示链表不为空
    return pHead->next == NULL;                  // 检查头结点的'next'指针是否为NULL。
}


// 栈的入栈操作push
bool Stack_Push(LinkList &pHead, int e)
{
    LNode *pTemp = (LNode *)malloc(sizeof(LNode));   //为临时节点分配内存并创建新节点
    if (pTemp == NULL)
    {
        return false;
    }
    pTemp->data = e;
    pTemp->next = pHead->next;                      //新节点的指针指向当前头节点的下一个节点
    pHead->next = pTemp;                            //头指针指向新节点，使其成为新的头节点
    return true;
}


// 栈的出栈操作pop
bool Stack_Pop(LinkList &pHead, int &e)
{
    if (List_Empty(pHead))
    {
        return false;                               // 栈为空，无法出栈
    }
    LNode *pTemp = pHead->next;                     // pTemp指向栈顶元素
    e = pTemp->data;                               // 获取栈顶元素的值
    pHead->next = pTemp->next;                     // 更新头节点的指针
    free(pTemp);                                   // 释放栈顶元素的内存
    return true;
}


// 获取栈顶元素top
bool Stack_Peek(LinkList pHead, int &e)
{
    if (List_Empty(pHead))
    {
        return false;                               // 栈为空，无法获取栈顶元素
    }
    e = pHead->next->data;                         // 获取栈顶元素的值
    return true;
}


// 判断栈是否已满（在动态分配内存的情况下，通常认为栈不会满，除非内存耗尽）
bool Stack_IsFull(LinkList pHead)
{
    // 在动态分配内存的情况下，通常认为栈不会满，除非内存耗尽
    // 这里简单返回false，表示栈永远不会满
    return false;
}


void List_Show (LinkList pHead)                    //打印链表所有值
{
    LNode *node = pHead->next;                     //将指针node初始化为头结点的下一个节点，即链表的第一个有效数据节点。
    printf("\n栈内元素：");
    while (node != NULL)                           //当node不为NULL时，说明还没有遍历到链表的末尾。
    {
        printf("%d、", node->data);
        node = node->next;                         //将node移动到下一个节点
    }
    printf("\n");
}


int main()
{
    LinkList pHead;
    List_Init(pHead);                              // 初始化链表
    printf("栈初始化完成。\n");

    int choice, value, e;
    bool continueOperation = true;

    while (continueOperation) {
        printf("\n请选择要执行的操作：\n");        // 提示用户选择操作
        printf("1. 入栈\n");                       // 入栈操作选项
        printf("2. 出栈\n");                       // 出栈操作选项
        printf("3. 查看栈顶元素\n");              // 查看栈顶元素选项
        printf("4. 查看栈内所有元素\n");         // 查看栈内所有元素选项
        printf("5. 退出\n");                       // 退出程序选项
        printf("请输入你的选择：");                // 提示用户输入选择
        if (scanf("%d", &choice) != 1) {          // 检查输入是否为整数
            printf("输入错误，请重新输入。\n");    // 提示输入错误
            while (getchar() != '\n');            // 清空输入缓冲区
            continue;                             // 跳过当前循环的剩余部分，重新开始循环
        }

        switch (choice) {
            case 1:
            {                                       // 入栈操作
                printf("请输入要入栈的值：");       // 提示用户输入要入栈的值
                if (scanf("%d", &value) != 1) 
                {                                   // 检查输入是否为整数
                    printf("输入错误，请重新输入。\n");// 提示输入错误
                    while (getchar() != '\n');     // 清空输入缓冲区
                    break;                         // 跳出switch语句
                }
                if (Stack_Push(pHead, value)) 
                {                                   // 尝试将值压入栈
                    printf("入栈成功\n");          // 提示入栈成功
                }
                else 
                {
                    printf("入栈失败\n");          // 提示入栈失败
                }
                break;                             // 跳出switch语句
            }
            case 2:
            {                                       // 出栈操作
                if (Stack_Pop(pHead, e)) 
                {                                   // 尝试从栈中弹出一个元素
                    printf("出栈成功，出栈的元素是：%d\n", e); // 提示出栈成功及出栈的元素
                }
                else 
                {
                    printf("出栈失败，栈为空\n");  // 提示出栈失败，栈为空
                }
                break;                             // 跳出switch语句
            }
            case 3:
            {                                       // 查看栈顶元素
                if (Stack_Peek(pHead, e)) 
                {                                   // 尝试查看栈顶元素
                    printf("栈顶元素是：%d\n", e); // 提示栈顶元素
                }
                else 
                {
                    printf("栈为空，没有栈顶元素\n"); // 提示栈为空
                }
                break;                             // 跳出switch语句
            }
            case 4:
            {                                       // 查看栈内所有元素
                List_Show(pHead);                   // 打印栈内所有元素
                break;                             // 跳出switch语句
            }
            case 5:
            {                                       // 退出
                printf("程序退出\n");              // 提示程序退出
                return 0;                           // 返回0，正常退出程序
            }
            default:
                printf("输入错误，请重新输入。\n"); // 提示输入错误
        }

        // 询问用户是否继续操作
        if (choice != 5) { // 如果不是退出操作，询问是否继续
            printf("是否继续操作？(y/Y继续，其他键退出): ");
            char continueChar;
            scanf(" %c", &continueChar); // 读取用户输入
            continueOperation = (continueChar == 'y' || continueChar == 'Y');
            if (!continueOperation) {
                printf("程序退出\n");
            }
        }
    }

    return 0;
}