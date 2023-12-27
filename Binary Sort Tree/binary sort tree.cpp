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
		std::cout << "�����������...\n";
		// ������뻺����
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// �ȴ��û�����
		std::cin.get();
	}
}BST;

// ��ʾ�˵�
void BinarySortTree::menu()
{
	std::cout << "��������������������������������������\n";
	std::cout << "��           ����������             ��\n";
	std::cout << "��         Binary Sort Tree         ��\n";
	std::cout << "��������������������������������������\n\n";
	std::cout << "======================================\n";
	std::cout << "*         ��ѡ��Ҫִ�еĲ���         *\n";
	std::cout << "*          1 --- ����������          *\n";
	std::cout << "*          2 --- ����Ԫ��            *\n";
	std::cout << "*          3 --- ��ѯԪ��            *\n";
	std::cout << "*          4 --- �˳�����            *\n";
	std::cout << "======================================\n";
}

// ������������
TreeNode<int>* BinarySortTree::insertRecursive(TreeNode<int>* node, int value)
{
	if (node == NULL) { return new TreeNode<int>(value);}
	if (value < node->value) { node->firstChild = insertRecursive(node->firstChild, value); }
	else { node->nextSibling = insertRecursive(node->nextSibling, value);}
	return node;
}

// �����ֵ
int BinarySortTree::inputNum()
{
	int inputNum;
	while (true) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum <= 0 || inputNum > 65536) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "����������������������\n";
			}
		}
	}
	return inputNum;
}

// ѡ�����
bool BinarySortTree::operation()
{
	int inputNum = 0;
	std::cout << ">>>��ѡ����Ҫִ�еĲ�����";
	while (true) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum <= 0 || inputNum > 4) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "����������������������\n";
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

// ��������������
void BinarySortTree::creatTree()
{
	int size[MAX_SIZE] = { 0 };
	int nodeNum = 0;
	std::cout << ">>>�����������ܽ�������";
	while (1) {
		std::cin >> nodeNum;
		if (std::cin.fail() || nodeNum <= 0 || nodeNum > MAX_SIZE) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "����������������������\n";
			}
		}
	}
	// �����ֵ
	std::cout << ">>>�������ֵ�Դ�������������[�����ܽ��������洢]��\n";
	for (int i = 0; i < nodeNum; ++i) { cin >> size[i]; }
	// ����
	for (int i = 0; i < nodeNum; ++i) {
		for (int j = i + 1; j < nodeNum; ++j) {
			if (size[i] == size[j]) {
				size[i] = 0;
				std::cout << "��ֵ" << size[j] << "�ظ���\n";
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

// ����Ԫ��
void BinarySortTree::addNode()
{
	int newElem;
	// ���������ļ�ֵ
	std::cout << "\n>>>��������Ҫ����ļ�ֵ��\n";
	newElem = inputNum();
	insert(newElem);
	inOrder(root);
	std::cout << std::endl;
}

// ��ѯԪ��
void BinarySortTree::searchNode()
{
	int searchElem;
	std::cout << "\n>>>��������Ҫ��ѯ�ļ�ֵ��\n";
	searchElem = inputNum();
	if (findNode(searchElem, root) != NULL)
		std::cout << "��ѯ�ɹ�����Ԫ���ڶ����������У�\n\n";
	else
		std::cout << "��ѯʧ�ܣ���Ԫ�ز����ڣ�\n\n";
}

// main����
int main()
{
	BST Solution;
	bool loop = 1;
	Solution.menu();
	while(loop){ loop = Solution.operation(); }
	return 0;
}
