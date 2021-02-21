#pragma once

#include <stdio.h>
#include <stdlib.h>



typedef int ElemType;

typedef struct SqList {
    ElemType* elem;
    int space_size;
    int elem_num;
}SqList;

// 1.��ʼ��
void init_list(SqList* sq, int size);
// 2.����
void insert_list(SqList* sq, ElemType val, int pos);
// 3.ɾ��:����pos����ɾ��
void delete_list(SqList* sq, int pos);
// 4.��ѯ
void find(SqList* sq, int pos);
// 5.����
void destory(SqList* sq);