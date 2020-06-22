#include "stu_inf.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1.界面
// 2.数据结构的设计
// 3.交互


// 菜单设计
void menu() {
	// 所有操作都必须同步到文件
	printf("------------[学生信息管理系统]-------------\n");
	printf("------------1.信息录入-------------\n");
	printf("------------2.信息打印-------------\n");
	printf("------------3.查找信息-------------\n");
	printf("------------4.删除信息-------------\n");
	printf("------------5.修改信息-------------\n");
	printf("-------------------------------------------\n");
}

// 用户的交互
void keyDown() {
	
	int choice = 0;
	scanf("%d", &choice);
	switch (choice) {
	case 0:
		printf("退出系统\n");
		exit(0);
		break;
	case 1:
		printf("信息录入\n");
		struct studentInf stu;
		printf("姓名\t年龄\t性别\t学号 : ");
		fflush(stdin);
		scanf("%s %d %s %s", stu._name, &stu._age, stu._sex, stu._num);
		insertNode(list, stu);
		writeInfoFromFile(list, "student.txt");
		break;
	case 2:
		printf("信息打印\n");
		printList(list);
		break;
	case 3:
		printf("查找信息\n");
		char name[32];
		printf("输入该学生的姓名:");
		scanf("%s", name);
		findNode(list, name);
		break;
	case 4:
		printf("删除信息\n");
		printf("输入该学生的姓名:");
		scanf("%s", name);
		deleteNode(list, name);
		writeInfoFromFile(list, "student.txt");
		break;
	case 5:
		printf("修改信息\n");
		writeInfoFromFile(list, "student.txt");
		break;
	default:
		printf("选择出错,重新输入\n");
		system("pause");
		break;
	}
	
}