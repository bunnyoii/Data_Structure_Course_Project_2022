#include <iostream>
#include "Graph.h"

#define MAX_SIZE 100

template <class T, class E>
struct MSTEdge {
	int source;  // 边的起点
	int dest;    // 边的终点
	E cost;      // 边的权值

	// 默认构造函数
	MSTEdge() : source(-1), dest(-1), cost(E()) {}
	MSTEdge(int s, int d, E c) : source(s), dest(d), cost(c) {}
};

typedef class graphTree :public MyGraphlnk<char,int> {
private:
	MSTEdge<char, int> mstEdges[DefaultVertices];
	int mstEdgeCount = 0;
public:
	void menu();
	int operation();
	void createVertex();
	void addEdge();
	void constructTree();
	int maxEdge(const int vertex) { return vertex * (vertex - 1) / 2; }
	void prim(int startVertex);
	void printMST();
	void Exit();
}GT;

void graphTree::Exit() {
	std::cout << "按任意键继续...\n";

	// 清除输入缓冲区
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// 等待用户按键
	std::cin.get();
}
void graphTree::prim(int startVertex)
{
	int n = getVerticesNum();						// 获取顶点数
	MinHeap<Edge<char,int>> heap(n * (n - 1) / 2);		// 假设最坏情况下的边数
	bool visited[DefaultVertices] = { false };		// 固定大小的访问标记数组
	// 确保不超出图的实际顶点数
	if (n > DefaultVertices) {
		std::cerr << "Error: Number of vertices exceeds MAX_VERTICES" << std::endl;
		return;
	}
	// 从起始顶点开始
	visited[startVertex] = true;
	int currentVertex = startVertex; // 初始化当前顶点为起始顶点
	Edge<char, int>* edge = NodeTable[startVertex].adj;
	while (edge != NULL) {
		heap.push(*edge);
		edge = edge->link;
	}
	// 构建最小生成树
	while (!heap.empty() && mstEdgeCount < n - 1) {
		Edge<char, int> minEdge = heap.top();
		heap.pop();

		int dest = minEdge.dest;
		if (visited[dest]) continue;  // 如果已经访问过，跳过

		visited[dest] = true;
		// 添加边到 MST，并记录起点和终点
		mstEdges[mstEdgeCount++] = MSTEdge<char, int>(currentVertex, minEdge.dest, minEdge.cost);

		currentVertex = dest; // 更新当前顶点为这条边的目的地

		edge = NodeTable[dest].adj;
		while (edge != NULL) {
			if (!visited[edge->dest]) heap.push(*edge);
			edge = edge->link;
		}
	}
}

void graphTree::printMST()
{
	std::cout << "最小生成树的顶点及边为：" << std::endl;
	for (int i = 0; i < mstEdgeCount; i++) {
		char src = getValue(mstEdges[i].source);
		char dst = getValue(mstEdges[i].dest);
		std::cout << src << " - ( " << mstEdges[i].cost << " ) -> " << dst << std::endl;
	}
}

// 显示菜单
void graphTree::menu()
{
	std::cout << "······························\n";
	std::cout << "·                   电网造价模拟系统                     ·\n";
	std::cout << "·   Electric Grid Construction Cost Simulation System    ·\n";
	std::cout << "······························\n\n";
	std::cout << "===========================================================\n";
	std::cout << "*                    请选择要执行的操作                   *\n";
	std::cout << "*                    A --- 创建电网顶点                   *\n";
	std::cout << "*                    B --- 添加电网的边                   *\n";
	std::cout << "*                    C --- 构造最小生成树                 *\n";
	std::cout << "*                    D --- 显示最小生成树                 *\n";
	std::cout << "*                    E --- 退出程序                       *\n";
	std::cout << "===========================================================\n";
}

// 选择操作
int graphTree::operation()
{
	char input;
	bool IsExit = 1;
	while (IsExit) {
		while (true) {
			std::cout << "\n** 注：输入多个字符，以第一个字符为准 **\n";
			std::cout << ">>>请选择要执行的操作：";
			std::cin >> input;
			// 检查输入是否为有效字符
			if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
				break;
			}
			else {
				std::cout << "无效字符，请重新输入！" << std::endl;
			}
		}
		switch (input) {
		case 'A':		
			createVertex();
			break;
		case 'B':
			addEdge();
			break;
		case 'C':
			constructTree();
			break;
		case 'D':
			printMST();
			break;
		case 'E':
			std::cout << "访问结束，程序退出。\n";
			Exit();
			IsExit = 0;
			break;
		}
	}
	return IsExit;
}

// 创建顶点
void graphTree::createVertex()
{
	std::cout << ">>>请输入顶点个数：";
	int VertexNum = 0;
	char InputName[DefaultVertices];
	char VertexName[DefaultVertices];
	while (true) {
		std::cin >> VertexNum;
		if (std::cin.fail() || VertexNum <= 0 || VertexNum > DefaultVertices) {
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
	std::cout << "\n**  注意：为了方便管理，每个顶点名称由一个字符组成，最好为字母  **\n";
	std::cout << ">>>请依次输入各顶点的名称：";
	std::cin.getline(InputName, MAX_SIZE);
	for (int i = 0,j = 0; i < InputName[i] != '\0'; i++,j++) {
		if (InputName[i] != ' ')
			VertexName[j] = InputName[i];
		else
			j--;
	}
	for (int i = 0; i < VertexNum; i++)
		insertVertex(VertexName[i]);
}

// 添加边
void graphTree::addEdge()
{
	int maxE = maxEdge(getVerticesNum());
	char VertexName[2];
	int VertexIndex[2];
	int edgeWeight = 0;
	bool end = 1;
	std::cout << "\n** 注意：1.根据已有的顶点个数，最多可以生成"<< maxE <<"条边。       **\n";
	std::cout << "**       2.输入E可以终止输入，否则默认持续生成直至结束。 **\n";
	std::cout << "**       3.顶点名称需存在，边由数字表示。              **\n\n";
	for (int i = 0; i < maxE; ++i) {
		std::cout << ">>>请输入两个顶点及边：";
		// 输入左顶点
		while (true) {
			std::cin >> VertexName[0];
			VertexIndex[0] = getVertexPos(VertexName[0]);
			if (VertexIndex[0] != -1)
				break;
			else if (VertexName[0] == 'E') {
				end = 0;
				break;
			}
			else
				std::cout << "该顶点不存在，请重新输入！\n";
		}
		if (end == 0)
			break;
		// 输入右顶点
		while (true) {
			std::cin >> VertexName[1];
			VertexIndex[1] = getVertexPos(VertexName[1]);
			if (VertexIndex[1] != -1)
				break;
			else
				std::cout << "该顶点不存在，请重新输入！\n";
		}
		// 输入边
		while (true) {
			std::cin >> edgeWeight;
			if (std::cin.fail() || edgeWeight <= 0) {
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
		if (!insertEdge(VertexIndex[0], VertexIndex[1], edgeWeight))
			std::cout << "该边已存在，请重新输入！\n";
	}
	std::cout << std::endl;
	std::cout << "该图的所有边如下：\n";
	printEdges();
}

// 构造最小生成树
void graphTree::constructTree()
{
	char inputVertex;
	int startVertex;
	std::cout << ">>>请输入起始顶点：";
	while (true) {
		std::cin >> inputVertex;
		startVertex = getVertexPos(inputVertex);
		if (startVertex != -1)
			break;
		else
			std::cout << "该顶点不存在，请重新输入！\n";
	}
	prim(startVertex);
	std::cout << "生成Prim最小生成树！\n";
}


int main() {
	bool loop = 1;
	GT Solution;
	Solution.menu();
	while (loop) { loop = Solution.operation(); }
	return 0;
}

