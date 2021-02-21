#pragma once

#include <stdio.h>
#include <stdlib.h>



typedef int ElemType;

typedef struct SqList {
    ElemType* elem;
    int space_size;
    int elem_num;
}SqList;

// 1.初始化
void init_list(SqList* sq, int size);
// 2.插入
void insert_list(SqList* sq, ElemType val, int pos);
// 3.删除:根据pos进行删除
void delete_list(SqList* sq, int pos);
// 4.查询
void find(SqList* sq, int pos);
// 5.销毁
void destory(SqList* sq);