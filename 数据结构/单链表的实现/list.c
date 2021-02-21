#include "list.h"

// 1.����ĳ�ʼ��
void init_List(Node* node) {
    // �жϴ�������Ƿ�Ϸ�
    if (node == NULL)
        return;
    node->num = 0;
    node->next = NULL;
}
// 2.����Ĳ���
void insert_List(Node* node, ElemType val, int pos) {
    // �жϴ�������Ƿ�Ϸ�
    if (node == NULL || pos < 1 || pos > node->num + 1)
        return;
    // ����һ������ָ��
    Node* cur = node;
    // ���Ҳ����λ��
    for (int i = 1; i < pos; ++i) {
        cur = cur->next;
    }
    // ����һ���µ�Node�ڵ㣬�����ڴ�����һ�οռ�
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL)
        return;
    tmp->data = val;
    // ��tmp�ڵ���뵽������
    tmp->next = cur->next;
    cur->next = tmp;
    // �������ǣ�����Ԫ�غ�Ԫ������++
    ++node->num;
}
// 3.�����ɾ��
void delete_List(Node* node, int pos) {
    // �жϴ�������ĺϷ���
    if (node == NULL || pos > node->num || pos < 1)
        return;
    Node* cur = node;
    for (int i = 1; i < pos; ++i) {
        cur = cur->next;
    }
    Node* tmp = cur->next;
    // cur->next = tmp->next;
    cur->next = cur->next->next;

    free(tmp);
    --node->num;
}
// 4.����Ĳ���
Node* find_List(Node* node, ElemType val) {
    if (node == NULL)
        return NULL;
    Node* cur = node;
    while (cur = cur->next) {
        if (cur->data == val)
            return cur;
    }
    return NULL;
}
// 5.���������
void destory(Node* node) {
    if (node == NULL)
        return NULL;
    while (node->next) {
        delete_List(node, 1);
    }
}

// ͷ��ͷɾ
void push_front(Node* node, ElemType val) {
    if (node == NULL)
        return;
    Node* cur = node;
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL)
        return;
    tmp->data = val;
    tmp->next = cur->next;
    cur->next = tmp;
    node->num++;
}
void pop_front(Node* node) {
    if (node == NULL)
        return;
    if (node->next == NULL)
        return;
    Node* cur = node;
    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    node->num--;
}
// β��βɾ
void push_back(Node* node, ElemType val) {
    if (node == NULL)
        return;
    Node* cur = node;
    //Node* ptr = cur->next;
    //while (ptr) {
    //    cur = cur->next;
    //    ptr = cur->next;
    //}
    while (cur->next)
        cur = cur->next;
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = val;
    tmp->next = cur->next;
    cur->next = tmp;
    node->num++;
}
void pop_back(Node* node) {
    if (node == NULL)
        return;
    Node* cur = node;
    Node* tmp = node;
    while (tmp->next) {
        cur = tmp;
        tmp = tmp->next;
    }
    cur->next = tmp->next;
    free(tmp);
    node->num--;
}