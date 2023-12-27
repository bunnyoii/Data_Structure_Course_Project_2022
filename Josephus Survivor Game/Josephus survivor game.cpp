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
		std::cout << "          ···················\n";
		std::cout << "          ·       约瑟夫生者死者游戏         ·\n";
		std::cout << "          ·      Josephus     Problem        ·\n";
		std::cout << "          ···················\n";
		std::cout << "游戏规则 : 现有N人围成一圈，从第S个人开始依次报数，报M的人出局，\n";
		std::cout << "	   再由下一人开始报数，如此循环，直到剩下K个人为止。\n";
		std::cout << "--------------------------游戏开始--------------------------\n";
		std::cout << std::setw(30) << std::left << "请输入总人数N(1~2147483647) : ";
		Input(PersonNum, 0);
		std::cout << std::setw(30) << std::left << "请输入游戏开始的位置S(1~N) : ";
		Input(StartLocation, 1);
		std::cout << std::setw(30) << std::left << "请输入死亡数字M(1~N) : ";
		Input(DeathNum, 1);
		std::cout << std::setw(30) << std::left << "请剩余生者人数K(1~N) : ";
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
	}

	/*
	* Function name : OutputDeathPerson
	* Function features : Output the location of the deceased
	* Input parameters : int num, int Dead
	* Return value : None
	*/
	void OutputDeathPerson(int num, int Dead)
	{
		std::cout << "第" << std::setw(2) << num;
		std::cout << std::setw(26) << std::left << "个死者的位置是 : ";
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
		std::cout << std::setw(16) << std::left << "最后剩下：" << SurvivalPerson << "人\n";
		std::cout << "剩余生者位置为：\n      ";
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
			std::cout << "链表为空，没有生者。\n";
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
				p = p->link; // 移动 p 到下一个节点
				q->link = p; // 删除节点 p
				JosephusList.setHead(p);
				OutputDeathPerson(count, to_delete->data);
				delete to_delete; // 释放被删除的节点
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
				// 如果链表为空，将新结点作为头结点
				JosephusList.setHead(newNode);
				JosephusList.getHead()->link = JosephusList.getHead();
			}
			else
			{
				// 否则将新结点插入到链表尾部
				newNode->link = JosephusList.getHead()->link;
				JosephusList.getHead()->link = newNode;
				JosephusList.setHead(newNode);
			}
		}
	}
	void Exit() {
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
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