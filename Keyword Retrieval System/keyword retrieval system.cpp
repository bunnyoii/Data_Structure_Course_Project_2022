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
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
		std::cin.get();
	}
};

//	串的模式匹配算法 
/*	---- BF算法
将主串的第pos个字符和模式串的第一个字符比较，
若相等，则继续逐个比较后续字符；
若不等，从主串的下一字符起，重新与模式串的第一个字符比较 */
int countBF(AString pattern,AString text) {
	int count = 0; // 子串出现的次数
	int i = 0, j = 0;
	while (i <= text.curLength - pattern.curLength) {
		if (j < pattern.curLength && text.ch[i + j] == pattern.ch[j]) {
			j++; // 继续匹配下一个字符
		}
		else {
			if (j == pattern.curLength) {
				count++; // 完全匹配，增加计数器
			}
			i++;
			j = 0; // 重置子串索引，从主串的下一个字符开始新的匹配
		}
	}
	return count; // 返回子串在主串中出现的总次数
}

/*	---- KMP算法
利用已经部分匹配的结果而加快模式串的滑动速度
且主串的指针i不必回溯，可以提速到O(n+m)*/

// 构造部分匹配表
void Nextval(const AString pattern, int next[])
{
	int len = pattern.curLength;
	next[0] = -1;//p的起始下标为0，所以这里设置为-1
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

// KMP 算法
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
		std::cout << "是否需要清空原先的文件内容（Y/N）？ ";
		while (true) {
			char response;
			response = getchar();
			if (response == 'Y' || response == 'y') {
				while (getchar() != '\n');// 清空输入缓冲区
				clearFile();
				break;
			}
			else if (response == 'N' || response == 'n') {
				while (getchar() != '\n'); // 清空输入缓冲区
				break;
			}
			else
				continue;
		}
	}
	ContainTxt();
	std::cout << "请输入需要检索的关键字：";
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
	std::cout << "···················\n";
	std::cout << "·         关键字检索系统           ·\n";
	std::cout << "·     Keyword Retrieval System     ·\n";
	std::cout << "···················\n";
	std::cout << ">>>请输入想要打开的文件名\n";
	std::cout << ">>>不存在的文件会自动创建，文件名请勿输入非法字符（包括中文）！\n";
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
		std::cerr << "无法打开文件 " << txtName << std::endl;
		return ERROR; // 退出程序，发生错误
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
		/* 创建一个字符串存储输入 */
		char* inputLine = nullptr;
		inputLine = new char[MaxSize];
		/* 获取输入 */
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
	ofs.open(input, std::ios::app); // 打开文件以附加内容
	if (!ofs.is_open()) {
		std::cerr << "无法打开文件 " << txtName << std::endl;
		return ERROR; // 退出程序，发生错误
	}
	std::cout << "请输入要写入文件的文本内容(英文):\n";
	inputTxt(txtContent, 1);
	ofs << txtContent << std::endl; // 将文本内容写入文件
	ofs.close(); // 关闭文件
	std::cout << "文本内容已成功附加到文件“" << txtName << "”中！" << std::endl;
	return OK;
}

/*
* Function name : OutputTxt
* Function features : Output the file content.
*/
Status KeywordSolution::OutputTxt()
{
	txtFile.clear();
	std::cout << "显示源文件“" << txtName.getString() << "” : \n";
	if (!isExist()) {
		std::cout << "已自动创建对应的新文件。\n";
		return ERROR;
	}
	if (file.get() == std::ifstream::traits_type::eof()) {
		std::cout << "源文件为空" << std::endl;
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
		file.close(); // 关闭文件
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
		std::cout << "打开文件失败！\n";
		return ERROR;
	}
	std::cout << "关键词出现次数共 : \n";
	int keywordCount = 0;
	keywordCount = countBF(KeyWord, txtFile);
	std::cout << "BF算法搜索效果 : " << keywordCount << " 次\n";
	keywordCount = countKMP(txtFile, KeyWord);
	std::cout << "KMP算法搜索效果 : " << keywordCount << " 次\n";
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
		std::cout << "文件 " << txtName << " 已清空！" << std::endl;
		return OK;
	}
	else {
		std::cerr << "无法清空文件 " << txtName << std::endl;
		return ERROR;
	}
}

int main()
{
	KeywordSolution Key;
	Key.Keymain();
	return 0;
}