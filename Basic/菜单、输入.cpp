#include <iostream>

#define MAX_SIZE 100
using namespace std;
int main()
{
	int inputNum = 0;
	std::cout << "···················\n";
	std::cout << "·          勇闯迷宫游戏            ·\n";
	std::cout << "·      Maze Adeventure Game        ·\n";
	std::cout << "···················\n";
	std::cout << "---------------游戏开始---------------\n";
	while (1) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum <= 0 || inputNum > MAX_SIZE) {
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