#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class MyString {
private:
	char* m_data;//���ڱ����ַ���
public:
	MyString(const char* cstr = nullptr);//��ͨ���캯��
	MyString(const MyString& str);//�������캯��
	~MyString(void);//��������
	MyString& operator=(const MyString& other);//��ֵ����
};