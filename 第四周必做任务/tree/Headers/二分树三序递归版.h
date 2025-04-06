#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 *  @name        : struct BstNode
 *  @description : 二叉树节点结构体
 */
typedef struct BstNode 
{
    int data;
    struct BstNode* left;
    struct BstNode* right;
} BstNode;

/**
 *  @name        : BstNode* FindMin(BstNode* root)
 *  @description : 查找二叉树中的最小值节点
 *  @param       : 根节点指针 root
 *  @return      : 最小值节点指针
 */
BstNode* FindMin(BstNode* root);

/**
 *  @name        : BstNode* Delete(BstNode* root, int data)
 *  @description : 从二叉树中删除指定值的节点
 *  @param       : 根节点指针 root, 要删除的值 data
 *  @return      : 删除后的根节点指针
 */
BstNode* Delete(BstNode* root, int data);

/**
 *  @name        : void Preorder(BstNode* root)
 *  @description : 前序遍历二叉树
 *  @param       : 根节点指针 root
 */
void Preorder(BstNode* root);

/**
 *  @name        : void Inorder(BstNode* root)
 *  @description : 中序遍历二叉树
 *  @param       : 根节点指针 root
 */
void Inorder(BstNode* root);

/**
 *  @name        : void Postorder(BstNode* root)
 *  @description : 后序遍历二叉树
 *  @param       : 根节点指针 root
 */
void Postorder(BstNode* root);

/**
 *  @name        : struct QueueNode
 *  @description : 队列节点结构体
 */
typedef struct QueueNode 
{
    BstNode* data;
    struct QueueNode* next;
} QueueNode;

/**
 *  @name        : struct Queue
 *  @description : 队列结构体
 */
typedef struct Queue 
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

/**
 *  @name        : Queue* CreateQueue()
 *  @description : 创建一个新队列
 *  @return      : 队列指针
 */
Queue* CreateQueue();

/**
 *  @name        : bool IsEmpty(Queue* q)
 *  @description : 判断队列是否为空
 *  @param       : 队列指针 q
 *  @return      : 队列为空返回 true，否则返回 false
 */
bool IsEmpty(Queue* q);

/**
 *  @name        : void EnQueue(Queue* q, BstNode* node)
 *  @description : 将节点入队
 *  @param       : 队列指针 q, 节点指针 node
 */
void EnQueue(Queue* q, BstNode* node);

/**
 *  @name        : BstNode* DeQueue(Queue* q)
 *  @description : 从队列中出队一个节点
 *  @param       : 队列指针 q
 *  @return      : 出队的节点指针
 */
BstNode* DeQueue(Queue* q);

/**
 *  @name        : void LevelOrder(BstNode* root)
 *  @description : 层序遍历二叉树
 *  @param       : 根节点指针 root
 */
void LevelOrder(BstNode* root);

/**
 *  @name        : bool Search(BstNode* root, int data)
 *  @description : 在二叉树中查找指定值
 *  @param       : 根节点指针 root, 要查找的值 data
 *  @return      : 找到返回 true，否则返回 false
 */
bool Search(BstNode* root, int data);

/**
 *  @name        : BstNode* GetNewNode(int data)
 *  @description : 创建一个新的二叉树节点
 *  @param       : 节点值 data
 *  @return      : 新节点指针
 */
BstNode* GetNewNode(int data);

/**
 *  @name        : BstNode* Insert(BstNode* root, int data)
 *  @description : 向二叉树中插入一个新节点
 *  @param       : 根节点指针 root, 要插入的值 data
 *  @return      : 插入后的根节点指针
 */
BstNode* Insert(BstNode* root, int data);

#endif // BST_H_INCLUDED