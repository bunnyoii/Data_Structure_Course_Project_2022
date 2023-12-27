#pragma once
#include <iostream>
#include <climits>
const int DefaultVertices = 30;
/* ��С�� */
template<class T>
class MinHeap {
private:
	T* heap;					// ָ��������ָ��
	int capacity;				// �ѵ��������
	int heapSize;				// ��ǰ���е�Ԫ������
	// ���ظ��ڵ������
	int parent(int i) { return (i - 1) / 2; }
	// �������ӽڵ������
	int left(int i) { return (2 * i + 1); }
	// �������ӽڵ������
	int right(int i) { return (2 * i + 2); }
	// ά���ѵ�����
	void heapify(int i) {
		int l = left(i);
		int r = right(i);
		int smallest = i;

		if (l < heapSize && heap[l] < heap[i])
			smallest = l;
		if (r < heapSize && heap[r] < heap[smallest])
			smallest = r;

		if (smallest != i) {
			std::swap(heap[i], heap[smallest]);
			heapify(smallest);
		}
	}
public:
	// ���캯��
	MinHeap(int cap) {
		heapSize = 0;
		capacity = cap;
		heap = new T[cap];
	}
	// ��������
	~MinHeap() {
		delete[] heap;
	}
	// ����һ��Ԫ��
	void push(T key) {
		if (heapSize == capacity) {
			std::cout << "Heap overflow" << std::endl;
			return;
		}
		heapSize++;
		int i = heapSize - 1;
		heap[i] = key;
		// ������
		while (i != 0 && heap[parent(i)] > heap[i]) {
			std::swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}
	// �����Ƿ�Ϊ��
	bool empty() const {
		return heapSize == 0;
	}
	// ��ȡ�Ѷ�Ԫ��
	T top() {
		if (empty()) return T();
		return heap[0];
	}
	// ɾ���Ѷ�Ԫ��
	void pop() {
		if (heapSize <= 0) return;
		if (heapSize == 1) {
			heapSize--;
			return;
		}

		heap[0] = heap[heapSize - 1];
		heapSize--;
		heapify(0);
	}
	// ��ȡ�ѵĴ�С
	int size() { return heapSize;}
};

/* �ڽӱ� */
template <class T, class E>
struct Edge {
	int dest;								// �ߵ���һ����λ��
	E cost;									// ���ϵ�Ȩֵ
	Edge<T, E>* link;						// ��һ������ָ��
	Edge() {};								// ���캯��
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {}
	// �б߲��ȷ�
	bool operator !=(Edge<T, E>& R)const { return(dest != R.dest) ? true : false; }
	// ���ش��������
	bool operator >(const Edge<T, E>& R) const { return cost > R.cost; }
	// ����С�������
	bool operator <(const Edge<T, E>& R) const { return cost < R.cost; }
};

template <class T, class E>
struct Vertex {
	T data;					// ���������
	Edge<T, E>* adj;		// �������ͷָ��
};

template <class T, class E>
class MyGraphlnk {
	friend std::istream& operator>>(std::istream& in, MyGraphlnk<T, E>& G);		//����
	friend std::ostream& operator<<(std::ostream& out, MyGraphlnk<T, E>& G);		//���
protected:
	int maxVertices;							// ͼ����󶥵���
	int numEdges;								// ��ǰ����
	int numVertices;							// ��ǰ������
	int mstEdgeCount = 0;						// ����MST�бߵ�����
	Edge<T, E> mstEdges[DefaultVertices];		// MST�еı�
	Vertex<T, E>* NodeTable;					// ��������������ͷ��㣩

	// ��������vertex��ͼ�е�λ��
	int getVertexPos(const T vertex) {
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex) return i;
		return -1;
	}
public:
	const E maxWeight = 65536;					// ����������ֵ
	MyGraphlnk(int sz = DefaultVertices);
	~MyGraphlnk();
	bool GraphEmpty() const {
		return numEdges == 0;  // ���û�бߣ���ͼΪ��
	}
	bool GraphFull()const {						// �ж�ͼ����
		return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
	}
	int getVerticesNum() { return numVertices; }
	int getEdgesNum() { return numEdges; }
	T getValue(int i);							// ȡ����i��ֵ��i��������0
	E getWeight(int v1, int v2);				// ȡ��v1��v2�ϵ�Ȩֵ
	int getFirstNeighbor(int v);				// ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);			// ȡ�ڽӶ���w����һ���ڽӶ���
	bool insertVertex(const T& vertex);			// ����һ������
	bool insertEdge(int v1, int v2, E cost);	// �����(v1,v2)��Ȩ��Ϊconst
	bool removeVertex(int v);					// ɾȥ����v����ص���������
	bool removeEdge(int v1, int v2);			// ��ͼ��ɾȥ��(v1,v2)
	void printEdges()const;						// �����Ѵ��ڵ����б�
};

template<class T, class E>
MyGraphlnk<T, E>::MyGraphlnk(int sz)
{
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];		// �������������
	if (NodeTable == NULL) { std::cerr << "�洢�����\n"; exit(1); }
	for (int i = 0; i < maxVertices; i++)NodeTable[i].adj = NULL;
}

template<class T, class E>
MyGraphlnk<T, E>::~MyGraphlnk()
{
	for (int i = 0; i < numVertices; i++) {
		Edge<T, E>* p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

template<class T,class E>
int MyGraphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		if (p != NULL) return p->dest;
	}
}

template<class T, class E>
int MyGraphlnk<T, E>::getNextNeighbor(int v,int w)
{
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}

template <class T, class E>
E MyGraphlnk<T, E>::getWeight(int v1, int v2) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
		return maxWeight; // �����������Ϸ����������Ȩ�ر�ʾ�޷�����
	}

	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL) {
		if (p->dest == v2) {
			return p->cost; // �ҵ��ߣ�������Ȩ��
		}
		p = p->link;
	}

	return maxWeight; // û���ҵ��ߣ��������Ȩ�ر�ʾ�޷�����
}

template<class T, class E>
bool MyGraphlnk<T, E>::insertVertex(const T&vertex)
{
	if (numVertices == maxVertices) return false;
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

template<class T, class E>
bool MyGraphlnk<T, E>::removeVertex(int v)
{
	if (v < 0 || v >= numVertices) {
		return false; // �����Ų��Ϸ�
	}

	// �Ƴ����д�v�����ı�
	Edge<T, E>* p = NodeTable[v].adj;
	while (p != NULL) {
		Edge<T, E>* temp = p;
		p = p->link;
		delete temp;
		numEdges--;
	}

	// �Ƴ�����ָ��v�ı�
	for (int i = 0; i < numVertices; i++) {
		if (i != v) {
			Edge<T, E>* pre = NULL;
			Edge<T, E>* q = NodeTable[i].adj;
			while (q != NULL) {
				if (q->dest == v) {
					if (pre == NULL) {
						NodeTable[i].adj = q->link;
					}
					else {
						pre->link = q->link;
					}
					Edge<T, E>* temp = q;
					q = q->link;
					delete temp;
					numEdges--;
				}
				else {
					pre = q;
					q = q->link;
				}
			}
		}
	}

	// �������ɾ�����㣬����Ҫ�ƶ������б��еĶ���
	// �������ڽӱ�ָ��
	// ע�⣺����ʵ�ַ�ʽ��ı��������������
	NodeTable[v] = NodeTable[numVertices - 1];
	numVertices--;

	return true;
}

template <class T, class E>
T MyGraphlnk<T, E>::getValue(int i) {
	if (i >= 0 && i < numVertices) {
		return NodeTable[i].data; // ��������i��Ӧ�����ֵ
	}
	else {
		// ���������Ч�������׳��쳣�����߷���һ���ض���ֵ
		// ������� T ������Ĭ�Ϲ��캯��
		return T(); // ���� T ���͵�Ĭ��ֵ
	}
}

template <class T, class E>
bool MyGraphlnk<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
		return false; // �����������Ϸ�
	}

	// �����Ƿ��Ѵ���
	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL) {
		if (p->dest == v2) {
			return false; // ���Ѵ���
		}
		p = p->link;
	}

	// �����������±�
	Edge<T, E>* newEdge = new Edge<T, E>(v2, cost);
	newEdge->link = NodeTable[v1].adj; // �±�ָ��ǰ������ڽ�����ͷ��
	NodeTable[v1].adj = newEdge;       // �����ڽ�����ͷ��Ϊ�±�

	numEdges++; // ���±ߵ�����
	return true;
}

template <class T, class E>
bool MyGraphlnk<T, E>::removeEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
		return false; // �����������Ϸ�
	}

	Edge<T, E>* pre = NULL, * p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2) {
		pre = p;
		p = p->link;
	}

	if (p == NULL) {
		return false; // û���ҵ���
	}

	// �Ƴ���
	if (pre == NULL) {
		// �����ڽ������ͷ��
		NodeTable[v1].adj = p->link;
	}
	else {
		// �����ڽ�������м��β��
		pre->link = p->link;
	}

	delete p; // �ͷű�ռ�õ��ڴ�
	numEdges--; // ���±ߵ�����
	return true;
}

// �������������
template <class T, class E>
std::istream& operator>>(std::istream& in, MyGraphlnk<T, E>& G) {
	int numVertices, numEdges;
	in >> numVertices >> numEdges;

	T vertex;
	for (int i = 0; i < numVertices; i++) {
		in >> vertex;
		G.insertVertex(vertex);
	}

	int v1, v2;
	E weight;
	for (int j = 0; j < numEdges; j++) {
		in >> v1 >> v2 >> weight;
		G.insertEdge(v1, v2, weight);
	}

	return in;
}

// ������������
template <class T, class E>
std::ostream& operator<<(std::ostream& out, MyGraphlnk<T, E>& G) {
	out << "Vertices: " << G.getVerticesNum() << ", Edges: " << G.getEdgesNum() << std::endl;

	for (int i = 0; i < G.getVerticesNum(); i++) {
		out << "Vertex " << i << " (" << G.getValue(i) << "): ";
		Edge<T, E>* p = G.NodeTable[i].adj;
		while (p != NULL) {
			out << "-> " << p->dest << " (Cost: " << p->cost << ") ";
			p = p->link;
		}
		out << std::endl;
	}

	return out;
}

template <class T, class E>
void MyGraphlnk<T, E>::printEdges() const {
	for (int i = 0; i < numVertices; i++) {        // ����ÿ������
		Edge<T, E>* p = NodeTable[i].adj;          // ��ȡ����i���ڽ�����
		while (p != NULL) {                        // ��������
			std::cout << "(" << NodeTable[i].data << ", " << NodeTable[p->dest].data << ", " << p->cost << ")" << std::endl;
			p = p->link;                           // ������һ����
		}
	}
}