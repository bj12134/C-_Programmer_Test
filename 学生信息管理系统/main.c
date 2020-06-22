#include "stu_inf.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void menu();
void keyDown();

int main() {
	list = createList();
	readInfoFromFile(list, "student.txt");
	while (1) {
		menu();
		keyDown();
		system("pause");
		system("cls");
	}
	//struct Node* list = createList();
	//insertNode(list, 1);
	//insertNode(list, 2);
	//insertNode(list, 3);
	//insertNode(list, 4);
	//insertNode(list, 5);
	//printList(list);
	//findNode(list, 3);
	//deleteNode(list, 3);
	//findNode(list, 3);
	//printList(list);
	return 0;
}