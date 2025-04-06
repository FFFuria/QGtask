#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//	运行时仍需等待一段时间
//	三序非递归版执行完三序遍历后无法回到菜单栏，只能直接退出程序
//	采用清空缓存区也无法解决此bug，请见谅
// 定义二叉树节点
typedef struct BstNode 
{
    int data;
    struct BstNode* left;
    struct BstNode* right;
} BstNode;

//	寻找最小值
BstNode* FindMin(BstNode* root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

//	删除函数
BstNode* Delete(BstNode* root, int data) 
{
    if (root == NULL)
        return root; 
    else if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    //	找到了，准备删除！
    else 
    {
        // 没有孩子
        if (root->left == NULL && root->right == NULL) 
        { 
            free(root);
            root = NULL;
        }
        //	独生孩子
        else if (root->left == NULL) 
        {
            BstNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) 
        {
            BstNode* temp = root;
            root = root->left;
            free(temp);
        }
        //	双胞胎
        else 
        { 
            BstNode* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

// 前序遍历（非递归）
void Preorder(BstNode *root) 
{
    if (root == NULL)
        return;

    // 使用栈来模拟递归过程
    struct StackNode 
    {
        BstNode* node;
        struct StackNode* next;
    };
    typedef struct StackNode StackNode;

    StackNode* CreateStack() 
    {
        StackNode* stack = (StackNode*)malloc(sizeof(StackNode));
        stack->node = NULL;
        stack->next = NULL;
        return stack;
    }

    void Push(StackNode** stack, BstNode* node) 
    {
        StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
        temp->node = node;
        temp->next = *stack;
        *stack = temp;
    }

    BstNode* Pop(StackNode** stack) 
    {
        if (*stack == NULL)
            return NULL;
        StackNode* temp = *stack;
        BstNode* node = temp->node;
        *stack = temp->next;
        free(temp);
        return node;
    }

    StackNode* stack = CreateStack();
    Push(&stack, root);

    while (stack != NULL) 
    {
        BstNode* current = Pop(&stack);
        printf("%d ", current->data);

        if (current->right != NULL)
            Push(&stack, current->right);
        if (current->left != NULL)
            Push(&stack, current->left);
    }
}

// 中序遍历（非递归）
void Inorder(BstNode *root) 
{
    if (root == NULL)
        return;

    struct StackNode 
    {
        BstNode* node;
        struct StackNode* next;
    };
    typedef struct StackNode StackNode;

    StackNode* CreateStack() 
    {
        StackNode* stack = (StackNode*)malloc(sizeof(StackNode));
        stack->node = NULL;
        stack->next = NULL;
        return stack;
    }

    void Push(StackNode** stack, BstNode* node) 
    {
        StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
        temp->node = node;
        temp->next = *stack;
        *stack = temp;
    }

    BstNode* Pop(StackNode** stack) 
    {
        if (*stack == NULL)
            return NULL;
        StackNode* temp = *stack;
        BstNode* node = temp->node;
        *stack = temp->next;
        free(temp);
        return node;
    }

    StackNode* stack = CreateStack();
    BstNode* current = root;

    while (current != NULL || stack != NULL) 
    {
        while (current != NULL) 
        {
            Push(&stack, current);
            current = current->left;
        }

        current = Pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// 后序遍历（非递归）
void Postorder(BstNode *root) 
{
    if (root == NULL)
        return;

    struct StackNode 
    {
        BstNode* node;
        bool visited;
        struct StackNode* next;
    };
    typedef struct StackNode StackNode;

    StackNode* CreateStack() 
    {
        StackNode* stack = (StackNode*)malloc(sizeof(StackNode));
        stack->node = NULL;
        stack->next = NULL;
        return stack;
    }

    void Push(StackNode** stack, BstNode* node, bool visited) 
    {
        StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
        temp->node = node;
        temp->visited = visited;
        temp->next = *stack;
        *stack = temp;
    }

    BstNode* Pop(StackNode** stack) 
    {
        if (*stack == NULL)
            return NULL;
        StackNode* temp = *stack;
        BstNode* node = temp->node;
        *stack = temp->next;
        free(temp);
        return node;
    }

    StackNode* stack = CreateStack();
    Push(&stack, root, false);

    while (stack != NULL) 
    {
        StackNode* top = stack;
        BstNode* current = top->node;
        bool isVisited = top->visited;

        if (!isVisited) 
        {
            Pop(&stack);
            Push(&stack, current, true);
            if (current->right != NULL)
                Push(&stack, current->right, false);
            if (current->left != NULL)
                Push(&stack, current->left, false);
        } 
        else 
        {
            Pop(&stack);
            printf("%d ", current->data);
        }
    }
}

// 定义队列节点
typedef struct QueueNode 
{
    BstNode* data;
    struct QueueNode* next;
} QueueNode;

// 定义队列
typedef struct Queue 
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 创建队列
Queue* CreateQueue() 
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// 判断队列是否为空
bool IsEmpty(Queue* q) 
{
    return q->front == NULL;
}

// 入队
void EnQueue(Queue* q, BstNode* node) 
{
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = node;
    temp->next = NULL;

    if (q->rear == NULL) 
    {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// 出队
BstNode* DeQueue(Queue* q) 
{
    if (IsEmpty(q)) 
    {
        return NULL;
    }
    QueueNode* temp = q->front;
    BstNode* node = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) 
    {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

// 层序遍历
void LevelOrder(BstNode* root) 
{
    if (root == NULL)
        return;

    Queue* q = CreateQueue();
    EnQueue(q, root);

    while (!IsEmpty(q)) 
    {
        BstNode* current = DeQueue(q);
        printf("%d ", current->data);

        if (current->left != NULL) 
        {
            EnQueue(q, current->left);
        }
        if (current->right != NULL) 
        {
            EnQueue(q, current->right);
        }
    }
    // 释放队列内存
    free(q);
}

// 查找函数
bool Search(BstNode* root, int data) 
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data <= root->data)
        return Search(root->left, data);
    else
        return Search(root->right, data);
}

// 创建新节点
BstNode* GetNewNode(int data) 
{
    BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 插入函数
BstNode* Insert(BstNode* root, int data) 
{
    // 空树的情况
    if (root == NULL) 
    {
        root = GetNewNode(data);
    }
    // 非空树的情况
    // 插入到左子树
    else if (data <= root->data) 
    {
        root->left = Insert(root->left, data);
    }
    // 插入到右子树
    else 
    {
        root->right = Insert(root->right, data);
    }
    return root;
}

// 主函数的菜单栏交互和鲁棒性与链表相同
// 因此此处不做过多注释
int main()
{
    BstNode* root = NULL;  // 创建树
    bool continueOperation = true;

    while (continueOperation) 
    {
        printf("\n请选择要执行的操作：\n");
        printf("1. 插入节点\n");
        printf("2. 删除节点\n");
        printf("3. 查找节点\n");
        printf("4. 前序遍历\n");
        printf("5. 中序遍历\n");
        printf("6. 后序遍历\n");
        printf("7. 层序遍历\n");
        printf("8. 退出\n");
        printf("请输入你的选择：");

        int choice;
        if (scanf("%d", &choice) != 1) 
        {
            printf("输入错误，请重新输入。\n");
            while (getchar() != '\n'); // 清除错误输入
            continue;
        }
        while (getchar() != '\n'); // 清除输入行的剩余字符

        int value;
        switch (choice) 
        {
            case 1:
                printf("请输入要插入的值：");
                if (scanf("%d", &value) != 1) 
                {
                    printf("输入错误，请重新输入。\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); // 清除剩余字符
                root = Insert(root, value);
                printf("插入成功\n");
                break;
            case 2:
                printf("请输入要删除的值：");
                if (scanf("%d", &value) != 1) 
                {
                    printf("输入错误，请重新输入。\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); // 清除剩余字符
                root = Delete(root, value);
                printf("删除成功\n");
                break;
            case 3:
                printf("请输入要查找的值：");
                if (scanf("%d", &value) != 1) 
                {
                    printf("输入错误，请重新输入。\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); // 清除剩余字符
                if (Search(root, value))
                    printf("找到\n");
                else
                    printf("未找到\n");
                break;
            case 4:
                printf("前序遍历结果: ");
                Preorder(root);
                printf("\n");
                break;
            case 5:
                printf("中序遍历结果: ");
                Inorder(root);
                printf("\n");
                break;
            case 6:
                printf("后序遍历结果: ");
                Postorder(root);
                printf("\n");
                break;
            case 7:
                printf("层序遍历结果: ");
                LevelOrder(root);
                printf("\n");
                break;
            case 8:
                printf("程序退出\n");
                return 0;
            default:
                printf("输入错误，请重新输入。\n");
        }

        if (choice != 8) 
        {
            printf("是否继续操作？(y/Y继续，其他键退出): ");
            char continueChar;
            scanf(" %c", &continueChar);
            while (getchar() != '\n'); // 清除输入行的剩余字符
            continueOperation = (continueChar == 'y' || continueChar == 'Y');
            if (!continueOperation) 
            {
                printf("程序退出\n");
            }
        }
    }

    return 0;
}