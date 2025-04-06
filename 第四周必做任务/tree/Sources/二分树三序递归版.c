#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//	运行时仍需等待一段时间
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

// 前序遍历
void Preorder(BstNode *root) 
{
    // 递归的基准条件
    // 如果树或子树为空，返回并退出
    if (root == NULL)
        return;
    printf("%d ", root->data); // 打印数据
    Preorder(root->left);      // 访问左子树
    Preorder(root->right);     // 访问右子树
}

// 中序遍历
void Inorder(BstNode *root) 
{
    if (root == NULL)
        return;
    Inorder(root->left);       // 访问左子树
    printf("%d ", root->data); // 打印数据
    Inorder(root->right);      // 访问右子树
}

// 后序遍历
void Postorder(BstNode *root) 
{
    if (root == NULL)
        return;
    Postorder(root->left);     // 访问左子树
    Postorder(root->right);    // 访问右子树
    printf("%d ", root->data); // 打印数据
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

//	main函数的菜单栏交互和鲁棒性与第一周链表相同
//	因此此处不做过多注释
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
            while (getchar() != '\n');
            continue;
        }

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
            continueOperation = (continueChar == 'y' || continueChar == 'Y');
            if (!continueOperation) 
			{
                printf("程序退出\n");
            }
        }
    }

    return 0;
}