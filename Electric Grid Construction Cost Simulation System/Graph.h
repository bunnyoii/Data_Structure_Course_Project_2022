#pragma once
#include <iostream>
#include <climits>
const int DefaultVertices = 30;
/* 最小堆 */
template<class T>
class MinHeap {
private:
	T* heap;					// 指向堆数组的指针
	int capacity;				// 堆的最大容量
	int heapSize;				// 当前堆中的元素数量
	// 返回父节点的索引
	int parent(int i) { return (i - 1) / 2; }
	// 返回左子节点的索引
	int left(int i) { return (2 * i + 1); }
	// 返回右子节点的索引
	int right(int i) { return (2 * i + 2); }
	// 维护堆的性质
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
	// 构造函数
	MinHeap(int cap) {
		heapSize = 0;
		capacity = cap;
		heap = new T[cap];
	}
	// 析构函数
	~MinHeap() {
		delete[] heap;
	}
	// 插入一个元素
	void push(T key) {
		if (heapSize == capacity) {
			std::cout << "Heap overflow" << std::endl;
			return;
		}
		heapSize++;
		int i = heapSize - 1;
		heap[i] = key;
		// 调整堆
		while (i != 0 && heap[parent(i)] > heap[i]) {
			std::swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}
	// 检查堆是否为空
	bool empty() const {
		return heapSize == 0;
	}
	// 提取堆顶元素
	T top() {
		if (empty()) return T();
		return heap[0];
	}
	// 删除堆顶元素
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
	// 获取堆的大小
	int size() { return heapSize;}
};

/* 邻接表 */
template <class T, class E>
struct Edge {
	int dest;								// 边的另一顶点位置
	E cost;									// 边上的权值
	Edge<T, E>* link;						// 下一条边链指针
	Edge() {};								// 构造函数
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {}
	// 判边不等否
	bool operator !=(Edge<T, E>& R)const { return(dest != R.dest) ? true : false; }
	// 重载大于运算符
	bool operator >(const Edge<T, E>& R) const { return cost > R.cost; }
	// 重载小于运算符
	bool operator <(const Edge<T, E>& R) const { return cost < R.cost; }
};

template <class T, class E>
struct Vertex {
	T data;					// 顶点的名字
	Edge<T, E>* adj;		// 边链表的头指针
};

template <class T, class E>
class MyGraphlnk {
	friend std::istream& operator>>(std::istream& in, MyGraphlnk<T, E>& G);		//输入
	friend std::ostream& operator<<(std::ostream& out, MyGraphlnk<T, E>& G);		//输出
protected:
	int maxVertices;							// 图中最大顶点数
	int numEdges;								// 当前边数
	int numVertices;							// 当前顶点数
	int mstEdgeCount = 0;						// 跟踪MST中边的数量
	Edge<T, E> mstEdges[DefaultVertices];		// MST中的边
	Vertex<T, E>* NodeTable;					// 顶点表（各边链表的头结点）

	// 给出顶点vertex在图中的位置
	int getVertexPos(const T vertex) {
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex) return i;
		return -1;
	}
public:
	const E maxWeight = 65536;					// 代表无穷大的值
	MyGraphlnk(int sz = DefaultVertices);
	~MyGraphlnk();
	bool GraphEmpty() const {
		return numEdges == 0;  // 如果没有边，则图为空
	}
	bool GraphFull()const {						// 判断图满否
		return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
	}
	int getVerticesNum() { return numVertices; }
	int getEdgesNum() { return numEdges; }
	T getValue(int i);							// 取顶点i的值，i不合理返回0
	E getWeight(int v1, int v2);				// 取边v1、v2上的权值
	int getFirstNeighbor(int v);				// 取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w);			// 取邻接顶点w的下一个邻接顶点
	bool insertVertex(const T& vertex);			// 插入一个顶点
	bool insertEdge(int v1, int v2, E cost);	// 插入边(v1,v2)，权重为const
	bool removeVertex(int v);					// 删去顶点v和相关的所有联边
	bool removeEdge(int v1, int v2);			// 在图中删去边(v1,v2)
	void printEdges()const;						// 访问已存在的所有边
};

template<class T, class E>
MyGraphlnk<T, E>::MyGraphlnk(int sz)
{
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];		// 创建顶点表数组
	if (NodeTable == NULL) { std::cerr << "存储分配错！\n"; exit(1); }
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
		return maxWeight; // 顶点索引不合法，返回最大权重表示无法访问
	}

	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL) {
		if (p->dest == v2) {
			return p->cost; // 找到边，返回其权重
		}
		p = p->link;
	}

	return maxWeight; // 没有找到边，返回最大权重表示无法访问
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
		return false; // 顶点编号不合法
	}

	// 移除所有从v出发的边
	Edge<T, E>* p = NodeTable[v].adj;
	while (p != NULL) {
		Edge<T, E>* temp = p;
		p = p->link;
		delete temp;
		numEdges--;
	}

	// 移除所有指向v的边
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

	// 如果允许删除顶点，则需要移动顶点列表中的顶点
	// 并更新邻接表指针
	// 注意：这种实现方式会改变其他顶点的索引
	NodeTable[v] = NodeTable[numVertices - 1];
	numVertices--;

	return true;
}

template <class T, class E>
T MyGraphlnk<T, E>::getValue(int i) {
	if (i >= 0 && i < numVertices) {
		return NodeTable[i].data; // 返回索引i对应顶点的值
	}
	else {
		// 如果索引无效，可以抛出异常，或者返回一个特定的值
		// 这里假设 T 类型有默认构造函数
		return T(); // 返回 T 类型的默认值
	}
}

template <class T, class E>
bool MyGraphlnk<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
		return false; // 顶点索引不合法
	}

	// 检查边是否已存在
	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL) {
		if (p->dest == v2) {
			return false; // 边已存在
		}
		p = p->link;
	}

	// 创建并插入新边
	Edge<T, E>* newEdge = new Edge<T, E>(v2, cost);
	newEdge->link = NodeTable[v1].adj; // 新边指向当前顶点的邻接链表头部
	NodeTable[v1].adj = newEdge;       // 更新邻接链表头部为新边

	numEdges++; // 更新边的数量
	return true;
}

template <class T, class E>
bool MyGraphlnk<T, E>::removeEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
		return false; // 顶点索引不合法
	}

	Edge<T, E>* pre = NULL, * p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2) {
		pre = p;
		p = p->link;
	}

	if (p == NULL) {
		return false; // 没有找到边
	}

	// 移除边
	if (pre == NULL) {
		// 边在邻接链表的头部
		NodeTable[v1].adj = p->link;
	}
	else {
		// 边在邻接链表的中间或尾部
		pre->link = p->link;
	}

	delete p; // 释放边占用的内存
	numEdges--; // 更新边的数量
	return true;
}

// 输入运算符重载
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

// 输出运算符重载
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
	for (int i = 0; i < numVertices; i++) {        // 遍历每个顶点
		Edge<T, E>* p = NodeTable[i].adj;          // 获取顶点i的邻接链表
		while (p != NULL) {                        // 遍历链表
			std::cout << "(" << NodeTable[i].data << ", " << NodeTable[p->dest].data << ", " << p->cost << ")" << std::endl;
			p = p->link;                           // 移至下一条边
		}
	}
}