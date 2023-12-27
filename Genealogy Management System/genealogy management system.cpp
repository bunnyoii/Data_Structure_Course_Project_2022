#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "Tree.h"

#define MAX_SIZE 100

const int maxChildrenNum = 3;

// 存储家庭成员的信息
struct People {
	char name[MAX_SIZE];		// 姓名
	People() = default;
	People(const char* buf) {
		strncpy(name, buf, MAX_SIZE);
		name[MAX_SIZE - 1] = '\0';
	}
	// 判断两个成员是否是同一个人
	bool operator ==(const People& buf) {return strcmp(name,buf.name) == 0;}
};

std::ostream& operator<<(std::ostream& os, const People& person)
{
	os << person.name;
	return os;
}

// 建立家谱管理系统
typedef class genealogyManagement {
private:
	MyBinaryTree<People> familyTree;
public:
	void initgenealogy();
	void operation();
	void completeTree();			// 完善家谱
	void addMembers();				// 添加家庭成员
	void dissolveFamily();			// 解散局部家庭成员
	void changeName();				// 更改家庭成员姓名
	bool IsDuplicate(char chiName[maxChildrenNum][MAX_SIZE]);// 检测建立家庭成员是否重复
	void outputChildren(People parent);
	void menu();
	People inputParents(bool opt);
	void Exit() {
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
		std::cin.get();
	}
}GM;

void genealogyManagement::menu()
{
	std::cout << "···················\n";
	std::cout << "·          家谱管理系统            ·\n";
	std::cout << "·   Genealogy Management System    ·\n";
	std::cout << "···················\n\n";
	std::cout << "======================================\n";
	std::cout << "*         请选择要执行的操作         *\n";
	std::cout << "*          A --- 完善家谱            *\n";
	std::cout << "*          B --- 添加家庭成员        *\n";
	std::cout << "*          C --- 解散局部家庭        *\n";
	std::cout << "*          D --- 更改家庭成员姓名    *\n";
	std::cout << "*          E --- 退出程序            *\n";
	std::cout << "======================================\n";
}

// 检测建立家庭成员是否重复
bool genealogyManagement::IsDuplicate(char chiName[maxChildrenNum][MAX_SIZE])
{
	for (int i = 0; i < maxChildrenNum; ++i) {
		for (int j = i + 1; j < maxChildrenNum; ++j) {
			if (strcmp(chiName[i], chiName[j]) == 0)
				return 0;
		}
	}
	for (int i = 0; i < maxChildrenNum; ++i) {
		People person(chiName[i]);
		if (familyTree.findNode(person, familyTree.getRoot()) != NULL)
			return 0;
	}
	return 1;
}

// 输出子孙
void genealogyManagement::outputChildren(People parent)
{
	std::cout << parent.name << "的第一代子孙是：";
	// 获取第一个孩子
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	TreeNode<People>* child = familyTree.getLeftChild(parentNode);
	while (child != NULL) {
		std::cout << child->value.name << ' ';
		child = familyTree.getRightChild(child);
	}
	std::cout << '\n';
}

// 输入父母
People genealogyManagement::inputParents(bool opt)
{
	char name[MAX_SIZE];
	People newParents;
	/*
	* 输入要建立家庭/添加儿女的人的姓名
	* 错误判断：该人是否在家族里
	*/
	while (true) {
		std::cin.getline(name, MAX_SIZE);
		newParents = People(name);
		if (familyTree.findNode(newParents, familyTree.getRoot()) == NULL) {
			std::cout << "该人不在本家族中！\n";
			std::cout << ">>>请重新输入：\n";
		}
		else if (opt && familyTree.findNode(newParents, familyTree.getRoot())->firstChild != NULL) {
			std::cout << newParents.name << "已建立家庭！\n";
			std::cout << ">>>请重新输入：\n";
		}
		else
			break;
	}
	return newParents;
}

// 建立家谱 确定祖先
void genealogyManagement::initgenealogy()
{
	char name[MAX_SIZE];
	std::cout << "\n首先建立家谱;\n";
	std::cout << ">>>请输入祖先姓名：";
	std::cin.getline(name, MAX_SIZE);
	People ancestor(name);
	familyTree = MyBinaryTree<People>(ancestor);
	std::cout << "此家谱的祖先是：" << familyTree.getRoot()->value << std::endl;
}

// 完善家谱
void genealogyManagement::completeTree()
{
	int childrenNum = 0;
	char children[MAX_SIZE];
	char chiName[maxChildrenNum][MAX_SIZE];
	People newMember;
	People newChild;

	// 输入要建立家庭的人的名字
	newMember = inputParents(1);
	/*
	* 输入儿女人数
	* 错误判断：儿女人数需要大于0且小于3
	*/
	std::cout << ">>>请输入" << newMember.name << "的儿女人数：";
	while (true) {
		std::cin >> childrenNum;
		if (std::cin.fail() || childrenNum <= 0 || childrenNum > maxChildrenNum) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "输入数据有误，请重新输入\n";
			}
		}
	}

	/*
	* 输入儿女名字
	* 错误判断：超过儿女人数后的名字会被截断；不能重名
	*/
	std::cout << "** 注：输入多个名字，只按孩子个数读取 **\n";
	std::cout << ">>>请依次输入" << newMember.name << "的儿女的姓名:";
	while (true) {
		std::cin.getline(children, MAX_SIZE);
		// 将读取到的内容提取
		int chiIndex = 0; // 当前正在处理的chiName的索引
		int charIndex = 0; // 当前chiName子字符串的字符索引
		for (int i = 0; children[i] != '\0' && chiIndex < childrenNum; ++i) {
			if (children[i] == ' ') {
				if (charIndex > 0) { // 确保不是连续的空格
					chiName[chiIndex][charIndex] = '\0'; // 终止当前字符串
					chiIndex++; // 移动到下一个字符串
					charIndex = 0; // 重置字符索引
				}
			}
			else {
				chiName[chiIndex][charIndex++] = children[i]; // 复制字符
			}
		}
		// 处理最后一个字符串
		if (charIndex > 0 && chiIndex < childrenNum) { chiName[chiIndex][charIndex] = '\0'; }
		if (IsDuplicate(chiName))
			break;
		else {
			std::cout << "孩子不可以重名，也不可以和祖上的人名字一样！\n";
			std::cout << ">>>请重新输入所有孩子的名字：";
			continue;
		}
	}
	// 将其插入进家族树里
	TreeNode<People>* parentNode = familyTree.findNode(newMember, familyTree.getRoot());
	for (int i = 0; i < childrenNum; ++i) {
		newChild = People(chiName[i]);

		if (i == 0) {
			if (!familyTree.leftInsertNode(parentNode, newChild)) {
				std::cerr << "无法插入: " << newChild.name << std::endl;
			}
			else
				parentNode = parentNode->firstChild;
		}
		else {
			// 其他名字作为右兄弟插入
			if (!familyTree.rightInsertNode(parentNode, newChild)) {
				std::cerr << "无法插入: " << newChild.name << std::endl;
			}
			else
				parentNode = parentNode->nextSibling;
		}
	}
	outputChildren(newMember);
}

// 添加家庭成员
void genealogyManagement::addMembers()
{
	char childName[MAX_SIZE];
	People parent;
	People newChild;
	parent = inputParents(0);
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	std::cout << ">>>请输入"<<parent.name<<"新添加的儿/女的姓名[仅一个，多的不予存储]：";
	while (true) {
		std::cin.getline(childName, MAX_SIZE);
		newChild = People(childName);
		if (familyTree.findNode(newChild, familyTree.getRoot())!=NULL) {
			std::cout << "该人在本家族中！\n";
			std::cout << ">>>请重新输入：\n";
		}
		else break;
	}
	if (!familyTree.insertAsFirstChild(parentNode, newChild)) {
		std::cerr << "无法插入: " << newChild.name << std::endl;
	}
	outputChildren(parent);
}

// 解散局部家庭成员
void genealogyManagement::dissolveFamily()
{
	People parent;
	parent = inputParents(0);
	std::cout << "要解散家庭的人是：" << parent.name << std::endl;
	outputChildren(parent);
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	familyTree.deleteChildren(parentNode);
}

// 更改家庭成员姓名
void genealogyManagement::changeName()
{
	char changeName[MAX_SIZE];
	People parent;
	People newName;
	parent = inputParents(0);
	std::cout << ">>请输入更改后的姓名:";
	while (true) {
		std::cin.getline(changeName, MAX_SIZE);
		newName = People(changeName);
		if (familyTree.findNode(newName, familyTree.getRoot()) != NULL) {
			std::cout << "该名在本家族中使用过！\n";
			std::cout << ">>>请重新输入：\n";
		}
		else break;
	}
	familyTree.modifyNode(parent, newName, familyTree.getRoot());
	std::cout << parent.name << "已经更名为" << newName.name << std::endl;
}

// 选择操作
void genealogyManagement::operation()
{
	char input;
	bool IsExit = 1;
	while (IsExit) {
		while (true) {
			std::cout << "\n** 注：输入多个字符，以第一个字符为准 **\n";
			std::cout << ">>>请选择要执行的操作：";
			input = getchar();
			// 清除输入缓冲区中的多余字符（如回车键）
			while (getchar() != '\n') {
				continue;
			}
			// 检查输入是否为有效字符
			if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
				break;
			}
			else {
				std::cout << "无效字符，请重新输入！" << std::endl;
			}
		}
		switch (input) {
		case 'A':		// 完善家谱
			std::cout << ">>>请输入要建立家庭的人的姓名：";
			completeTree();
			break;
		case 'B':
			std::cout << ">>>请输入要添加儿女的人的姓名：";
			addMembers();
			break;
		case 'C':
			std::cout << ">>>请输入要解散家庭的人的姓名：";
			dissolveFamily();
			break;
		case 'D':
			std::cout << ">>>请输入要更改姓名的人的姓名：";
			changeName();
			break;
		case 'E':
			std::cout << "访问结束，程序退出。\n";
			Exit();
			IsExit = 0;
			break;
		}
	}
}

int main()
{
	GM Solution;
	Solution.menu();
	Solution.initgenealogy();
	Solution.operation();
	return 0;
}