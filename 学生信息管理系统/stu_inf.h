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

// ********** �������� **********
struct Node* createList();
// ********** ������� **********
struct Node* createNode(struct studentInf data);
// ********** ������� **********
void insertNode(struct Node* head, struct studentInf data);
// ********** ɾ������ **********
void deleteNode(struct Node* head, char* data);
// ********** �޸Ĳ��� **********
void modefyNode(struct Node* head, char* name);
// ********** ���Ҳ��� **********
struct Node* findNode(struct Node* head, char* name);
// ********** ��ӡ���� **********
void printList(struct Node* hd);
// ********** �ļ������� **********
void readInfoFromFile(struct Node* head, char* fileName);
// ********** �ļ�д���� **********
void writeInfoFromFile(struct Node* head, char* fileName);