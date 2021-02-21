#include "list.h"

// 1.链表的初始化
void init_List(Node* node) {
    // 判断传入参数是否合法
    if (node == NULL)
        return;
    node->num = 0;
    node->next = NULL;
}
// 2.链表的插入
void insert_List(Node* node, ElemType val, int pos) {
    // 判断传入参数是否合法
    if (node == NULL || pos < 1 || pos > node->num + 1)
        return;
    // 声明一个副本指针
    Node* cur = node;
    // 查找插入的位置
    for (int i = 1; i < pos; ++i) {
        cur = cur->next;
    }
    // 声明一个新的Node节点，并向内存申请一段空间
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL)
        return;
    tmp->data = val;
    // 将tmp节点插入到链表中
    tmp->next = cur->next;
    cur->next = tmp;
    // 切勿忘记，插入元素后，元素数量++
    ++node->num;
}
// 3.链表的删除
void delete_List(Node* node, int pos) {
    // 判断传入参数的合法性
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
// 4.链表的查找
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
// 5.链表的销毁
void destory(Node* node) {
    if (node == NULL)
        return NULL;
    while (node->next) {
        delete_List(node, 1);
    }
}

// 头插头删
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
// 尾插尾删
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