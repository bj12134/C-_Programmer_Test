#pragma once

struct studentInf {
	char _name[32];
	int _age;
	char _sex[4];
	char _num[32];
	//char _major[32];
}stu_inf;



struct Node {
	//int data;
	struct studentInf data;
	struct Node* next;
};

struct Node* list;

// ********** 创建链表 **********
struct Node* createList();
// ********** 创建结点 **********
struct Node* createNode(struct studentInf data);
// ********** 插入操作 **********
void insertNode(struct Node* head, struct studentInf data);
// ********** 删除操作 **********
void deleteNode(struct Node* head, char* data);
// ********** 修改操作 **********
void modefyNode(struct Node* head, char* name);
// ********** 查找操作 **********
struct Node* findNode(struct Node* head, char* name);
// ********** 打印操作 **********
void printList(struct Node* hd);
// ********** 文件读操作 **********
void readInfoFromFile(struct Node* head, char* fileName);
// ********** 文件写操作 **********
void writeInfoFromFile(struct Node* head, char* fileName);