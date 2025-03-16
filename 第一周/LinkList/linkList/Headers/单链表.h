#include<stdio.h>
#include<stdlib.h>

//首次编译运行需要在命令窗等待五秒左右

typedef struct LNode							//带头结点链表定义
{
	int data;									//data数据域
	struct LNode * next;						//next指针域
}
LNode,*LinkList;								//为结构体定义别名LNode和LinkList


bool List_Init (LinkList &pHead) 				//初始化链表
{
	pHead = (LNode *) malloc(sizeof(LNode)); 	//为头结点分配内存并将地址存储在pHead中
	if (pHead == NULL) 
	{
		return false; 
	}											//检查内存分配是否成功（若成功则pHead不为NULL）
	pHead->next = NULL; 						//初始化头结点的'next'指针为NULL，因为它是目前链表中唯一的节点
	return true;
}


int List_Length (LinkList pHead)
 {
  	int count = 0; 											//用于计数有效节点的计数器，初始化为0
 	for (LNode *p = pHead->next; p != NULL; p = p->next) 	//for循环遍历链表，每一次循环结束后可移动指针p执行后一位的移动
  	{														//有效节点为头结点的下一个结点不为空即存在结点时
		count++;
	}	 													//每经过一个节点，有效节点数量加1
  	return count;											//返回计数器
}


bool List_Empty (LinkList pHead) 				//判断链表是否为空的（LinkList先前typedef定义过，且pHead为指向头节点的指针
{												//bool返回true表示链表为空，返回false表示链表不为空
  	return pHead->next == NULL; 				// 检查头结点的'next'指针是否为NULL。
}


LinkList List_Create(LinkList &pHead)                     //头插法创建链表
{
    LNode *pTemp; int x, choice;                     // 定义临时节点指针、输入数据和菜单选项
    do 
    {
        printf("1. 继续输入\n");                     //提供路径选择
        printf("2. 结束输入\n");
        printf("请输入你的选择：");
        scanf("%d", &choice);
        if (choice == 1) 
        {
            printf("请输入数据：");
            scanf("%d", &x);
            pTemp = (LNode *)malloc(sizeof(LNode));   //为临时节点分配内存并创建新节点
            pTemp->data = x;
            pTemp->next = pHead->next;                //新节点的指针指向当前头节点的下一个节点
            pHead->next = pTemp;                      //头指针指向新节点，使其成为新的头节点
        }
        else if (choice != 2) // 处理无效输入
        {
            printf("无效输入，请重新输入！\n");
        }
    } while (choice != 2);
    return pHead;                                     //返回带头结点的链表的头指针
}


LinkList List_Create_Tail_Insert(LinkList &pHead)       //尾插法创建链表
{
    LNode *pTemp;                                     //定义临时节点指针
    LNode *pTail = pHead;                             //尾节点指针，初始指向头结点
    int x;                                            //用于存储输入的数据
    int choice;                                       //菜单选项变量

    do
    {                                                 //菜单选择
        printf("1. 继续输入\n");
        printf("2. 结束输入\n");
        printf("请输入你的选择：");
        scanf("%d", &choice);

        if (choice == 1) 
        {
            printf("请输入数据：");
            scanf("%d", &x);

            pTemp = (LNode *)malloc(sizeof(LNode));   //分配内存并创建新节点
            pTemp->data = x;                          //尾节点的下一个指针指向新节点
            pTail->next = pTemp;                      //更新尾节点指针，使其指向新节点
            pTail = pTemp;                            //读取下一个数据
        }
        else if (choice != 2) // 处理无效输入
        {
            printf("无效输入，请重新输入！\n");
        }
    } while (choice != 2);

    pTail->next = NULL;                               //尾节点的下一个指针置为 NULL，表示链表结束
    return pHead;                                     //返回带头结点的链表头指针
}


LNode* List_Get_All_Elems(LinkList pHead, int e, int &count, int **positions)  // 按值获取所有结点和其位序
{
    count = 0;
    *positions = NULL; 				// 初始化positions为NULL
    LNode *p = pHead->next; 		// p指向第一个数据节点
    int i = 1; 						// 用于记录当前节点的位序

    while (p != NULL) 				// 遍历链表直到末尾
    {
        if (p->data == e) 			// 如果当前节点的数据等于目标值
        {
            // 动态分配内存以存储新的位序
            int *temp = (int *)realloc(*positions, count * sizeof(int));
            if (temp == NULL) 		// 检查内存分配是否成功
            {
                free(*positions); 	// 释放已分配的内存
                *positions = NULL;
                return NULL; 		// 返回NULL表示分配失败
            }
            *positions = temp;
            (*positions)[count] = i; // 记录当前匹配节点的位序
            count++; 				// 增加匹配计数
        }
        p = p->next; 				// 移动到下一个节点
        i++; 						// 更新位序
    }

    if (count > 0) 					// 如果找到了匹配的节点
    {
        return pHead->next; 		// 返回头结点的下一个节点（链表不为空）
    }
    else
    {
        free(*positions); 			// 释放分配的内存
        *positions = NULL;
        return NULL; 				// 没有找到匹配的节点，返回NULL
    }
}


bool List_Insert(LinkList &pHead, int i, int e) 			//按位序插入新的节点，i=1插在表头，i=length+1插在表尾
{
	if (i < 1 || i > List_Length(pHead) + 1) 
	{
		return false;										//检查插入位置是否有效
	}  
	int j = 0; 												//当前p指向的是第几个结点
	LNode *p = pHead; 										//p 指向头结点
	while (p != NULL && j < i - 1) 							//p不等于null确保不会遍历到尾部
	{ 														//循环找到要插入位置的前驱结点，直到找到前驱结点或者链表结束
		p = p->next;
		j++;
	}
	LNode *pTemp = (LNode *)malloc(sizeof(LNode));			//分配新节点并申请内存
	pTemp->data = e;
	pTemp->next = p->next; 									//将新节点的'next'指向p的下一个节点
	p->next = pTemp; 										//更新p的'next'指向新节点，完成插入操作。
	return true;
}


bool List_Del (LinkList &pHead, int i) 						//按位序删除节点，i=1删表头，i=length删头尾
{
	if (i < 1 || i > List_Length(pHead)) 
	{
		return false;										//检查删去位置是否有效
	}
	LNode *p = pHead;										//p初始化为头节点
	for (int j = 0; j < i - 1; j++)  						//找到待删除位序的前一位结点，i==1已处理，故从j=2开始
	{														//通过for循环找到第i-1个节点（即待删除节点的前驱节点
		p = p->next;
	}
	LNode *q = p->next; 									//q指向待删除结点
	p->next = q->next; 										//将p的next指针指向q的下一个节点，从而跳过q，将其从链表中移除
	free(q);												//释放即删除待删除节点的内存，避免内存泄漏
	return true;
}


void List_Show (LinkList pHead)								//打印链表所有值
{
	LNode *node = pHead->next;								//将指针node初始化为头结点的下一个节点，即链表的第一个有效数据节点。
	printf("\n链表值：");
	while (node != NULL)									//当node不为NULL时，说明还没有遍历到链表的末尾。
	{
    	printf("%d、", node->data);
    	node = node->next;									//将node移动到下一个节点
  	}
	printf("\n");
}


//选做任务
//寻找链表的中点
LNode* Find_Middle_Node(LinkList pHead)
{
    if (pHead == NULL || pHead->next == NULL)		//如果链表为空（pHead == NULL）或者链表只有一个节点（pHead->next == NULL）
    {	
        return pHead;								//直接返回 pHead，因为此时的中间节点就是头节点本身
    }
    LNode *slow = pHead->next;						//slow 和 fast 都初始化为头节点的下一个节点（即链表的第一个有效节点）
    LNode *fast = pHead->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;							//slow 指针每次移动一步
        fast = fast->next->next;					//fast 指针每次移动两步。
    }												//当循环结束时，fast 指针已经到达链表的末尾即最后一个节点
    return slow;									//此时 slow 指针正好位于链表的中间位置。
}


//反转链表
void Reverse_List(LinkList pHead)
{
    if (pHead == NULL || pHead->next == NULL)	//与上面同理的防错操作
    {
        return;
    }
    LNode *previousNode = NULL;  				// 前一个节点
    LNode *currentNode = pHead->next;  			// 当前节点
    LNode *nextNode = NULL;  					// 下一个节点

    while (currentNode != NULL)
    {
        nextNode = currentNode->next;  			// 临时保存当前节点的下一个节点
        currentNode->next = previousNode;  		// 反转当前节点的指针方向，使其指向前一个节点
        previousNode = currentNode;        		// 前移 previousNode 指针到当前节点
        currentNode = nextNode;            		// 前移 currentNode 指针到下一个节点
    }

    pHead->next = previousNode;  				// 更新头节点的 next 指针，指向新的第一个节点
}


//链表的奇偶位置调换
void Exchange_Odd_Even_Positions(LinkList pHead)
{
    if (pHead == NULL || pHead->next == NULL || pHead->next->next == NULL)
    {
        return;
    }
    LNode *current = pHead->next; 						// 当前节点，初始指向链表的第一个有效节点（奇数位置）
	LNode *prev = pHead;          						// 前一个节点，初始指向头节点
   while (current != NULL && current->next != NULL)
	{
    	LNode *nextNode = current->next; 				// 偶数位置节点
    	current->next = nextNode->next;  				// 将奇数位置节点的 next 指针指向下一个奇数位置节点
    	nextNode->next = current;        				// 将偶数位置节点的 next 指针指向当前奇数位置节点，完成交换
    	prev->next = nextNode;           				// 更新前一个节点的 next 指针，使其指向新的奇数位置节点
    	prev = current;                  				// 更新 prev 指针到当前奇数位置节点
    	current = current->next;         				// 更新 current 指针到下一个奇数位置节点
	}
}


int main()
{
    LinkList pHead;
    List_Init(pHead);                                   // 初始化链表
    printf("链表判空：%s\n", List_Empty(pHead) ? "空" : "非空");   // 判断链表是否为空并打印结果

    List_Create(pHead);                                 // 使用头插法创建链表
    List_Show(pHead);                                   // 打印链表的所有值
    printf("链表长度：%d\n\n", List_Length(pHead));     // 打印链表的长度

    int choice, position, value;
    bool continueOperation = true;

    while (continueOperation) {
        printf("\n请选择要执行的操作：\n");             // 提示用户选择操作
        printf("1. 头插\n");                            // 头插操作选项
        printf("2. 尾插\n");                            // 尾插操作选项
        printf("3. 删除\n");                            // 删除操作选项
        printf("4. 查找\n");                            // 查找操作选项
        printf("5. 寻找链表的中点\n");                  // 寻找中点操作选项
        printf("6. 反转链表\n");                        // 反转链表操作选项
        printf("7. 奇偶位置调换\n");                    // 奇偶位置调换操作选项
        printf("8. 退出\n");                            // 退出程序选项
        printf("请输入你的选择：");                     // 提示用户输入选择
        if (scanf("%d", &choice) != 1) {               // 检查输入是否为整数
            printf("输入错误，请重新输入。\n");         // 提示输入错误
            while (getchar() != '\n');                 // 清空输入缓冲区
            continue;                                  // 跳过当前循环的剩余部分，重新开始循环
        }

        switch (choice) {
            case 1: 
            {                                       // 头插操作
                printf("请输入要头插的值：");       // 提示用户输入要头插的值
                if (scanf("%d", &value) != 1) 
                {                                   // 检查输入是否为整数
                    printf("输入错误，请重新输入。\n");// 提示输入错误
                    while (getchar() != '\n');     // 清空输入缓冲区
                    break;                         // 跳出switch语句
                }
                List_Insert(pHead, 1, value);      // 在链表头部插入新值
                List_Show(pHead);                   // 打印链表的所有值
                printf("链表长度：%d\n\n", List_Length(pHead)); // 打印链表的长度
                break;                             // 跳出switch语句
            }
            case 2: 
            {                                       // 尾插操作
                printf("请输入要尾插的值：");       // 提示用户输入要尾插的值
                if (scanf("%d", &value) != 1) {    // 检查输入是否为整数
                    printf("输入错误，请重新输入。\n");// 提示输入错误
                    while (getchar() != '\n');     // 清空输入缓冲区
                    break;                         // 跳出switch语句
                }
                List_Insert(pHead, List_Length(pHead) + 1, value); // 在链表尾部插入新值
                List_Show(pHead);                   // 打印链表的所有值
                printf("链表长度：%d\n\n", List_Length(pHead)); // 打印链表的长度
                break;                              // 跳出switch语句
            }
            case 3: 
            {                                       // 删除操作
                printf("请输入要删除的位序：");     // 提示用户输入要删除的位序
                if (scanf("%d", &position) != 1) 
                {                                   // 检查输入是否为整数
                    printf("输入错误，请重新输入。\n");// 提示输入错误
                    while (getchar() != '\n');     // 清空输入缓冲区
                    break;                         // 跳出switch语句
                }
                if (List_Del(pHead, position)) 
                {                                   // 尝试删除指定位序的节点
                    printf("删除成功\n");         // 提示删除成功
                    List_Show(pHead);               // 打印链表的所有值
                    printf("链表长度：%d\n\n", List_Length(pHead)); // 打印链表的长度
                }
                else 
                {
                    printf("删除失败\n");          // 提示删除失败
                }
                break;                              // 跳出switch语句
            }
            case 4: 
            {                                       // 查找操作
                printf("请输入要查找的值："); 
                if (scanf("%d", &value) != 1) 
                {                                   // 检查输入是否为整数
                    printf("输入错误，请重新输入。\n");// 提示输入错误
                    while (getchar() != '\n');     // 清空输入缓冲区
                    break;                         // 跳出当前case
                }
                int count = 0;                      // 初始化匹配计数器
                int *positions = NULL;              // 初始化位置数组指针为NULL
                LNode *foundNode = List_Get_All_Elems(pHead, value, count, &positions); // 调用函数获取所有匹配节点
                if (foundNode != NULL) 
                {                                   // 如果找到了匹配的节点
                    printf("值为%d的结点出现的位置为：", value); // 提示匹配节点的位置
                    for (int i = 0; i < count; i++) 
                    {                               // 遍历所有匹配的位置
                        printf("%d ", positions[i]); // 打印每个匹配的位置
                    }
                    printf("\n\n");                 
                    free(positions);                // 释放动态分配的内存
                }
                else
                {                                   // 如果没有找到匹配的节点
                    printf("未找到值为%d的结点\n\n", value); // 提示未找到
                }           
                break;                              // 跳出switch语句
            }
            case 5: 
            {                                       // 寻找链表的中点
                LNode *middleNode = Find_Middle_Node(pHead); // 调用函数寻找链表的中点
                if (middleNode != NULL) 
                {
                    printf("链表的中点值为：%d\n\n", middleNode->data); // 打印中点值
                }
                else
                {
                    printf("链表为空或只有一个头结点，没有中点\n\n"); //提示链表为空或只有一个头结点
                }
                break;                              // 跳出switch语句
            }
            case 6: 
            {                                       // 反转链表
                Reverse_List(pHead);                // 调用函数反转链表
                List_Show(pHead);                   // 打印链表的所有值
                printf("链表长度：%d\n\n", List_Length(pHead)); // 打印链表的长度
                break;                              // 跳出switch语句
            }
            case 7: 
            {                                       // 奇偶位置调换
                Exchange_Odd_Even_Positions(pHead); // 调用函数进行奇偶位置调换
                List_Show(pHead);                   // 打印链表的所有值
                printf("链表长度：%d\n\n", List_Length(pHead)); // 打印链表的长度
                break;                              // 跳出switch语句
            }
            case 8: 
            {                                       // 退出
                printf("程序退出\n");              // 提示程序退出
                return 0;                           // 返回0，正常退出程序
            }
            default:
                printf("输入错误，请重新输入。\n"); // 提示输入错误
        }

        // 询问用户是否继续操作
        if (choice != 8) { // 如果不是退出操作，询问是否继续
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