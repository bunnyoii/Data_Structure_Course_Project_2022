#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "LString.h"
using namespace std;
const int maxInputSize = 256;
const int maxTxtSize = 65536;

class KeywordSolution {
private:
	std::ofstream ofs;
	std::ifstream file;
	AString txtName;
	AString txtContent; 
	AString txtFile;
	AString KeyWord;    
public:
	void Keymain();
	void menu();
	void inputTxt(AString& file, int opt);
	Status ContainTxt();
	Status isExist();
	Status OutputTxt();
	Status searchKeyword();
	Status clearFile();
	void Exit() {
		std::cout << "�����������...\n";
		// ������뻺����
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// �ȴ��û�����
		std::cin.get();
	}
};

//	����ģʽƥ���㷨 
/*	---- BF�㷨
�������ĵ�pos���ַ���ģʽ���ĵ�һ���ַ��Ƚϣ�
����ȣ����������ȽϺ����ַ���
�����ȣ�����������һ�ַ���������ģʽ���ĵ�һ���ַ��Ƚ� */
int countBF(AString pattern,AString text) {
	int count = 0; // �Ӵ����ֵĴ���
	int i = 0, j = 0;
	while (i <= text.curLength - pattern.curLength) {
		if (j < pattern.curLength && text.ch[i + j] == pattern.ch[j]) {
			j++; // ����ƥ����һ���ַ�
		}
		else {
			if (j == pattern.curLength) {
				count++; // ��ȫƥ�䣬���Ӽ�����
			}
			i++;
			j = 0; // �����Ӵ�����������������һ���ַ���ʼ�µ�ƥ��
		}
	}
	return count; // �����Ӵ��������г��ֵ��ܴ���
}

/*	---- KMP�㷨
�����Ѿ�����ƥ��Ľ�����ӿ�ģʽ���Ļ����ٶ�
��������ָ��i���ػ��ݣ��������ٵ�O(n+m)*/

// ���첿��ƥ���
void Nextval(const AString pattern, int next[])
{
	int len = pattern.curLength;
	next[0] = -1;//p����ʼ�±�Ϊ0��������������Ϊ-1
	int k = -1, j = 0;
	while (j < len) {
		if (k == -1 || pattern.ch[k] == pattern.ch[j]) {
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}

// KMP �㷨
int countKMP(const AString text, const AString pattern) {
	int next[maxTxtSize];
	int lenText = text.curLength;
	int lenPattern = pattern.curLength;
	int i = 0, n = 0, k = 0;
	Nextval(pattern, next);
	while (i < lenText) {
		if (k == -1 || text.ch[i] == pattern.ch[k]) {
			++i;
			++k;
		}
		else
			k = next[k];
		if (k == lenPattern) {
			n++;
			k = next[k];
		}
	}
	return n;
}

/*
* Function name : Keymain
* Function features : Implement the main process of the key solution.
*/
void KeywordSolution::Keymain()
{
	menu();
	inputTxt(txtName, 0);
	if (OutputTxt()) {
		std::cout << "�Ƿ���Ҫ���ԭ�ȵ��ļ����ݣ�Y/N���� ";
		while (true) {
			char response;
			response = getchar();
			if (response == 'Y' || response == 'y') {
				while (getchar() != '\n');// ������뻺����
				clearFile();
				break;
			}
			else if (response == 'N' || response == 'n') {
				while (getchar() != '\n'); // ������뻺����
				break;
			}
			else
				continue;
		}
	}
	ContainTxt();
	std::cout << "��������Ҫ�����Ĺؼ��֣�";
	inputTxt(KeyWord, 1);
	OutputTxt();
	searchKeyword();
	Exit();
}

/*
* Function name : menu
* Function features : Present the menu.
*/
void KeywordSolution::menu()
{
	std::cout << "��������������������������������������\n";
	std::cout << "��         �ؼ��ּ���ϵͳ           ��\n";
	std::cout << "��     Keyword Retrieval System     ��\n";
	std::cout << "��������������������������������������\n";
	std::cout << ">>>��������Ҫ�򿪵��ļ���\n";
	std::cout << ">>>�����ڵ��ļ����Զ��������ļ�����������Ƿ��ַ����������ģ���\n";
}

/*
* Function name : isExist
* Function features : Determine if the file exists.
*/
Status KeywordSolution::isExist()
{
	char* input = new char[maxInputSize];
	txtName.copyTo(input,txtName.Length() + 1);
	file.open(input);
	if (!file.is_open()) {
		std::cerr << "�޷����ļ� " << txtName << std::endl;
		return ERROR; // �˳����򣬷�������
	}
	return OK;
}

/*
* Function name :  inputTxt
* Function features :  Enter the file
* Input parameters : char* file, int opt
*/
void KeywordSolution::inputTxt(AString& file, int opt)
{
	while (true) {
		int MaxSize = 0;
		if (!opt)
			MaxSize = maxInputSize;
		else
			MaxSize = maxTxtSize;
		/* ����һ���ַ����洢���� */
		char* inputLine = nullptr;
		inputLine = new char[MaxSize];
		/* ��ȡ���� */
		cin.getline(inputLine, MaxSize);
		file.setString(inputLine);
		delete[] inputLine;
		break;
	}
}

/*
* Function name : ContainTxt
* Function features : Add the input content to the attachment file.
*/
Status KeywordSolution::ContainTxt()
{
	char* input = new char[maxInputSize];
	txtName.copyTo(input, txtName.Length() + 1);
	ofs.open(input, std::ios::app); // ���ļ��Ը�������
	if (!ofs.is_open()) {
		std::cerr << "�޷����ļ� " << txtName << std::endl;
		return ERROR; // �˳����򣬷�������
	}
	std::cout << "������Ҫд���ļ����ı�����(Ӣ��):\n";
	inputTxt(txtContent, 1);
	ofs << txtContent << std::endl; // ���ı�����д���ļ�
	ofs.close(); // �ر��ļ�
	std::cout << "�ı������ѳɹ����ӵ��ļ���" << txtName << "���У�" << std::endl;
	return OK;
}

/*
* Function name : OutputTxt
* Function features : Output the file content.
*/
Status KeywordSolution::OutputTxt()
{
	txtFile.clear();
	std::cout << "��ʾԴ�ļ���" << txtName.getString() << "�� : \n";
	if (!isExist()) {
		std::cout << "���Զ�������Ӧ�����ļ���\n";
		return ERROR;
	}
	if (file.get() == std::ifstream::traits_type::eof()) {
		std::cout << "Դ�ļ�Ϊ��" << std::endl;
		file.close();
		return ERROR;
	}
	else {
		std::cout << '\n';
		file.seekg(0, std::ios::beg);
		char tmp;
		while (file.get(tmp)) {
			txtFile.append(tmp);
			std::cout << tmp;
		}
		std::cout << "\n";
		file.close(); // �ر��ļ�
		return OK;
	}
}

/*
* Function name : searchKeyword
* Function features : Search for keywords.
*/
Status KeywordSolution::searchKeyword()
{
	if (!isExist()) {
		std::cout << "���ļ�ʧ�ܣ�\n";
		return ERROR;
	}
	std::cout << "�ؼ��ʳ��ִ����� : \n";
	int keywordCount = 0;
	keywordCount = countBF(KeyWord, txtFile);
	std::cout << "BF�㷨����Ч�� : " << keywordCount << " ��\n";
	keywordCount = countKMP(txtFile, KeyWord);
	std::cout << "KMP�㷨����Ч�� : " << keywordCount << " ��\n";
	return OK;
}

/*
* Function name : clearFile
* Function features : Clear the content of the file.
*/
Status KeywordSolution::clearFile()
{
	char* input = new char[maxInputSize];
	txtName.copyTo(input, txtName.Length()+1);
	std::ofstream clearStream(input, std::ofstream::out | std::ofstream::trunc);
	if (clearStream.is_open()) {
		clearStream.close();
		std::cout << "�ļ� " << txtName << " ����գ�" << std::endl;
		return OK;
	}
	else {
		std::cerr << "�޷�����ļ� " << txtName << std::endl;
		return ERROR;
	}
}

int main()
{
	KeywordSolution Key;
	Key.Keymain();
	return 0;
}