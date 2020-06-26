#include "string_simualtion.h"


// string类的非成员函数

std::istream& operator >> (std::istream& is, string_sim& str);
std::ostream& operator << (std::ostream& os, string_sim& str);
std::istream& getline(std::istream& is, string_sim& str, char delim);
std::istream& getline(std::istream& is, string_sim& str);

bool operator== (const string_sim& lhs, const string_sim& rhs);
bool operator== (const char* lhs, const string_sim& rhs);
bool operator== (const string_sim& lhs, const char* rhs);

bool operator!= (const string_sim& lhs, const string_sim& rhs);
bool operator!= (const char* lhs, const string_sim& rhs);
bool operator!= (const string& lhs, const char* rhs);

bool operator<  (const string_sim& lhs, const string_sim& rhs);
bool operator<  (const char* lhs, const string_sim& rhs);
bool operator<  (const string_sim& lhs, const char* rhs);

bool operator<= (const string_sim& lhs, const string& rhs);
bool operator<= (const char* lhs, const string_sim& rhs);
bool operator<= (const string_sim& lhs, const char* rhs);

bool operator>  (const string_sim& lhs, const string_sim& rhs);
bool operator>  (const char* lhs, const string_sim& rhs);
bool operator>  (const string_sim& lhs, const char* rhs);

bool operator>= (const string_sim& lhs, const string_sim& rhs);
bool operator>= (const char* lhs, const string_sim& rhs);
bool operator>= (const string_sim& lhs, const char* rhs);