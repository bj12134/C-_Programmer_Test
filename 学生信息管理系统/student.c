#include "stu_inf.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1.����
// 2.���ݽṹ�����
// 3.����


// �˵����
void menu() {
	// ���в���������ͬ�����ļ�
	printf("------------[ѧ����Ϣ����ϵͳ]-------------\n");
	printf("------------1.��Ϣ¼��-------------\n");
	printf("------------2.��Ϣ��ӡ-------------\n");
	printf("------------3.������Ϣ-------------\n");
	printf("------------4.ɾ����Ϣ-------------\n");
	printf("------------5.�޸���Ϣ-------------\n");
	printf("-------------------------------------------\n");
}

// �û��Ľ���
void keyDown() {
	
	int choice = 0;
	scanf("%d", &choice);
	switch (choice) {
	case 0:
		printf("�˳�ϵͳ\n");
		exit(0);
		break;
	case 1:
		printf("��Ϣ¼��\n");
		struct studentInf stu;
		printf("����\t����\t�Ա�\tѧ�� : ");
		fflush(stdin);
		scanf("%s %d %s %s", stu._name, &stu._age, stu._sex, stu._num);
		insertNode(list, stu);
		writeInfoFromFile(list, "student.txt");
		break;
	case 2:
		printf("��Ϣ��ӡ\n");
		printList(list);
		break;
	case 3:
		printf("������Ϣ\n");
		char name[32];
		printf("�����ѧ��������:");
		scanf("%s", name);
		findNode(list, name);
		break;
	case 4:
		printf("ɾ����Ϣ\n");
		printf("�����ѧ��������:");
		scanf("%s", name);
		deleteNode(list, name);
		writeInfoFromFile(list, "student.txt");
		break;
	case 5:
		printf("�޸���Ϣ\n");
		writeInfoFromFile(list, "student.txt");
		break;
	default:
		printf("ѡ�����,��������\n");
		system("pause");
		break;
	}
	
}