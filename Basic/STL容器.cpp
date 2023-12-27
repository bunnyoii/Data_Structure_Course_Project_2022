#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class MyString {
private:
	char* m_data;//用于保存字符串
public:
	MyString(const char* cstr = nullptr);//普通构造函数
	MyString(const MyString& str);//拷贝构造函数
	~MyString(void);//析构函数
	MyString& operator=(const MyString& other);//赋值函数
};