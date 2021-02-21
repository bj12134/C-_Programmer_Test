#include "list.h"

void test() {
	Node node;
	Node* ptr = &node;
	Node* tmp = ptr;
	init_List(tmp);
	// Õ∑≤Â∑®≤‚ ‘
	// push_back pop_back push_front pop_front
	//push_front(tmp, 1);
	//push_front(tmp, 2);
	//push_front(tmp, 3);
	//// Õ∑…æ≤‚ ‘
	//pop_front(tmp);
	//pop_front(tmp);
	//pop_front(tmp);
	// Œ≤≤Â∑®≤‚ ‘
	push_back(tmp, 1);
	push_back(tmp, 2);
	push_back(tmp, 3);
	pop_back(tmp);
	for (int i = 0; i < node.num; ++i) {
		tmp = tmp->next;
		printf("%d->", tmp->data);
	}
	//for (int i = 1; i <= 10; ++i) {
	//	insert_List(tmp, i, i);
	//}
	//printf("node->num:[%d]\n", tmp->num);
	//for (int i = 0; i < node.num; ++i) {
	//	tmp = tmp->next;
	//	printf("%d->", tmp->data);
	//}
	//printf("NULL\n");
	//tmp = ptr;
	//delete_List(tmp, 3);
	//for (int i = 0; i < node.num; ++i) {
	//	tmp = tmp->next;
	//	printf("%d->", tmp->data);
	//}
	//printf("NULL\n");
}


int main() {
	test();
	return 0;
}