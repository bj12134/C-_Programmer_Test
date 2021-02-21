#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    union {
        int num;	// ͷ�ڵ��¼����Ԫ�ص�����
        ElemType data; // ������
    };
    struct Node* next; // ָ����
}Node, List;

// 1.����ĳ�ʼ��
void init_List(Node* node);
// 2.����Ĳ���
void insert_List(Node* node, ElemType val, int pos);
// 3.�����ɾ��
void delete_List(Node* node, int pos);
// 4.����Ĳ���
Node* find_List(Node* node, int pos);
// 5.���������
void destory(Node* node);

// **************

// ͷ��ͷɾ
void push_front(Node* node, ElemType val);
void pop_front(Node* node);
// ͷɾβɾ
void push_back(Node* node, ElemType val);
void pop_back(Node* node);