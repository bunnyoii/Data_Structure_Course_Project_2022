#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "Tree.h"

#define MAX_SIZE 100

const int maxChildrenNum = 3;

// �洢��ͥ��Ա����Ϣ
struct People {
	char name[MAX_SIZE];		// ����
	People() = default;
	People(const char* buf) {
		strncpy(name, buf, MAX_SIZE);
		name[MAX_SIZE - 1] = '\0';
	}
	// �ж�������Ա�Ƿ���ͬһ����
	bool operator ==(const People& buf) {return strcmp(name,buf.name) == 0;}
};

std::ostream& operator<<(std::ostream& os, const People& person)
{
	os << person.name;
	return os;
}

// �������׹���ϵͳ
typedef class genealogyManagement {
private:
	MyBinaryTree<People> familyTree;
public:
	void initgenealogy();
	void operation();
	void completeTree();			// ���Ƽ���
	void addMembers();				// ��Ӽ�ͥ��Ա
	void dissolveFamily();			// ��ɢ�ֲ���ͥ��Ա
	void changeName();				// ���ļ�ͥ��Ա����
	bool IsDuplicate(char chiName[maxChildrenNum][MAX_SIZE]);// ��⽨����ͥ��Ա�Ƿ��ظ�
	void outputChildren(People parent);
	void menu();
	People inputParents(bool opt);
	void Exit() {
		std::cout << "�����������...\n";
		// ������뻺����
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// �ȴ��û�����
		std::cin.get();
	}
}GM;

void genealogyManagement::menu()
{
	std::cout << "��������������������������������������\n";
	std::cout << "��          ���׹���ϵͳ            ��\n";
	std::cout << "��   Genealogy Management System    ��\n";
	std::cout << "��������������������������������������\n\n";
	std::cout << "======================================\n";
	std::cout << "*         ��ѡ��Ҫִ�еĲ���         *\n";
	std::cout << "*          A --- ���Ƽ���            *\n";
	std::cout << "*          B --- ��Ӽ�ͥ��Ա        *\n";
	std::cout << "*          C --- ��ɢ�ֲ���ͥ        *\n";
	std::cout << "*          D --- ���ļ�ͥ��Ա����    *\n";
	std::cout << "*          E --- �˳�����            *\n";
	std::cout << "======================================\n";
}

// ��⽨����ͥ��Ա�Ƿ��ظ�
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

// �������
void genealogyManagement::outputChildren(People parent)
{
	std::cout << parent.name << "�ĵ�һ�������ǣ�";
	// ��ȡ��һ������
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	TreeNode<People>* child = familyTree.getLeftChild(parentNode);
	while (child != NULL) {
		std::cout << child->value.name << ' ';
		child = familyTree.getRightChild(child);
	}
	std::cout << '\n';
}

// ���븸ĸ
People genealogyManagement::inputParents(bool opt)
{
	char name[MAX_SIZE];
	People newParents;
	/*
	* ����Ҫ������ͥ/��Ӷ�Ů���˵�����
	* �����жϣ������Ƿ��ڼ�����
	*/
	while (true) {
		std::cin.getline(name, MAX_SIZE);
		newParents = People(name);
		if (familyTree.findNode(newParents, familyTree.getRoot()) == NULL) {
			std::cout << "���˲��ڱ������У�\n";
			std::cout << ">>>���������룺\n";
		}
		else if (opt && familyTree.findNode(newParents, familyTree.getRoot())->firstChild != NULL) {
			std::cout << newParents.name << "�ѽ�����ͥ��\n";
			std::cout << ">>>���������룺\n";
		}
		else
			break;
	}
	return newParents;
}

// �������� ȷ������
void genealogyManagement::initgenealogy()
{
	char name[MAX_SIZE];
	std::cout << "\n���Ƚ�������;\n";
	std::cout << ">>>����������������";
	std::cin.getline(name, MAX_SIZE);
	People ancestor(name);
	familyTree = MyBinaryTree<People>(ancestor);
	std::cout << "�˼��׵������ǣ�" << familyTree.getRoot()->value << std::endl;
}

// ���Ƽ���
void genealogyManagement::completeTree()
{
	int childrenNum = 0;
	char children[MAX_SIZE];
	char chiName[maxChildrenNum][MAX_SIZE];
	People newMember;
	People newChild;

	// ����Ҫ������ͥ���˵�����
	newMember = inputParents(1);
	/*
	* �����Ů����
	* �����жϣ���Ů������Ҫ����0��С��3
	*/
	std::cout << ">>>������" << newMember.name << "�Ķ�Ů������";
	while (true) {
		std::cin >> childrenNum;
		if (std::cin.fail() || childrenNum <= 0 || childrenNum > maxChildrenNum) {
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

	/*
	* �����Ů����
	* �����жϣ�������Ů����������ֻᱻ�ضϣ���������
	*/
	std::cout << "** ע�����������֣�ֻ�����Ӹ�����ȡ **\n";
	std::cout << ">>>����������" << newMember.name << "�Ķ�Ů������:";
	while (true) {
		std::cin.getline(children, MAX_SIZE);
		// ����ȡ����������ȡ
		int chiIndex = 0; // ��ǰ���ڴ����chiName������
		int charIndex = 0; // ��ǰchiName���ַ������ַ�����
		for (int i = 0; children[i] != '\0' && chiIndex < childrenNum; ++i) {
			if (children[i] == ' ') {
				if (charIndex > 0) { // ȷ�����������Ŀո�
					chiName[chiIndex][charIndex] = '\0'; // ��ֹ��ǰ�ַ���
					chiIndex++; // �ƶ�����һ���ַ���
					charIndex = 0; // �����ַ�����
				}
			}
			else {
				chiName[chiIndex][charIndex++] = children[i]; // �����ַ�
			}
		}
		// �������һ���ַ���
		if (charIndex > 0 && chiIndex < childrenNum) { chiName[chiIndex][charIndex] = '\0'; }
		if (IsDuplicate(chiName))
			break;
		else {
			std::cout << "���Ӳ�����������Ҳ�����Ժ����ϵ�������һ����\n";
			std::cout << ">>>�������������к��ӵ����֣�";
			continue;
		}
	}
	// ����������������
	TreeNode<People>* parentNode = familyTree.findNode(newMember, familyTree.getRoot());
	for (int i = 0; i < childrenNum; ++i) {
		newChild = People(chiName[i]);

		if (i == 0) {
			if (!familyTree.leftInsertNode(parentNode, newChild)) {
				std::cerr << "�޷�����: " << newChild.name << std::endl;
			}
			else
				parentNode = parentNode->firstChild;
		}
		else {
			// ����������Ϊ���ֵܲ���
			if (!familyTree.rightInsertNode(parentNode, newChild)) {
				std::cerr << "�޷�����: " << newChild.name << std::endl;
			}
			else
				parentNode = parentNode->nextSibling;
		}
	}
	outputChildren(newMember);
}

// ��Ӽ�ͥ��Ա
void genealogyManagement::addMembers()
{
	char childName[MAX_SIZE];
	People parent;
	People newChild;
	parent = inputParents(0);
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	std::cout << ">>>������"<<parent.name<<"����ӵĶ�/Ů������[��һ������Ĳ���洢]��";
	while (true) {
		std::cin.getline(childName, MAX_SIZE);
		newChild = People(childName);
		if (familyTree.findNode(newChild, familyTree.getRoot())!=NULL) {
			std::cout << "�����ڱ������У�\n";
			std::cout << ">>>���������룺\n";
		}
		else break;
	}
	if (!familyTree.insertAsFirstChild(parentNode, newChild)) {
		std::cerr << "�޷�����: " << newChild.name << std::endl;
	}
	outputChildren(parent);
}

// ��ɢ�ֲ���ͥ��Ա
void genealogyManagement::dissolveFamily()
{
	People parent;
	parent = inputParents(0);
	std::cout << "Ҫ��ɢ��ͥ�����ǣ�" << parent.name << std::endl;
	outputChildren(parent);
	TreeNode<People>* parentNode = familyTree.findNode(parent, familyTree.getRoot());
	familyTree.deleteChildren(parentNode);
}

// ���ļ�ͥ��Ա����
void genealogyManagement::changeName()
{
	char changeName[MAX_SIZE];
	People parent;
	People newName;
	parent = inputParents(0);
	std::cout << ">>��������ĺ������:";
	while (true) {
		std::cin.getline(changeName, MAX_SIZE);
		newName = People(changeName);
		if (familyTree.findNode(newName, familyTree.getRoot()) != NULL) {
			std::cout << "�����ڱ�������ʹ�ù���\n";
			std::cout << ">>>���������룺\n";
		}
		else break;
	}
	familyTree.modifyNode(parent, newName, familyTree.getRoot());
	std::cout << parent.name << "�Ѿ�����Ϊ" << newName.name << std::endl;
}

// ѡ�����
void genealogyManagement::operation()
{
	char input;
	bool IsExit = 1;
	while (IsExit) {
		while (true) {
			std::cout << "\n** ע���������ַ����Ե�һ���ַ�Ϊ׼ **\n";
			std::cout << ">>>��ѡ��Ҫִ�еĲ�����";
			input = getchar();
			// ������뻺�����еĶ����ַ�����س�����
			while (getchar() != '\n') {
				continue;
			}
			// ��������Ƿ�Ϊ��Ч�ַ�
			if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
				break;
			}
			else {
				std::cout << "��Ч�ַ������������룡" << std::endl;
			}
		}
		switch (input) {
		case 'A':		// ���Ƽ���
			std::cout << ">>>������Ҫ������ͥ���˵�������";
			completeTree();
			break;
		case 'B':
			std::cout << ">>>������Ҫ��Ӷ�Ů���˵�������";
			addMembers();
			break;
		case 'C':
			std::cout << ">>>������Ҫ��ɢ��ͥ���˵�������";
			dissolveFamily();
			break;
		case 'D':
			std::cout << ">>>������Ҫ�����������˵�������";
			changeName();
			break;
		case 'E':
			std::cout << "���ʽ����������˳���\n";
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