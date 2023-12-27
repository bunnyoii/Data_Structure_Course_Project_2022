#include <iostream>
#include "BinaryTree.h"

#define MAX_SIZE 100

typedef class BinarySortTree:public MyBinaryTree<int>{
private:
	TreeNode<int>* insertRecursive(TreeNode<int>* node, int value);
public:
	void menu();
	void creatTree();
	void addNode();
	void searchNode();
	void insert(int value){ root = insertRecursive(root, value); }
	bool operation();
	int inputNum();
	void Exit() {
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
		std::cin.get();
	}
}BST;

// 显示菜单
void BinarySortTree::menu()
{
	std::cout << "···················\n";
	std::cout << "·           二叉排序树             ·\n";
	std::cout << "·         Binary Sort Tree         ·\n";
	std::cout << "···················\n\n";
	std::cout << "======================================\n";
	std::cout << "*         请选择要执行的操作         *\n";
	std::cout << "*          1 --- 建立二叉树          *\n";
	std::cout << "*          2 --- 插入元素            *\n";
	std::cout << "*          3 --- 查询元素            *\n";
	std::cout << "*          4 --- 退出程序            *\n";
	std::cout << "======================================\n";
}

// 二叉树排序建立
TreeNode<int>* BinarySortTree::insertRecursive(TreeNode<int>* node, int value)
{
	if (node == NULL) { return new TreeNode<int>(value);}
	if (value < node->value) { node->firstChild = insertRecursive(node->firstChild, value); }
	else { node->nextSibling = insertRecursive(node->nextSibling, value);}
	return node;
}

// 输入键值
int BinarySortTree::inputNum()
{
	int inputNum;
	while (true) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum <= 0 || inputNum > 65536) {
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
	return inputNum;
}

// 选择操作
bool BinarySortTree::operation()
{
	int inputNum = 0;
	std::cout << ">>>请选择你要执行的操作：";
	while (true) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum <= 0 || inputNum > 4) {
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
	switch (inputNum)
	{
	case 1:
		creatTree();
		break;
	case 2:
		addNode();
		break;
	case 3:
		searchNode();
		break;
	case 4:
		Exit();
		return 0;
		break;
	}
	return 0;
}

// 构建二叉排序树
void BinarySortTree::creatTree()
{
	int size[MAX_SIZE] = { 0 };
	int nodeNum = 0;
	std::cout << ">>>请输入树的总结点个数：";
	while (1) {
		std::cin >> nodeNum;
		if (std::cin.fail() || nodeNum <= 0 || nodeNum > MAX_SIZE) {
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
	// 输入键值
	std::cout << ">>>请输入键值以创建二叉排序树[超过总结点数不予存储]：\n";
	for (int i = 0; i < nodeNum; ++i) { cin >> size[i]; }
	// 查重
	for (int i = 0; i < nodeNum; ++i) {
		for (int j = i + 1; j < nodeNum; ++j) {
			if (size[i] == size[j]) {
				size[i] = 0;
				std::cout << "键值" << size[j] << "重复！\n";
				break;
			}
		}
	}
	for (int i = 0; i < nodeNum; ++i) {
		if (size[i] != 0)
			insert(size[i]);
	}
	inOrder(root);
	std::cout << std::endl;
}

// 增加元素
void BinarySortTree::addNode()
{
	int newElem;
	// 输入新增的键值
	std::cout << "\n>>>请输入需要插入的键值：\n";
	newElem = inputNum();
	insert(newElem);
	inOrder(root);
	std::cout << std::endl;
}

// 查询元素
void BinarySortTree::searchNode()
{
	int searchElem;
	std::cout << "\n>>>请输入需要查询的键值：\n";
	searchElem = inputNum();
	if (findNode(searchElem, root) != NULL)
		std::cout << "查询成功，该元素在二叉排序树中！\n\n";
	else
		std::cout << "查询失败，该元素不存在！\n\n";
}

// main函数
int main()
{
	BST Solution;
	bool loop = 1;
	Solution.menu();
	while(loop){ loop = Solution.operation(); }
	return 0;
}
