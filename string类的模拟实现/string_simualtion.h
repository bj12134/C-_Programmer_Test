#pragma once

#include <assert.h>
#include <string.h>
#include <istream>
using namespace std;

#define npos = 0

class string_sim {
public:
	string_sim(const char* str = "") {
		if (str == nullptr) {
			assert(false);
			return;
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	~string_sim() {
		if (_str) {
			delete[]_str;
			_str = nullptr;
		}
	}

public:	//string��������������
	size_t size() const;
	size_t length() const;
	size_t capacity()const;
	bool empty()const;
	void clear();
	void resize(size_t n, char c);
	void resize(size_t n);
	void reserve(size_t res_arg = 0);
public:	// string�����ķ��ʲ���
	char& operator[](size_t pos);
	const char& operator [] (size_t pos)const;
public:	// string�������޸Ĳ���
	void push_back(char c);
	string_sim& append(const char* s);
	string_sim& operator += (const string_sim& str);
	string_sim& operator += (const char c);
	const char* c_str() const;
	size_t find(char c, size_t pos = 0)const;
	size_t rfind(char c, size_t npos);
	string_sim substr(size_t pos, size_t len) const;
public: // string��ķǳ�Ա����

public:
	
private:
	char* _str;
};