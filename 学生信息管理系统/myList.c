#include "stu_inf.h"
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>


// ********** �������� **********
struct Node* createList() {
	// �ṹ�������ʾ��ͷ
	// ָ��-->����:��̬�ڴ�����
	// ��ͷ:�����컯����,������data��������
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->next = NULL;
	return head;
}

// ********** ������� **********
struct Node* createNode(struct studentInf data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// ********** ������� **********
void insertNode(struct Node* head, struct studentInf data) {
	struct Node* newNode = createNode(data);
	newNode->next = head->next;
	head->next = newNode;
}

// ********** ɾ������ **********
void deleteNode(struct Node* head, char* name) {
	if (head == NULL) {
		printf("����Ϊ��,ɾ��ʧ��!\n");
		return;
	}

	struct Node* posFrontNode = head;
	struct Node* posNode = head->next;

	while (strcmp(posNode->data._name, name)) {
		posFrontNode = posNode;
		posNode = posNode->next;
		if (posNode == NULL) {
			printf("δ�ҵ�ָ������,ɾ��ʧ��!\n");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
}
// ********** �޸Ĳ��� **********
void modefyNode(struct Node* head, char* num) {
	if (head == NULL) {
		printf("����Ϊ��,�޸�ʧ��\n");
		return;
	}
	// ͨ��name�Ƚ��в���,�ҵ�name���ڵĽ��
	// �����޸�ѧ������Ϣ�����б���
	struct Node* phead = head->next;
	while (phead) {
		if (strcmp(phead->data.num, num)) {
			printf("���������ѧ������Ϣ\n");
			printf("����ѧ��������,����,�Ա�:");
			fflush(stdin);
			scanf("%s %d %s", phead->data._name, phead->data._age, phead->data._sex);
			return;
		}
		phead = phead->next;
	}
	printf("δ�и�ѧ������Ϣ,�޸�ʧ��!\n");
}
// ********** ���Ҳ��� **********
struct Node* findNode(struct Node* head, char* name) {
	if (head == NULL) {
		printf("����Ϊ��,ɾ��ʧ��!\n");
		return NULL;
	}
	struct Node* posNode = head->next;

	while (strcmp(posNode->data._name, name)) {
		posNode = posNode->next;
		if (posNode == NULL) {
			printf("δ�ҵ�ָ������!\n");
			return NULL;
		}
	}
	printf("���ҳɹ�\n");
	return posNode;
}
// ********** ��ӡ���� **********
void printList(struct Node* head) {
	struct Node* phead = head->next;
	printf("����\t����\t�Ա�\tѧ��\n");
	while (phead) {
		printf("%s\t%d\t%s\t%s\n", phead->data._name, phead->data._age, phead->data._sex, phead->data._num);
		phead = phead->next;
	}
}

void readInfoFromFile(struct Node* head, char* fileName) {
	// 1.���ļ�
	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fopen(fileName, "w+");
	}
	// 2.��ȡ�ļ�
	struct studentInf stu;
	while (fscanf(fp, "%s\t%d\t%s\t%s\n", stu._name, &stu._age, stu._sex, stu._num) != EOF) {
		insertNode(head, stu);
	}
	// 3.�ر��ļ�
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