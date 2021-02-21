#include "SqList.h"


void test_sqlist() {
	SqList sq;
	init_list(&sq, 10);
	for(int i = 0; i < 10; ++i){
		insert_list(&sq, i, i);
	}
	find(&sq, 2);
	delete_list(&sq, 2);
	find(&sq, 2);
	system("pause");
}

int main() {
	test_sqlist();
	return 0;
}