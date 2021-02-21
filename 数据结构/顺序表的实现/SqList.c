#include "SqList.h"

static void AppendSpace(SqList* sq) {
	ElemType* tmp = (ElemType*)malloc(sizeof(ElemType) * sq->space_size * 2);
	if (tmp == NULL)
		return;
	for (int i = 0; i < sq->elem_num; ++i) {
		tmp[i] = sq->elem[i];
	}
	free(sq->elem);
	sq->elem = tmp;
	sq->space_size *= 2;
}

// 1.初始化
void init_list(SqList* sq, int size) {
	// 判断传入参数是否合法
	if (sq == NULL || size <= 0)
		return;
	// 在堆区申请一段动态空间
	sq->elem = (ElemType*)malloc( size * sizeof(ElemType));
	if (sq->elem == NULL)
		return;
	// 申请成功,设置成员变量
	sq->elem_num = 0;
	sq->space_size = size;
	return;
}
// 2.插入
void insert_list(SqList* sq, ElemType val, int pos) {
	// 传入参数合法性判断
	if (sq == NULL || pos < 0 || pos > sq->space_size)
		return;
	// 若空间已满则需要扩容
	if (sq->elem_num == sq->space_size)
		AppendSpace(sq);
	// 插入操作 
	for (int i = sq->elem_num; i > pos; --i) {
		sq->elem[i] = sq->elem[i - 1];
	}
	
	sq->elem[pos] = val;
	++sq->elem_num;
}
// 3.删除:根据pos进行删除
void delete_list(SqList* sq, int pos) {
	// 传入参数合法性判断
	if (sq == NULL || pos < 0 || pos > sq->space_size)
		return;
	// 将pos后的元素前移一位
	for (int i = pos; i < sq->elem_num - 1; ++i) {
		sq->elem[i] = sq->elem[i + 1];
	}
	--sq->elem_num;
}
// 4.查询
void find(SqList* sq, int pos) {
	printf("pos:%d-%d\n", pos, sq->elem[pos]);
}
// 5.销毁
void destory(SqList* sq);