#pragma once
#include <iostream>
using namespace std;
const int defaultSize = 65536;
/* 操作算法中用到的预定义常量和类型 */
// 函数结果状态代码
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

typedef int DataType;
template<typename Type>
class TreeNode;
class BinarySortTree;

// 定义栈存储表达式
template<class Type>
struct StackNode {
	Type data;
	StackNode<Type>* link;
	StackNode(Type d = 0, StackNode<Type>* l = nullptr) :data(d), link(l) {}
};

template<class Type>
class Stack {
private:
	StackNode<Type>* top;
	int size;
public:
	Stack() :top(NULL) ,size(0){}					//构造函数
	~Stack();										//析构函数
	void Push(const Type& item);					//进栈
	Type Pop();										//出栈
	Type GetTop();									//取栈顶元素
	void MakeEmpty();								//置空栈
	int IsEmpty()const { return top == NULL; }		//判栈空否
	void OverturnStack();							//翻转栈
	int GetSize() const { return size; }			// 获取栈的元素总数
};

template<class Type>
Stack<Type>::~Stack()
{
	StackNode<Type>* p;
	while (top != NULL) { p = top; top = top->link; delete p; }
}

template<class Type>
void Stack<Type>::Push(const Type& item)
{
	top = new StackNode<Type>(item, top);
	size++;
	//新结点链入top之前，并成为新栈顶
}

template<class Type>
Type Stack<Type>::Pop()
{
	if (IsEmpty()) { return ERROR;}
	StackNode<Type>* p = top;
	Type retvalue = p->data;	//暂存栈顶数据
	top = top->link;			//修改栈顶指针
	delete p;
	size--;
	return retvalue;			//释放，返回数据
}

template<class Type>
Type Stack<Type>::GetTop()
{
	if (IsEmpty()) { return ERROR; }
	return top->data;
}

template<class Type>
void Stack<Type>::MakeEmpty()
{
	StackNode<Type>* p;
	while (top != NULL) { p = top; top = top->link; delete p; }
}

template <class Type>
void Stack<Type>::OverturnStack() {
	if (top == nullptr || top->link == nullptr) {
		// The stack is empty or contains only one element; no need to overturn.
		return;
	}
	StackNode<Type>* previous = nullptr;
	StackNode<Type>* current = top;
	StackNode<Type>* next = nullptr;

	while (current != nullptr) {
		next = current->link;
		current->link = previous;
		previous = current;
		current = next;
	}

	top = previous;  // Update the top to the new top element.;;
}

// 定义队列便于进行层次序遍历
// 链表节点定义
template<typename Type>
class QueueNode {
public:
	TreeNode<Type>* data;
	QueueNode<Type>* next;
	QueueNode(TreeNode<Type>* node) : data(node), next(NULL) {}
};

// 链队定义
template<typename Type>
class LinkedQueue {
private:
	QueueNode<Type>* front;   // 队列头指针
	QueueNode<Type>* rear;    // 队列尾指针

public:
	LinkedQueue() : front(NULL), rear(NULL) {}
	~LinkedQueue() {
		while (!isEmpty()) { dequeue(); }
	}
	bool isEmpty() const { return front == NULL; }
	void enqueue(TreeNode<Type>* node) {
		QueueNode<Type>* newNode = new QueueNode<Type>(node);
		if (rear == NULL) {
			front = rear = newNode;
		}
		else {
			rear->next = newNode;
			rear = newNode;
		}
	}
	TreeNode<Type>* dequeue() {
		if (isEmpty()) {
			return NULL;
		}
		QueueNode<Type>* temp = front;
		TreeNode<Type>* node = front->data;
		front = front->next;
		if (front == NULL) {
			rear = NULL;
		}
		delete temp;
		return node;
	}
	TreeNode<Type>* getFront() const {
		return isEmpty() ? NULL : front->data;
	}
};

/* 构建二叉树 */
// 孩子兄弟法定义结点
template<typename Type>
class TreeNode {
public:
	Type value;
	TreeNode* firstChild, * nextSibling;

	TreeNode() : firstChild(NULL), nextSibling(NULL) {}
	TreeNode(Type item, TreeNode<Type>* l = NULL, TreeNode<Type>* r = NULL) : value(item), firstChild(l), nextSibling(r) {}
	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node);
};

// 重载 << 运算符
template<typename Type>
std::ostream& operator<<(std::ostream& os, const TreeNode<Type>& node) {
	os << node.value;
	return os;
}

// 定义二叉树
template<typename Type>
class MyBinaryTree {
protected:
	TreeNode<Type>* root;				// 根节点
	TreeNode<Type>* copy(const TreeNode<Type>* subTree);
	void outputNode(TreeNode<Type>* node) { if (node != NULL) std::cout << node->value << " "; }
	bool containsRecursive(TreeNode<Type>* node, const Type& data) {
		if (node == nullptr) { return false; }
		if (node->value == data) { return true; }
		return containsRecursive(node->firstChild, data) || containsRecursive(node->nextSibling, data);
	}
public:
	MyBinaryTree() : root(NULL) {}																							// 构造函数
	MyBinaryTree(Type& item);																								// 构造函数
	MyBinaryTree(MyBinaryTree<Type>& other) { root = copy(other.root); }													// 复制构造函数
	~MyBinaryTree() { destroy(root); }																						// 析构函数
	void setRoot(TreeNode<Type>* newRoot) { root = newRoot; }
	void destroy(TreeNode<Type>*& subTree);
	bool isEmpty(void) { return root == NULL; }																				// 判断二叉树是否为空
	// 得到二叉树的高度
	int getHeight(TreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (std::max(getHeight(subTree->firstChild), getHeight(subTree->nextSibling)) + 1); }
	// 得到二叉树的结点数
	int getSize(TreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (getSize(subTree->firstChild) + getSize(subTree->nextSibling) + 1); }
	TreeNode<Type>* getRoot(void) const { return root; }
	TreeNode<Type>* getParent(TreeNode<Type>* current, TreeNode<Type>* subTree);
	TreeNode<Type>* getLeftChild(TreeNode<Type>* current) { return current == NULL ? NULL : current->firstChild; }
	TreeNode<Type>* getRightChild(TreeNode<Type>* current) { return current == NULL ? NULL : current->nextSibling; }
	TreeNode<Type>* findNode(const Type& item, TreeNode<Type>* subTree);													// 获取指定值的节点
	// 遍历二叉树
	void preOrder(TreeNode<Type>* subTree);																	// 前序遍历
	void inOrder(TreeNode<Type>* subTree);																	// 中序遍历
	void postOrder(TreeNode<Type>* subTree);																// 后序遍历
	void levelOrder(TreeNode<Type>* subTree);																// 层次序遍历
	// 插入二叉树
	bool leftInsertNode(TreeNode<Type>* current, const Type& item);
	bool rightInsertNode(TreeNode<Type>* current, const Type& item);
	bool modifyNode(const Type& oldItem, const Type& newItem, TreeNode<Type>* subTree);
	bool insertAsFirstChild(TreeNode<Type>* current, const Type& item);
	void deleteChildren(TreeNode<Type>* node);
	MyBinaryTree<Type>& operator=(const MyBinaryTree<Type>& other);
};

// 复制二叉树
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::copy(const TreeNode<Type>* subTree)
{
	if (subTree == NULL) {
		// 如果子树为空，则返回空
		return NULL;
	}

	// 创建新节点的副本
	TreeNode<Type>* newNode = new TreeNode<Type>(subTree->value);

	// 递归复制左子树和右子树
	newNode->firstChild = copy(subTree->firstChild);
	newNode->nextSibling = copy(subTree->nextSibling);

	return newNode;
}

// 创建二叉树
template<typename Type>
MyBinaryTree<Type>::MyBinaryTree(Type& item) { root = new(std::nothrow) TreeNode<Type>(item); }

// 销毁二叉树
template<typename Type>
void MyBinaryTree<Type>::destroy(TreeNode<Type>*& subTree)
{
	if (subTree != NULL) {
		// 递归删除所有子节点
		destroy(subTree->firstChild);
		// 递归删除所有兄弟节点
		destroy(subTree->nextSibling);
		// 删除当前节点
		delete subTree;
		// 确保父结点指针为空
		subTree = NULL;
	}
}

// 获取指定节点的父节点
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::getParent(TreeNode<Type>* current, TreeNode<Type>* subTree) {
	if (subTree == NULL || current == NULL || subTree == current) {
		return NULL;
	}

	// 检查当前节点的孩子或兄弟是否是目标节点
	if (subTree->firstChild == current || subTree->nextSibling == current) {
		return subTree;
	}

	// 递归查找左子树（第一个孩子）
	TreeNode<Type>* leftResult = getParent(current, subTree->firstChild);
	if (leftResult != NULL) {
		return leftResult;
	}

	// 递归查找右子树（下一个兄弟）
	return getParent(current, subTree->nextSibling);
}

// 获取指定节点
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::findNode(const Type& item, TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		// 如果子树为空，返回 NULL
		return NULL;
	}

	if (subTree->value == item) {
		// 找到匹配的节点，返回该节点
		return subTree;
	}

	// 首先在第一个孩子（左子树）中递归查找
	TreeNode<Type>* found = findNode(item, subTree->firstChild);
	if (found != NULL) {
		// 如果在子树中找到了，返回找到的节点
		return found;
	}

	// 如果没有在子树中找到，继续在兄弟节点（右子树）中递归查找
	return findNode(item, subTree->nextSibling);
}

// 前序遍历
template<typename Type>
void MyBinaryTree<Type>::preOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		outputNode(subTree);
		preOrder(subTree->firstChild);
		preOrder(subTree->nextSibling);
	}
}

// 中序遍历
template<typename Type>
void MyBinaryTree<Type>::inOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		inOrder(subTree->firstChild);
		outputNode(subTree);
		inOrder(subTree->nextSibling);
	}
}

// 后序遍历
template<typename Type>
void MyBinaryTree<Type>::postOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		postOrder(subTree->firstChild);
		postOrder(subTree->nextSibling);
		outputNode(subTree);
	}
}

// 层次遍历
template<typename Type>
void MyBinaryTree<Type>::levelOrder(TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		return;
	}

	LinkedQueue<Type> q;
	q.enqueue(subTree);

	while (!q.isEmpty()) {
		TreeNode<Type>* currentNode = q.dequeue();
		// 访问当前节点
		outputNode(currentNode);
		// 将当前节点的所有孩子加入队列
		TreeNode<Type>* child = currentNode->firstChild;
		while (child != NULL) {
			q.enqueue(child);
			child = child->nextSibling;
		}
	}
}

// 从左边插入节点
template<typename Type>
bool MyBinaryTree<Type>::leftInsertNode(TreeNode<Type>* current, const Type& item) {
	if (current == NULL || current->firstChild != NULL)
		return false;
	current->firstChild = new(std::nothrow) TreeNode<Type>(item);
	return true;
}

// 从右边插入节点
template<typename Type>
bool MyBinaryTree<Type>::rightInsertNode(TreeNode<Type>* current, const Type& item) {
	if (current == NULL || current->nextSibling != NULL)
		return false;
	current->nextSibling = new(std::nothrow) TreeNode<Type>(item);
	return true;
}

// 修改指定节点
template<typename Type>
bool MyBinaryTree<Type>::modifyNode(const Type& oldItem, const Type& newItem, TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		return false;
	}
	if (subTree->value == oldItem) {
		// 找到匹配的节点，修改它的值
		subTree->value = newItem;
		return true;
	}
	// 在第一个孩子中递归查找并尝试修改
	if (modifyNode(oldItem, newItem, subTree->firstChild)) {
		return true;
	}
	// 在兄弟节点中递归查找并尝试修改
	return modifyNode(oldItem, newItem, subTree->nextSibling);
}

template<typename Type>
bool MyBinaryTree<Type>::insertAsFirstChild(TreeNode<Type>* current, const Type& item)
{
	if (current == NULL) return false;
	// 创建新的树节点
	TreeNode<Type>* newNode = new TreeNode<Type>(item);
	newNode->nextSibling = current->firstChild;
	current->firstChild = newNode;
	return true;
}

template<typename Type>
void MyBinaryTree<Type>::deleteChildren(TreeNode<Type>* node)
{
	if (node == NULL) {
		return;
	}

	// 递归删除左子树和右子树
	deleteChildren(node->firstChild);
	deleteChildren(node->nextSibling);

	// 删除子节点并将指针设置为NULL
	delete node->firstChild;
	node->firstChild = NULL;
	delete node->nextSibling;
	node->nextSibling = NULL;
}

// 重载 = 运算符
template <typename Type>
MyBinaryTree<Type>& MyBinaryTree<Type>::operator=(const MyBinaryTree<Type>& other)
{
	if (this != &other) {
		destroy(root);
		root = copy(other.root);
	}
	return *this;
}
