#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    union {
        int num;	// 头节点记录插入元素的数量
        ElemType data; // 数据域
    };
    struct Node* next; // 指针域
}Node, List;

// 1.链表的初始化
void init_List(Node* node);
// 2.链表的插入
void insert_List(Node* node, ElemType val, int pos);
// 3.链表的删除
void delete_List(Node* node, int pos);
// 4.链表的查找
Node* find_List(Node* node, int pos);
// 5.链表的销毁
void destory(Node* node);

// **************

// 头插头删
void push_front(Node* node, ElemType val);
void pop_front(Node* node);
// 头删尾删
void push_back(Node* node, ElemType val);
void pop_back(Node* node);