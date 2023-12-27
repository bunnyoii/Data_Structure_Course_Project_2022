#include <iostream>
#include <iomanip>
#include "CircList.h"
const int maxPersonNum = 2147483647;

template <typename Type>
class Josephussolution {
private:
	CircList<Type> JosephusList;
	int PersonNum;
	int StartLocation;
	int DeathNum;
	int SurvivalPerson;
public:
	Josephussolution()
	{
		PersonNum = 0;
		StartLocation = 0;
		DeathNum = 0;
		SurvivalPerson = 0;
	}

	/*
	* Function name : menu
	* Function features : Output the interface
	* Input parameters : None
	* Return value : None
	*/
	void menu() {
		std::cout << "          ��������������������������������������\n";
		std::cout << "          ��       Լɪ������������Ϸ         ��\n";
		std::cout << "          ��      Josephus     Problem        ��\n";
		std::cout << "          ��������������������������������������\n";
		std::cout << "��Ϸ���� : ����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�\n";
		std::cout << "	   ������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��\n";
		std::cout << "--------------------------��Ϸ��ʼ--------------------------\n";
		std::cout << std::setw(30) << std::left << "������������N(1~2147483647) : ";
		Input(PersonNum, 0);
		std::cout << std::setw(30) << std::left << "��������Ϸ��ʼ��λ��S(1~N) : ";
		Input(StartLocation, 1);
		std::cout << std::setw(30) << std::left << "��������������M(1~N) : ";
		Input(DeathNum, 1);
		std::cout << std::setw(30) << std::left << "��ʣ����������K(1~N) : ";
		Input(SurvivalPerson, 1);
	}

	/*
	* Function name : Input
	* Function features : Input Relevant Parameters
	* Input parameters : int& inputNum, bool opt
	* Return value : None
	*/
	void Input(int& inputNum, bool opt) {
		int MaxNum = 0;
		if (!opt)
			MaxNum = maxPersonNum;
		else
			MaxNum = PersonNum;
		while (1) {
			std::cin >> inputNum;
			if (std::cin.fail() || inputNum <= 0 || inputNum > MaxNum) {
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

	/*
	* Function name : OutputDeathPerson
	* Function features : Output the location of the deceased
	* Input parameters : int num, int Dead
	* Return value : None
	*/
	void OutputDeathPerson(int num, int Dead)
	{
		std::cout << "��" << std::setw(2) << num;
		std::cout << std::setw(26) << std::left << "�����ߵ�λ���� : ";
		std::cout << Dead << "\n";
	}

	/*
	* Function name : OutputSurvivalPerson
	* Function features : Output the location of the living
	* Input parameters : None
	* Return value : None
	*/
	void OutputSurvivalPerson()
	{
		int cnt = 0;
		int MinValue = JosephusList.FindMinValue(JosephusList);
		CircLinkNode<Type>* p;
		std::cout << std::setw(16) << std::left << "���ʣ�£�" << SurvivalPerson << "��\n";
		std::cout << "ʣ������λ��Ϊ��\n      ";
		if (!JosephusList.IsEmpty()) {
			if (JosephusList.Length() == 1)
				p = JosephusList.getHead();
			else
				p = JosephusList.search(MinValue);
			while (cnt < SurvivalPerson) {
				std::cout << std::setw(7) << p->data;
				cnt++;
				p = p->link;
				if (cnt % 7 == 0)
					std::cout << "\n      ";
			}
		}
		else {
			std::cout << "����Ϊ�գ�û�����ߡ�\n";
		}
	}

	/*
	* Function name : JosephusEliminate
	* Function features : Handle the Joseph Ring
	* Input parameters : None
	* Return value : None
	*/
	void JosephusEliminate()
	{
		int num = 2;
		int count = 1;
		CircLinkNode<Type>* p = JosephusList.Locate(StartLocation);
		CircLinkNode<Type>* q = JosephusList.Locate(StartLocation);
		while (q->link != p) {
			q = q->link;
		}
		while (count <= PersonNum - SurvivalPerson)
		{
			if ((num - 1) % DeathNum != 0 ||num - 1 == 0) {
				q = p;
				p = p->link;
			}
			else {
				CircLinkNode<Type>* to_delete = p;
				p = p->link; // �ƶ� p ����һ���ڵ�
				q->link = p; // ɾ���ڵ� p
				JosephusList.setHead(p);
				OutputDeathPerson(count, to_delete->data);
				delete to_delete; // �ͷű�ɾ���Ľڵ�
				count++;
			}
			num++;
		}
		OutputSurvivalPerson();
	}

	/*
	* Function name : CreatCircList
	* Function features : Tail Interpolation Creates a Linked List
	* Input parameters : None
	* Return value : None
	*/
	void CreatCircList()
	{
		for (int i = 1; i <= PersonNum; i++) {
			CircLinkNode<Type>* newNode = new CircLinkNode<Type>(i);
			if (!JosephusList.getHead()) {
				// �������Ϊ�գ����½����Ϊͷ���
				JosephusList.setHead(newNode);
				JosephusList.getHead()->link = JosephusList.getHead();
			}
			else
			{
				// �����½����뵽����β��
				newNode->link = JosephusList.getHead()->link;
				JosephusList.getHead()->link = newNode;
				JosephusList.setHead(newNode);
			}
		}
	}
	void Exit() {
		std::cout << "�����������...\n";
		// ������뻺����
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// �ȴ��û�����
		std::cin.get();
	}
};

int main() {
	Josephussolution<int> JSG;
	JSG.menu();
	JSG.CreatCircList();
	JSG.JosephusEliminate();
	JSG.Exit();
	return 0;
}