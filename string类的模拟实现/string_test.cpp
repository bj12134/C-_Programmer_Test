#include <iostream>
#include <string>

using namespace std;

void string_test_01() {
	// 1.string类对象的构造
	std::string str1;
	std::string str2("Hello World");
	std::string str3(10, 'c');
	std::string str4(str2);
	std::string str5(str2, 5);
	cout << "string();---------------------------";
	cout << "str1 : " << str1 << endl;
	cout << "string(const char* s);--------------";
	cout << "str2 : " << str2 << endl;
	cout << "string(size_t n, char c);-----------";
	cout << "str3 : " << str3 << endl;
	cout << "string(const string& s);------------";
	cout << "str4 : " << str4 << endl;
	cout << "string(const string& s,size_t n);---";
	cout << "str5 : " << str5 << endl;
}

void string_test_02() {
	// 2.string类对象的容量操作
	std::string str("Hello World");
	cout << str.length() << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;
	cout << str.empty() << endl;
	str.resize(5, 'o');
	cout << str << endl;
	str.clear();
}

int main() {

	return 0;
}