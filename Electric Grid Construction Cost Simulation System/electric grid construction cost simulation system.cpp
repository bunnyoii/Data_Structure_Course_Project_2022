#include <iostream>
#include "Graph.h"

#define MAX_SIZE 100

template <class T, class E>
struct MSTEdge {
	int source;  // �ߵ����
	int dest;    // �ߵ��յ�
	E cost;      // �ߵ�Ȩֵ

	// Ĭ�Ϲ��캯��
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
	std::cout << "�����������...\n";

	// ������뻺����
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// �ȴ��û�����
	std::cin.get();
}
void graphTree::prim(int startVertex)
{
	int n = getVerticesNum();						// ��ȡ������
	MinHeap<Edge<char,int>> heap(n * (n - 1) / 2);		// ���������µı���
	bool visited[DefaultVertices] = { false };		// �̶���С�ķ��ʱ������
	// ȷ��������ͼ��ʵ�ʶ�����
	if (n > DefaultVertices) {
		std::cerr << "Error: Number of vertices exceeds MAX_VERTICES" << std::endl;
		return;
	}
	// ����ʼ���㿪ʼ
	visited[startVertex] = true;
	int currentVertex = startVertex; // ��ʼ����ǰ����Ϊ��ʼ����
	Edge<char, int>* edge = NodeTable[startVertex].adj;
	while (edge != NULL) {
		heap.push(*edge);
		edge = edge->link;
	}
	// ������С������
	while (!heap.empty() && mstEdgeCount < n - 1) {
		Edge<char, int> minEdge = heap.top();
		heap.pop();

		int dest = minEdge.dest;
		if (visited[dest]) continue;  // ����Ѿ����ʹ�������

		visited[dest] = true;
		// ��ӱߵ� MST������¼�����յ�
		mstEdges[mstEdgeCount++] = MSTEdge<char, int>(currentVertex, minEdge.dest, minEdge.cost);

		currentVertex = dest; // ���µ�ǰ����Ϊ�����ߵ�Ŀ�ĵ�

		edge = NodeTable[dest].adj;
		while (edge != NULL) {
			if (!visited[edge->dest]) heap.push(*edge);
			edge = edge->link;
		}
	}
}

void graphTree::printMST()
{
	std::cout << "��С�������Ķ��㼰��Ϊ��" << std::endl;
	for (int i = 0; i < mstEdgeCount; i++) {
		char src = getValue(mstEdges[i].source);
		char dst = getValue(mstEdges[i].dest);
		std::cout << src << " - ( " << mstEdges[i].cost << " ) -> " << dst << std::endl;
	}
}

// ��ʾ�˵�
void graphTree::menu()
{
	std::cout << "������������������������������������������������������������\n";
	std::cout << "��                   �������ģ��ϵͳ                     ��\n";
	std::cout << "��   Electric Grid Construction Cost Simulation System    ��\n";
	std::cout << "������������������������������������������������������������\n\n";
	std::cout << "===========================================================\n";
	std::cout << "*                    ��ѡ��Ҫִ�еĲ���                   *\n";
	std::cout << "*                    A --- ������������                   *\n";
	std::cout << "*                    B --- ��ӵ����ı�                   *\n";
	std::cout << "*                    C --- ������С������                 *\n";
	std::cout << "*                    D --- ��ʾ��С������                 *\n";
	std::cout << "*                    E --- �˳�����                       *\n";
	std::cout << "===========================================================\n";
}

// ѡ�����
int graphTree::operation()
{
	char input;
	bool IsExit = 1;
	while (IsExit) {
		while (true) {
			std::cout << "\n** ע���������ַ����Ե�һ���ַ�Ϊ׼ **\n";
			std::cout << ">>>��ѡ��Ҫִ�еĲ�����";
			std::cin >> input;
			// ��������Ƿ�Ϊ��Ч�ַ�
			if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
				break;
			}
			else {
				std::cout << "��Ч�ַ������������룡" << std::endl;
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
			std::cout << "���ʽ����������˳���\n";
			Exit();
			IsExit = 0;
			break;
		}
	}
	return IsExit;
}

// ��������
void graphTree::createVertex()
{
	std::cout << ">>>�����붥�������";
	int VertexNum = 0;
	char InputName[DefaultVertices];
	char VertexName[DefaultVertices];
	while (true) {
		std::cin >> VertexNum;
		if (std::cin.fail() || VertexNum <= 0 || VertexNum > DefaultVertices) {
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
	std::cout << "\n**  ע�⣺Ϊ�˷������ÿ������������һ���ַ���ɣ����Ϊ��ĸ  **\n";
	std::cout << ">>>�������������������ƣ�";
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

// ��ӱ�
void graphTree::addEdge()
{
	int maxE = maxEdge(getVerticesNum());
	char VertexName[2];
	int VertexIndex[2];
	int edgeWeight = 0;
	bool end = 1;
	std::cout << "\n** ע�⣺1.�������еĶ������������������"<< maxE <<"���ߡ�       **\n";
	std::cout << "**       2.����E������ֹ���룬����Ĭ�ϳ�������ֱ�������� **\n";
	std::cout << "**       3.������������ڣ��������ֱ�ʾ��              **\n\n";
	for (int i = 0; i < maxE; ++i) {
		std::cout << ">>>�������������㼰�ߣ�";
		// �����󶥵�
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
				std::cout << "�ö��㲻���ڣ����������룡\n";
		}
		if (end == 0)
			break;
		// �����Ҷ���
		while (true) {
			std::cin >> VertexName[1];
			VertexIndex[1] = getVertexPos(VertexName[1]);
			if (VertexIndex[1] != -1)
				break;
			else
				std::cout << "�ö��㲻���ڣ����������룡\n";
		}
		// �����
		while (true) {
			std::cin >> edgeWeight;
			if (std::cin.fail() || edgeWeight <= 0) {
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
		if (!insertEdge(VertexIndex[0], VertexIndex[1], edgeWeight))
			std::cout << "�ñ��Ѵ��ڣ����������룡\n";
	}
	std::cout << std::endl;
	std::cout << "��ͼ�����б����£�\n";
	printEdges();
}

// ������С������
void graphTree::constructTree()
{
	char inputVertex;
	int startVertex;
	std::cout << ">>>��������ʼ���㣺";
	while (true) {
		std::cin >> inputVertex;
		startVertex = getVertexPos(inputVertex);
		if (startVertex != -1)
			break;
		else
			std::cout << "�ö��㲻���ڣ����������룡\n";
	}
	prim(startVertex);
	std::cout << "����Prim��С��������\n";
}


int main() {
	bool loop = 1;
	GT Solution;
	Solution.menu();
	while (loop) { loop = Solution.operation(); }
	return 0;
}

