#include "stu_inf.h"
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>


// ********** 创建链表 **********
struct Node* createList() {
	// 结构体变量表示表头
	// 指针-->变量:动态内存申请
	// 表头:做差异化处理,数据域data不做处理
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->next = NULL;
	return head;
}

// ********** 创建结点 **********
struct Node* createNode(struct studentInf data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// ********** 插入操作 **********
void insertNode(struct Node* head, struct studentInf data) {
	struct Node* newNode = createNode(data);
	newNode->next = head->next;
	head->next = newNode;
}

// ********** 删除操作 **********
void deleteNode(struct Node* head, char* name) {
	if (head == NULL) {
		printf("链表为空,删除失败!\n");
		return;
	}

	struct Node* posFrontNode = head;
	struct Node* posNode = head->next;

	while (strcmp(posNode->data._name, name)) {
		posFrontNode = posNode;
		posNode = posNode->next;
		if (posNode == NULL) {
			printf("未找到指定数据,删除失败!\n");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
}
// ********** 修改操作 **********
void modefyNode(struct Node* head, char* num) {
	if (head == NULL) {
		printf("链表为空,修改失败\n");
		return;
	}
	// 通过name先进行查找,找到name所在的结点
	// 重新修改学生的信息并进行保存
	struct Node* phead = head->next;
	while (phead) {
		if (strcmp(phead->data.num, num)) {
			printf("重新输入该学生的信息\n");
			printf("输入学生的姓名,年龄,性别:");
			fflush(stdin);
			scanf("%s %d %s", phead->data._name, phead->data._age, phead->data._sex);
			return;
		}
		phead = phead->next;
	}
	printf("未有该学生的信息,修改失败!\n");
}
// ********** 查找操作 **********
struct Node* findNode(struct Node* head, char* name) {
	if (head == NULL) {
		printf("链表为空,删除失败!\n");
		return NULL;
	}
	struct Node* posNode = head->next;

	while (strcmp(posNode->data._name, name)) {
		posNode = posNode->next;
		if (posNode == NULL) {
			printf("未找到指定数据!\n");
			return NULL;
		}
	}
	printf("查找成功\n");
	return posNode;
}
// ********** 打印操作 **********
void printList(struct Node* head) {
	struct Node* phead = head->next;
	printf("姓名\t年龄\t性别\t学号\n");
	while (phead) {
		printf("%s\t%d\t%s\t%s\n", phead->data._name, phead->data._age, phead->data._sex, phead->data._num);
		phead = phead->next;
	}
}

void readInfoFromFile(struct Node* head, char* fileName) {
	// 1.打开文件
	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fopen(fileName, "w+");
	}
	// 2.读取文件
	struct studentInf stu;
	while (fscanf(fp, "%s\t%d\t%s\t%s\n", stu._name, &stu._age, stu._sex, stu._num) != EOF) {
		insertNode(head, stu);
	}
	// 3.关闭文件
	fclose(fp);
}

void writeInfoFromFile(struct Node* head, char* fileName) {
	FILE* fp;
	fp = fopen(fileName, "w");
	struct Node* phead = head->next;
	while (phead) {
		fprintf(fp, "%s\t%d\t%s\t%s\n", phead->data._name, phead->data._age, phead->data._sex, phead->data._num);
		phead = phead->next;
	}
	fclose(fp);
}