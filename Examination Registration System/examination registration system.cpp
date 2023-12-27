#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <conio.h>

/* �����㷨���õ���Ԥ���峣�������� */
// �������״̬����
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

// startus �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
const int maxLength = (int)1e6;
const int minLength = 1;
const int maxAge = 35;
const int minAge = 18;
const int maxCategoryLength = 18;
const int maxSexLength = 3;
const int maxNameLength = 18;

/* �����ṹ��洢������Ϣ */
typedef struct studentInformation {
	int examNum;
	char name[maxNameLength];
	char sex[maxSexLength];
	int age;
	char applicationCategory[maxCategoryLength];
}SI;

/* ��������洢ͳ�Ƶı��������Ϣ */
typedef struct ApplicationCategoryCount {
	char category[maxCategoryLength];
	int count;
	ApplicationCategoryCount* next;
}ACC;

/* ����Ľ��� */
// �洢������Ϣ
typedef struct LNode {
	SI data;//����������
	struct LNode* next;//����ָ����
} *LinkList;

/* getline��������ʵ�� */
int myGetline(char s[], int lim)
{
	int c, i;// getchar()����ֵΪint�ͣ���c��int�Ͷ���
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

class solution {
private:
	LNode* studentList;
	SI getStudentData;
	ACC* categoryCounts = nullptr;
	int personNum;//������
	int opt;//����Ĳ�����
	int operationNum;//����Ŀ���
	int locationNum;//�����λ�����
	int operationLocation;//����Ŀ�������Ӧ��λ�����
	int femaleNum = 0;//Ů������
	int maleNum = 0;//��������
	int searchExamNum = 0;//��Ҫ���ҵ�ѧ���Ŀ���
	bool NumorInformation;//����Ԫ��ʱ��Ҫ������Ż���ֵ

public:
	// ��ʼ������
	Status InitList() {
		studentList = new LNode;
		studentList->next = NULL;
		return OK;
	}
	~solution() {
		DestroyList();
	}
	// ���ٵ�����L
	Status DestroyList() {
		LNode* p;
		while (studentList) {
			p = studentList;
			studentList = studentList->next;
			delete p;
		}
		return OK;
	}
	// �ж������Ƿ�Ϊ��
	bool listEmpty() {
		if (studentList->next)
			return 0;
		else
			return 1;
	}
	// ���������Ϣ
	void showData(SI studentData, bool opt) {
		if (opt) {
			std::cout << "| " << std::setw(18) << std::left << studentData.examNum;
			std::cout << "| " << std::setw(18) <<std::left << studentData.name;
			std::cout << "| " << std::setw(18) <<std::left << studentData.sex;
			std::cout << "| " << std::setw(18) <<std::left << studentData.age;
			std::cout << "| " << std::setw(18) <<std::left << studentData.applicationCategory;
			std::cout << "|\n";
		}
		else {
			std::cout << std::setw(18) <<std::left << studentData.examNum;
			std::cout << std::setw(18) <<std::left << studentData.name;
			std::cout << std::setw(18) <<std::left << studentData.sex;
			std::cout << std::setw(18) <<std::left << studentData.age;
			std::cout << std::setw(18) <<std::left << studentData.applicationCategory << std::endl;
		}
	}
	Status listInsert();
	Status listDelete();
	int getElem(bool InformationorNum);
	Status listRevise();
	void deletRepetitiveList();
	int listLength();
	void statsSexDistribution();
	void statsAge();
	void countApplicationCategory();
	void statsInformation();
	void createList();
	void inputPersonNum();
	bool inputPersonInformation(SI& studentData);
	void inputOperationLocation();
	void inputOperationNum();
	bool option();
	void output(bool opt);
};

/***************************************************************************
  �������ƣ�	deletRepetitiveList����
  ���������	��
  ��   �ܣ�	����˫��ѭ����������ѭ����ǰ�����Ľ��Ϊcur����ѭ����cur��ʼ��������ͬ��ɾ�� 
  �� �� ֵ��	��
 ***************************************************************************/
void solution::deletRepetitiveList()
{
	LinkList p, q;
	p = studentList;
	while (p != NULL){
		q = p;
		while (q->next != NULL){
			if (p->data.examNum == q->next->data.examNum)//ɾ��q����ڵ�
				q->next = q->next->next;//ɾ��q->next����ڵ� 
			else
				q = q->next;
		}
		p = p->next;
	}		
}

/***************************************************************************
  �������ƣ�	listInsert����
  ���������	��
  ��   �ܣ�	�ڵ�i��Ԫ��ǰ���뿼����Ϣ
  �� �� ֵ��	��
 ***************************************************************************/
Status solution::listInsert()
{
	LNode* p = studentList;
	LNode* s;
	int j = 0;
	std::cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������\n";
	while (p && j < locationNum - 1) { p = p->next; ++j; }//Ѱ�ҵ�i-1����㣬pָ��i-1���
	if (!p || j > locationNum - 1) return ERROR;//i���ڱ�+1����С��1������λ�÷Ƿ�
	s = new LNode;
	while (!inputPersonInformation(s->data)) continue;
	s->next = p->next;//�����s����L��
	p->next = s;
	return OK;
}

/***************************************************************************
  �������ƣ�	listDelete����
  ���������	��
  ��   �ܣ�	�ڵ�i��Ԫ��ɾ��������Ϣ
  �� �� ֵ��	��
 ***************************************************************************/
Status solution::listDelete() {
	LNode* p = studentList;
	int j = 0;
	while (p->next && j < operationLocation - 1) { p = p->next; ++j; }//Ѱ�ҵ�i����㣬����pָ����ǰ��
	if (!(p->next) || j > operationLocation - 1)return ERROR;
	LNode* q;
	q = p->next;//��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
	p->next = q->next;//�ı�ɾ�����ǰ������ָ����
	getStudentData = q->data;//����ɾ������������
	std::cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
	showData(getStudentData, 0);
	delete q;//�ͷ�ɾ�����Ŀռ�
	return OK;
}

/***************************************************************************
  �������ƣ�	getElem����
  ���������	InformationorNum -- 1 ��õ�ǰԪ�ص�ֵ
							 -- 0 ��õ�ǰԪ�ص����
  ��   �ܣ�	��ֵ����Ԫ��
  �� �� ֵ��	ERROR -- ����ʧ��
			OK    -- ���ҳɹ������������ҵĿ�����ȫ����Ϣ
			j     -- ���ҳɹ���������Ҫ���ҵ��������
 ***************************************************************************/
int solution::getElem(bool InformationorNum) {
	LNode* p;
	p = studentList->next;
	int j = 1;
	while (p && p->data.examNum != operationNum) {
		p = p->next;
		j++;
	}
	if (!p || j > personNum) {
		std::cout << "������Ҫ���ҵĿ�������Ϣ��" << std::endl;
		return ERROR;
	}
	if (InformationorNum) {
		getStudentData = p->data;
		return OK;
	}
	else
		return j;
}

/***************************************************************************
  �������ƣ�	listRevise����
  ���������	��
  ��   �ܣ�	�޸Ŀ�����Ϣ
  �� �� ֵ��	��
 ***************************************************************************/
Status solution::listRevise() {
	LNode* p = studentList;
	int j = 0;
	while (p->next && j < operationLocation - 1) { p = p->next; ++j; }//Ѱ�ҵ�i����㣬����pָ����ǰ��
	if (!(p->next) || j > operationLocation - 1)return ERROR;
	std::cout << "�����������޸ĺ�ĵĿ����Ŀ��ţ��������Ա����估�������\n";
	while (!inputPersonInformation(getStudentData)) continue;
	p->next->data = getStudentData;
	return OK;
}

/***************************************************************************
  �������ƣ�	listLength����
  ���������	��
  ��   �ܣ�	ͳ��������
  �� �� ֵ��	������length
 ***************************************************************************/
int solution::listLength() {
	LNode* p = studentList->next;
	int length = 0;
	while (p) {
		length++;
		p = p->next;
	}
	return length;
}

/***************************************************************************
  �������ƣ�	statsSexDistribution����
  ���������	��
  ��   �ܣ�	ͳ����Ů�����ֲ�
  �� �� ֵ��	��
 ***************************************************************************/
void solution::statsSexDistribution()
{
	LNode* p = studentList->next;
	while (p) {
		if (p->data.sex[0] == -59 && p->data.sex[1] == -82)//Ů
			femaleNum++;
		else if (p->data.sex[0] == -60 && p->data.sex[1] == -48)//��
			maleNum++;
		p = p->next;
	}
	std::cout << std::endl;
	std::cout << "������������" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| �Ա�����";
	std::cout << std::setw(20) <<std::left << "| �Ա�����";
	std::cout << std::setw(20) <<std::left << "| �Ա����          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << "| " << std::setw(18) <<std::left << "��";
	std::cout << "| " << std::setw(18) <<std::left << maleNum;
	std::cout << "| " << std::setw(17) <<std::left << maleNum * 100.0 / personNum << '%';
	std::cout << "|\n";
	std::cout << "| " << std::setw(18) <<std::left << "Ů";
	std::cout << "| " << std::setw(18) <<std::left << femaleNum;
	std::cout << "| " << std::setw(17) <<std::left << femaleNum * 100.0 / personNum << '%';
	std::cout << "|\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  �������ƣ�	statsAge����
  ���������	��
  ��   �ܣ�	ͳ������ֲ�
  �� �� ֵ��	��
 ***************************************************************************/
void solution::statsAge()
{
	int ageCounts[maxAge - minAge + 1];
	int flag = 0;
	for (int j = 0; j < maxAge - minAge + 1; j++)
		ageCounts[j] = 0;
	LNode* p = studentList->next;
	//��������ͳ��ÿ�������Ӧ��ѧ������
	while (p) {
		ageCounts[p->data.age - 18]++;
		p = p->next;
	}
	//������
	std::cout << std::endl;
	std::cout << "������������" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| �����С";
	std::cout << std::setw(20) <<std::left << "| ��������";
	std::cout << std::setw(20) <<std::left << "| �������          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	for (int i = 0; i <= maxAge - minAge + 1; i++) {
		if (flag == personNum)
			break;
		if (ageCounts[i] > 0) {
			std::cout << "| " << std::setw(18) <<std::left << i + 18;
			std::cout << "| " << std::setw(18) <<std::left << ageCounts[i];
			std::cout << "| " << std::setw(17) <<std::left << ageCounts[i] * 100.0 / personNum << '%';
			std::cout << "|\n";
			flag+= ageCounts[i];
		}
	}
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  �������ƣ�	countApplicationCategory����
  ���������	��
  ��   �ܣ�	ͳ�Ʊ�����Ϣ�ֲ�
  �� �� ֵ��	��
 ***************************************************************************/
void solution::countApplicationCategory()
{
	LNode* p = studentList->next;
	while (p) {
		char* category = p->data.applicationCategory;

		// Ѱ���Ƿ��Ѵ��ڸñ������͵�ͳ��
		ACC* current = categoryCounts;
		while (current != nullptr) {
			if (strcmp(category, current->category) == 0) {
				current->count++;
				break;
			}
			current = current->next;
		}

		// �ñ�������δͳ�ƹ�������µ�ͳ����
		if (current == nullptr) {
			ACC* newCount = new ACC;
			strcpy(newCount->category, category);
			newCount->count = 1;
			newCount->next = categoryCounts;
			categoryCounts = newCount;
		}
		p = p->next;
	}

	// ���ͳ�ƽ��
	std::cout << "��������ͳ��:\n";
	ACC* current = categoryCounts;
	std::cout << std::endl;
	std::cout << "������������" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| ��������";
	std::cout << std::setw(20) <<std::left << "| ��������";
	std::cout << std::setw(20) <<std::left << "| ��������          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	while (current != nullptr) {
		std::cout << "| " << std::setw(18) <<std::left << current->category;
		std::cout << "| " << std::setw(18) <<std::left << current->count;
		std::cout << "| " << std::setw(17) <<std::left << current->count * 100.0 / personNum << '%';
		std::cout << "|\n"; 
		ACC* temp = current;
		current = current->next;
		delete temp;
	}
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  �������ƣ�	statsInformation����
  ���������	��
  ��   �ܣ�	ʵ�ָ���ͳ�ƹ���
  �� �� ֵ�� �� 
 ***************************************************************************/
void solution::statsInformation()
{
	int opt_5;
	int personNum = 0;
	std::cout << "\n��ѡ����Ҫͳ�Ƶ���Ϣ����1.�������� 2.�Ա�ֲ� 3.����ֲ� 4.�������" << std::endl;
	while (1) {
		std::cin >> opt_5;
		if (std::cin.fail() || personNum < 0 || personNum > 4) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
	switch (opt_5) {
	case 1:
		/* ͳ�ƿ������� */
		personNum = listLength();
		std::cout << "��������" << personNum << "�ˡ�\n";
		break;
	case 2:
		/* ͳ���Ա�ֲ� */
		statsSexDistribution();
		break;
	case 3:
		/* ͳ������ֲ� */
		statsAge();
		break;
	case 4:
		/* ͳ�Ʊ������ֲ� */
		countApplicationCategory();
		break;
	default:
		break;
	}
}

/***************************************************************************
  �������ƣ�	createList����
  ���������	��
  ��   �ܣ�	β�巨��������
  �� �� ֵ��	��
 ***************************************************************************/
void solution::createList() {
	LNode* r = studentList;
	LNode* p;
	std::cout << "���������뿼���Ŀ��ţ��������Ա����估�������\n";
	std::cout << "ע������Ӧ��18~35֮�䣬�Ա�ֻ��Ϊ��/Ů����ͬ�������ᱻ�ϲ���Ӣ�������������»�������ȫ��\n";
	std::cout << "���磺1234567 ���� �� 20 �������ʦ\n";
	std::cout << "      2345678 ���� Ů 19 �������ʦ\n";
	std::cout << "      1 Gabrielle_Bonheur Ů 19 �������ʦ\n";
	for (int i = 0; i < personNum; ++i) {
		p = new LNode;
		while (!inputPersonInformation(p->data)) continue;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	deletRepetitiveList();
}

/***************************************************************************
  �������ƣ�	inputPersonNum����
  ���������	��
  ��   �ܣ�	����ѧ������
  �� �� ֵ��	��
 ***************************************************************************/
void solution::inputPersonNum()
{
	std::cout << "�����뿼��������";
	while (1) {
		std::cin >> personNum;
		if (std::cin.fail() || personNum < minLength || personNum > maxLength) {
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
}

/***************************************************************************
  �������ƣ�	inputPersonInformation����
  ���������	SI studentData
  ��   �ܣ�	���뿼����Ϣ
  �� �� ֵ��	true --����ɹ�
			false --����ʧ��
 ***************************************************************************/
bool solution::inputPersonInformation(SI& studentData)
{
	while (true) {
		studentData.name[maxNameLength - 1] = '\0';
		/* ����һ���ַ����洢���� */ 
		char input_line[65536] = { 0 };
		/* ��ȡ���� */
		myGetline(input_line, 65536);
		std::istringstream iss(input_line);
		iss >> studentData.examNum >> studentData.name >> studentData.sex >> studentData.age >> studentData.applicationCategory;
		/* �Ƿ����롢���������С���Ա�����/Ů*/
		if (iss.fail() || studentData.examNum <=0 ||studentData.age < minAge || studentData.age > maxAge || !((studentData.sex[0] == -59 && studentData.sex[1] == -82) ||
			(studentData.sex[0] == -60 && studentData.sex[1] == -48))||studentData.name[maxNameLength - 1]!='\0' || studentData.applicationCategory[0]=='.') {
			std::cout << "�������ݷǷ������������루��ͷ���룩\n";
			iss.str("");
			iss.clear();
			iss.ignore(65536, '\n');
			return false;
		}
		if (studentData.applicationCategory) break;  // �˳�ѭ��
	}
	return true;
}

/***************************************************************************
  �������ƣ�	inputOperationLocation����
  ���������	��
  ��   �ܣ�	������Ҫ���е�ѡ��
  �� �� ֵ��	��
 ***************************************************************************/
void solution::inputOperationLocation()
{
	while (1) {
		std::cin >> locationNum;
		if (std::cin.fail() || locationNum <= 0 || locationNum > personNum + 1) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
}

/***************************************************************************
  �������ƣ�	inputOperationNum����
  ���������	��
  ��   �ܣ�	������Ҫ���в����Ŀ���
  �� �� ֵ��	��
 ***************************************************************************/
void  solution::inputOperationNum()
{
	while (1) {
		std::cin >> operationNum;
		operationLocation = getElem(0);
		if (std::cin.fail() || !operationLocation) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
}

/***************************************************************************
  �������ƣ�	option����
  ���������	��
  ��   �ܣ�	ѡ����Ҫ���еĲ���
  �� �� ֵ��	true --����ɹ�
			false --����ʧ��
 ***************************************************************************/
bool solution::option()
{
	std::cout << std::endl << std::endl << "��ѡ����Ҫ���еĲ�����";
	while (1) {
		std::cin >> opt;
		if (std::cin.fail() || opt < 0 || opt > 5) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
	switch (opt) {
	case 0:
		return 0;
		break;
	case 1:
		std::cout << "��������Ҫ����Ŀ�����λ�ã�";
		inputOperationLocation();
		listInsert();
		deletRepetitiveList();
		output(1);
		break;
	case 2:
		std::cout << "��������Ҫɾ���Ŀ����Ŀ��ţ�";
		inputOperationNum();
		listDelete();
		output(1);
		break;
	case 3:
		std::cout << "��������Ҫ���ҵĿ����Ŀ��ţ�";
		inputOperationNum();
		if (getElem(1))
			output(0);
		break;
	case 4:
		std::cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
		inputOperationNum();
		listRevise();
		deletRepetitiveList();
		output(1);
		break;
	case 5:
		std::cout << "ͳ�ƵĿ�����Ϣ���£�\n";
		deletRepetitiveList();
		output(1);
		std::cout << "�Ƿ���Ҫ��һ��ͳ�ƾ�����Ϣ��(Y/N)";
		while (1) {
			char ch1 = _getch();
			std::cout << ch1;
			if (ch1 == 'Y' || ch1 == 'y') {
				statsInformation();
				std::cout << "�Ƿ���Ҫ��һ��ͳ�ƾ�����Ϣ��(Y/N)";
			}
			else if (ch1 == 'N' || ch1 == 'n') {
				std::cout << std::endl;
				break;
			}
			else {
				std::cout << "\n����������������������\n";
				continue;
			}
		}
		break;
	default:
		break;
	}
	personNum = listLength();
	return 1;
}

/***************************************************************************
  �������ƣ�	output����
  ���������	opt -- 0 �����Ҫ���ҵĿ�����Ϣ
				-- 1 ������п�����Ϣ
  ��   �ܣ�	���������Ϣ
  �� �� ֵ��	��
 ***************************************************************************/
void solution::output(bool opt)
{
	std::cout << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| ����";
	std::cout << std::setw(20) <<std::left << "| ����";
	std::cout << std::setw(20) <<std::left << "| �Ա�";
	std::cout << std::setw(20) <<std::left << "| ����";
	std::cout << std::setw(20) <<std::left << "| �������          |\n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
	if (opt) {
		LNode* p;
		p = studentList->next;
		while (p) {
			showData(p->data,1);
			p = p->next;
		}
	}
	else
		showData(getStudentData,1);
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
}

int main() {
	solution ERS;
	bool flag = 1;
	std::cout << "����������������������������������������������" << std::endl;
	std::cout << "��               ��������ϵͳ               ��" << std::endl;
	std::cout << "��      Examination Registration System     ��" << std::endl;
	std::cout << "����������������������������������������������" << std::endl;
	/* ��ʼ������ */
	ERS.InitList();
	/* ���뿼�������� */
	ERS.inputPersonNum();
	/* β�巨�������� */
	ERS.createList();
	/* ���ѧ����Ϣ */
	ERS.output(1);
	while (flag) {
		if (ERS.listEmpty()) {
			std::cout << "ѧ�������ѿգ������Ƿ�Ҫ�������в�����(Y/N)";
			while (true) {
				char ch1 = _getch();
				std::cout << ch1;
				if (ch1 == 'Y' || ch1 == 'y')
					break;
				else if (ch1 == 'N' || ch1 == 'n') {
					std::cout << std::endl;
					flag = 0;
					break;
				}
				else {
					std::cout << "\n����������������������\n";
					continue;
				}
			}
		}
		if (flag) {
			/* ѡ����� */
			std::cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)";
			flag = ERS.option();
		}
	}
	return 0;
}

/* ��������-��1������
2251310 ������ Ů 19 ������ʦ
2251730 ������ Ů 19 �������ʦ
2252444 ��˼Դ Ů 19 �������ʦ
2252551 �쿡�� Ů 19 �����Ӫʦ
2253893 ����� Ů 19 ������ʦ
2250693 ����� Ů 20 �������ʦ
2254282 ��Ψ�� Ů 20 �������ʦ
2251742 �ﾲ�� Ů 20 �����Ӫʦ
2251338 ������ �� 20 ������ʦ
2252956 ��Ҷ���� �� 20 �������ʦ
2253896 ���Ľ� �� 21 �������ʦ
2251321 ��κ� �� 21 �����Ӫʦ
2251948 ���� �� 21 ������ʦ
2250944 ���ֿ��� �� 21 �������ʦ
2251556 ���� �� 21 �������ʦ
2252088 ���ٽ� �� 22 �����Ӫʦ
2251324 ������ �� 22 ������ʦ
2252073 ��һͮ �� 22 �������ʦ
2253106 ���Ƴ� �� 22 �������ʦ
2253640 �ƿ��� �� 22 �����Ӫʦ
2250288 ����׿ �� 23 ������ʦ
2253226 �κ��� �� 23 �������ʦ
2252841 ����� �� 23 �������ʦ
2252700 ��һ�� �� 23 �����Ӫʦ
2250758 �ּ��� �� 23 ������ʦ
2253333 ��ĭ�� �� 24 �������ʦ
2250931 ������ �� 24 �������ʦ
2252712 ������ �� 24 �����Ӫʦ
2251648 �ſ� �� 24 ������ʦ
2254198 ������ �� 24 �������ʦ
2253537 ����Ȼ �� 25 �������ʦ
2253637 �׹��� �� 25 �����Ӫʦ
2254267 ��־Զ �� 25 ������ʦ
2253715 �¸��� �� 25 �������ʦ
2254285 ���� �� 25 �������ʦ
2151422 ���ƶ� Ů 26 �����Ӫʦ
2152140 ������ Ů 26 ������ʦ
2153085 ������ Ů 26 �������ʦ
2256223 ��ƾ� �� 26 �������ʦ
*/