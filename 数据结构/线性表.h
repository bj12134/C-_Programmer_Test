#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

#define DEFAULT_SIZE 10

template <class T>
class SeqList {
public:
	SeqList(size_t size = 0) {
		_count = size > DEFAULT_SIZE ? size : DEFAULT_SIZE;
		_data = new T(_count);
		_elemCount = 0;
	}
	//SeqList(const SeqList& sq);
	//SeqList& operator = (const SeqList& sq);
	~SeqList() {
		delete []_data;
	}
public:
	bool isEmpty()const {
		return _elemCount == 0;
	}
	bool isFull()const {
		return _elemCount >= _count;
	}
public:
	bool push_back();
	bool show_list()const;
	bool push_front();
	bool insert_val();
	bool insert_pos();
	bool pop_back();
	bool pop_front();
	bool delete_pos();
	bool delete_val();
	int search_val();
	T search_pos();
	void sort();
	void clear();
	void destroy();
	bool revrese();

private:
	T* _data;
	int _count;
	int _elemCount;
};

template <class T>
bool SeqList<T>::push_back() {
	int number = 0;
	if (isFull()) {
		cout << "线性表已满" << endl;
		return false;
	}
	cout << "输入尾随的数字(-1结束输入)" << endl;
	cin >> number;
	while (number != -1) {
		_data[_elemCount++] = number;
		cin >> number;
	}
	return true;
}

template <class T>
bool SeqList<T>::show_list()const {
	int i = 0;
	for (; i < _elemCount; ++i) {
		cout << _data[i] << "->";
	}
	cout << "NULL" << endl;
	return true;
}
template <class T>
bool SeqList<T>::push_front() {
	if (isFull()) {
		cout << "线性表存储已满" << endl;
		return false;
	}
	int number = 0;
	int i = _elemCount - 1;
	for (; i >= 0; --i) {
		_data[i] = _data[i - 1];
	}
	cout << "输入需要头插的数字";
	cin >> number;
	_data[0] = number;
	++_elemCount;
	return true;
}

template <class T>
bool SeqList<T>::insert_val() {
	int number1 = 0;
	int number2 = 0;
	int i = 0;
	int local = 0;
	if (isFull()) {
		cout << "线性表存储已满" << endl;
		return false;
	}
	cout << "输入要查找的位置的数字:";
	cin >> number1;
	for (; i < _elemCount; ++i) {
		if (_data[i] == number1) {
			local = i;
		}
		else {
			local = _elemCount;
		}
	}
	for (i = _elemCount - 1; i >= local; --i) {
		_data[i + 1] = _data[i];
	}
	cout << "输入该位置想要插入的数字" << endl;
	cin >> number2;
	_data[local] = number2;
	++_elemCount;
	return true;
}
template <class T>
bool SeqList<T>::insert_pos() {
	int number = 0;
	int i = 0;
	int pos = 0;
	if (isFull()) {
		cout << "线性表存储已满" << endl;
		return false;
	}	
	cout << "输入需要插入数字的位置:";
	cin >> pos;
	if (pos < 0 || pos > _elemCount) {
		cout << "Pos插入位置不合法" << endl;
		return false;
	}
	cout << "输入插入的数字:";
	cin >> number;
	if (isEmpty()) {
		_data[pos] = number;
		++_elemCount;
		return true;
	}
	for (i = _elemCount - 1; i >= pos; --i) {
		_data[i + 1] = _data[i];
	}
	_data[pos] = number;
	++_elemCount;
	return true;
}
template <class T>
bool SeqList<T>::pop_back() {
	if (isEmpty()) {
		cout << "线性表为空,删除失败" << endl;
		return false;
	}
	--_elemCount;
	return true;
}
template <class T>
bool SeqList<T>::pop_front() {
	if (isEmpty()) {
		cout << "线性表为空,删除失败" << endl;
		return false;
	}
	int i = 0;
	for (; i < _elemCount - 1; ++i) {
		_data[i] = _data[i + 1];
	}
	--_elemCount;
	return true;
}
template <class T>
bool SeqList<T>::delete_pos() {
	int i = 0;
	int pos = 0;
	if (isEmpty()) {
		cout << "线性表为空,删除失败" << endl;
		return false;
	}
	cout << "输入需要删除数字的位置:";
	cin >> pos;
	if (pos < 0 || pos > _elemCount) {
		cout << "Pos插入位置不合法" << endl;
		return false;
	}
	cout << "删除的数字为:" << _data[pos] << endl;
	for (i = pos; i < _elemCount - 1; ++i) {
		_data[i] = _data[i + 1];
	}
	--_elemCount;
	return true;
}
template <class T>
bool SeqList<T>::delete_val() {
	int number = 0;
	int i = 0;
	int local = 0;
	int k = 0;
	if (isEmpty()) {
		cout << "线性表为空,删除失败" << endl;
		return false;
	}
	cout << "输入要删除的数字:";
	cin >> number;
	for (; i < _elemCount; ++i) {
		if (_data[i] == number) {
			local = i;
			k = 1;
		}
	}
	if (!k) {
		cout << "未找到所要删除的数字,查找失败" << endl;
		return false;
	}
	for (i = local; i < _elemCount - 1; ++i) {
		_data[i] = _data[i + 1];
	}
	cout << "删除成功" << endl;
	--_elemCount;
	return true;
}
template <class T>
int SeqList<T>::search_val() {
	if (isEmpty()) {
		cout << "线性表为空,查找失败" << endl;
		return false;
	}
	int number = 0;
	cout << "请输入需要查找的数字";
	cin >> number;
	for (int i = 0; i < _elemCount; ++i) {
		if (_data[i] == number)
			return i;
	}
	reuturn - 1;
}
template <class T>
T SeqList<T>::search_pos() {
	if (isEmpty()) {
		cout << "线性表为空,查找失败" << endl;
		return false;
	}
	int pos = 0;
	cout << "请输入需要查找数字的位置:";
	cin >> pos;
	if (pos < 0 || pos > _elemCount) {
		cout << "Pos插入位置不合法" << endl;
		return false;
	}
	return _data[pos];
}
template <class T>
void SeqList<T>::sort() {
	int i = 0, j = 0;
	T tmp;
	for (; i < _elemCount; ++i) {
		for (; j < _elemCount - i - 1; ++j) {
			if (_data[j] > _data[j + 1]) {
				tmp = _data[j];
				_data[j] = _data[j + 1];
				_data[j + 1] = tmp;
			}
		}
	}
}
template <class T>
void SeqList<T>::clear() {
	_elemCount = 0;
}
template <class T>
bool SeqList<T>::revrese() {
	if (isEmpty()) {
		cout << "线性表为空,查找失败" << endl;
		return false;
	}
	int i = 0;
	T tmp;
	for (; i < _elemCount / 2; ++i) {
		tmp = _data[i];
		_data[i] = _data[_elemCount - i - 1];
		_data[_elemCount - i - 1] = tmp;
	}
	return true;
}