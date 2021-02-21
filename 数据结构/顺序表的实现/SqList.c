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

// 1.��ʼ��
void init_list(SqList* sq, int size) {
	// �жϴ�������Ƿ�Ϸ�
	if (sq == NULL || size <= 0)
		return;
	// �ڶ�������һ�ζ�̬�ռ�
	sq->elem = (ElemType*)malloc( size * sizeof(ElemType));
	if (sq->elem == NULL)
		return;
	// ����ɹ�,���ó�Ա����
	sq->elem_num = 0;
	sq->space_size = size;
	return;
}
// 2.����
void insert_list(SqList* sq, ElemType val, int pos) {
	// ��������Ϸ����ж�
	if (sq == NULL || pos < 0 || pos > sq->space_size)
		return;
	// ���ռ���������Ҫ����
	if (sq->elem_num == sq->space_size)
		AppendSpace(sq);
	// ������� 
	for (int i = sq->elem_num; i > pos; --i) {
		sq->elem[i] = sq->elem[i - 1];
	}
	
	sq->elem[pos] = val;
	++sq->elem_num;
}
// 3.ɾ��:����pos����ɾ��
void delete_list(SqList* sq, int pos) {
	// ��������Ϸ����ж�
	if (sq == NULL || pos < 0 || pos > sq->space_size)
		return;
	// ��pos���Ԫ��ǰ��һλ
	for (int i = pos; i < sq->elem_num - 1; ++i) {
		sq->elem[i] = sq->elem[i + 1];
	}
	--sq->elem_num;
}
// 4.��ѯ
void find(SqList* sq, int pos) {
	printf("pos:%d-%d\n", pos, sq->elem[pos]);
}
// 5.����
void destory(SqList* sq);