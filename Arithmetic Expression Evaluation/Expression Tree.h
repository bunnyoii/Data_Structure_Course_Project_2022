#pragma once
#include <iostream>
using namespace std;
const int defaultSize = 65536;
/* �����㷨���õ���Ԥ���峣�������� */
// �������״̬����
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

typedef int DataType;
template<typename Type>
class TreeNode;
class BinarySortTree;

// ����ջ�洢���ʽ
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
	Stack() :top(NULL) ,size(0){}					//���캯��
	~Stack();										//��������
	void Push(const Type& item);					//��ջ
	Type Pop();										//��ջ
	Type GetTop();									//ȡջ��Ԫ��
	void MakeEmpty();								//�ÿ�ջ
	int IsEmpty()const { return top == NULL; }		//��ջ�շ�
	void OverturnStack();							//��תջ
	int GetSize() const { return size; }			// ��ȡջ��Ԫ������
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
	//�½������top֮ǰ������Ϊ��ջ��
}

template<class Type>
Type Stack<Type>::Pop()
{
	if (IsEmpty()) { return ERROR;}
	StackNode<Type>* p = top;
	Type retvalue = p->data;	//�ݴ�ջ������
	top = top->link;			//�޸�ջ��ָ��
	delete p;
	size--;
	return retvalue;			//�ͷţ���������
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

// ������б��ڽ��в�������
// ����ڵ㶨��
template<typename Type>
class QueueNode {
public:
	TreeNode<Type>* data;
	QueueNode<Type>* next;
	QueueNode(TreeNode<Type>* node) : data(node), next(NULL) {}
};

// ���Ӷ���
template<typename Type>
class LinkedQueue {
private:
	QueueNode<Type>* front;   // ����ͷָ��
	QueueNode<Type>* rear;    // ����βָ��

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

/* ���������� */
// �����ֵܷ�������
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

// ���� << �����
template<typename Type>
std::ostream& operator<<(std::ostream& os, const TreeNode<Type>& node) {
	os << node.value;
	return os;
}

// ���������
template<typename Type>
class MyBinaryTree {
protected:
	TreeNode<Type>* root;				// ���ڵ�
	TreeNode<Type>* copy(const TreeNode<Type>* subTree);
	void outputNode(TreeNode<Type>* node) { if (node != NULL) std::cout << node->value << " "; }
	bool containsRecursive(TreeNode<Type>* node, const Type& data) {
		if (node == nullptr) { return false; }
		if (node->value == data) { return true; }
		return containsRecursive(node->firstChild, data) || containsRecursive(node->nextSibling, data);
	}
public:
	MyBinaryTree() : root(NULL) {}																							// ���캯��
	MyBinaryTree(Type& item);																								// ���캯��
	MyBinaryTree(MyBinaryTree<Type>& other) { root = copy(other.root); }													// ���ƹ��캯��
	~MyBinaryTree() { destroy(root); }																						// ��������
	void setRoot(TreeNode<Type>* newRoot) { root = newRoot; }
	void destroy(TreeNode<Type>*& subTree);
	bool isEmpty(void) { return root == NULL; }																				// �ж϶������Ƿ�Ϊ��
	// �õ��������ĸ߶�
	int getHeight(TreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (std::max(getHeight(subTree->firstChild), getHeight(subTree->nextSibling)) + 1); }
	// �õ��������Ľ����
	int getSize(TreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (getSize(subTree->firstChild) + getSize(subTree->nextSibling) + 1); }
	TreeNode<Type>* getRoot(void) const { return root; }
	TreeNode<Type>* getParent(TreeNode<Type>* current, TreeNode<Type>* subTree);
	TreeNode<Type>* getLeftChild(TreeNode<Type>* current) { return current == NULL ? NULL : current->firstChild; }
	TreeNode<Type>* getRightChild(TreeNode<Type>* current) { return current == NULL ? NULL : current->nextSibling; }
	TreeNode<Type>* findNode(const Type& item, TreeNode<Type>* subTree);													// ��ȡָ��ֵ�Ľڵ�
	// ����������
	void preOrder(TreeNode<Type>* subTree);																	// ǰ�����
	void inOrder(TreeNode<Type>* subTree);																	// �������
	void postOrder(TreeNode<Type>* subTree);																// �������
	void levelOrder(TreeNode<Type>* subTree);																// ��������
	// ���������
	bool leftInsertNode(TreeNode<Type>* current, const Type& item);
	bool rightInsertNode(TreeNode<Type>* current, const Type& item);
	bool modifyNode(const Type& oldItem, const Type& newItem, TreeNode<Type>* subTree);
	bool insertAsFirstChild(TreeNode<Type>* current, const Type& item);
	void deleteChildren(TreeNode<Type>* node);
	MyBinaryTree<Type>& operator=(const MyBinaryTree<Type>& other);
};

// ���ƶ�����
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::copy(const TreeNode<Type>* subTree)
{
	if (subTree == NULL) {
		// �������Ϊ�գ��򷵻ؿ�
		return NULL;
	}

	// �����½ڵ�ĸ���
	TreeNode<Type>* newNode = new TreeNode<Type>(subTree->value);

	// �ݹ鸴����������������
	newNode->firstChild = copy(subTree->firstChild);
	newNode->nextSibling = copy(subTree->nextSibling);

	return newNode;
}

// ����������
template<typename Type>
MyBinaryTree<Type>::MyBinaryTree(Type& item) { root = new(std::nothrow) TreeNode<Type>(item); }

// ���ٶ�����
template<typename Type>
void MyBinaryTree<Type>::destroy(TreeNode<Type>*& subTree)
{
	if (subTree != NULL) {
		// �ݹ�ɾ�������ӽڵ�
		destroy(subTree->firstChild);
		// �ݹ�ɾ�������ֵܽڵ�
		destroy(subTree->nextSibling);
		// ɾ����ǰ�ڵ�
		delete subTree;
		// ȷ�������ָ��Ϊ��
		subTree = NULL;
	}
}

// ��ȡָ���ڵ�ĸ��ڵ�
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::getParent(TreeNode<Type>* current, TreeNode<Type>* subTree) {
	if (subTree == NULL || current == NULL || subTree == current) {
		return NULL;
	}

	// ��鵱ǰ�ڵ�ĺ��ӻ��ֵ��Ƿ���Ŀ��ڵ�
	if (subTree->firstChild == current || subTree->nextSibling == current) {
		return subTree;
	}

	// �ݹ��������������һ�����ӣ�
	TreeNode<Type>* leftResult = getParent(current, subTree->firstChild);
	if (leftResult != NULL) {
		return leftResult;
	}

	// �ݹ��������������һ���ֵܣ�
	return getParent(current, subTree->nextSibling);
}

// ��ȡָ���ڵ�
template<typename Type>
TreeNode<Type>* MyBinaryTree<Type>::findNode(const Type& item, TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		// �������Ϊ�գ����� NULL
		return NULL;
	}

	if (subTree->value == item) {
		// �ҵ�ƥ��Ľڵ㣬���ظýڵ�
		return subTree;
	}

	// �����ڵ�һ�����ӣ����������еݹ����
	TreeNode<Type>* found = findNode(item, subTree->firstChild);
	if (found != NULL) {
		// ������������ҵ��ˣ������ҵ��Ľڵ�
		return found;
	}

	// ���û�����������ҵ����������ֵܽڵ㣨���������еݹ����
	return findNode(item, subTree->nextSibling);
}

// ǰ�����
template<typename Type>
void MyBinaryTree<Type>::preOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		outputNode(subTree);
		preOrder(subTree->firstChild);
		preOrder(subTree->nextSibling);
	}
}

// �������
template<typename Type>
void MyBinaryTree<Type>::inOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		inOrder(subTree->firstChild);
		outputNode(subTree);
		inOrder(subTree->nextSibling);
	}
}

// �������
template<typename Type>
void MyBinaryTree<Type>::postOrder(TreeNode<Type>* subTree) {
	if (subTree != NULL) {
		postOrder(subTree->firstChild);
		postOrder(subTree->nextSibling);
		outputNode(subTree);
	}
}

// ��α���
template<typename Type>
void MyBinaryTree<Type>::levelOrder(TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		return;
	}

	LinkedQueue<Type> q;
	q.enqueue(subTree);

	while (!q.isEmpty()) {
		TreeNode<Type>* currentNode = q.dequeue();
		// ���ʵ�ǰ�ڵ�
		outputNode(currentNode);
		// ����ǰ�ڵ�����к��Ӽ������
		TreeNode<Type>* child = currentNode->firstChild;
		while (child != NULL) {
			q.enqueue(child);
			child = child->nextSibling;
		}
	}
}

// ����߲���ڵ�
template<typename Type>
bool MyBinaryTree<Type>::leftInsertNode(TreeNode<Type>* current, const Type& item) {
	if (current == NULL || current->firstChild != NULL)
		return false;
	current->firstChild = new(std::nothrow) TreeNode<Type>(item);
	return true;
}

// ���ұ߲���ڵ�
template<typename Type>
bool MyBinaryTree<Type>::rightInsertNode(TreeNode<Type>* current, const Type& item) {
	if (current == NULL || current->nextSibling != NULL)
		return false;
	current->nextSibling = new(std::nothrow) TreeNode<Type>(item);
	return true;
}

// �޸�ָ���ڵ�
template<typename Type>
bool MyBinaryTree<Type>::modifyNode(const Type& oldItem, const Type& newItem, TreeNode<Type>* subTree) {
	if (subTree == NULL) {
		return false;
	}
	if (subTree->value == oldItem) {
		// �ҵ�ƥ��Ľڵ㣬�޸�����ֵ
		subTree->value = newItem;
		return true;
	}
	// �ڵ�һ�������еݹ���Ҳ������޸�
	if (modifyNode(oldItem, newItem, subTree->firstChild)) {
		return true;
	}
	// ���ֵܽڵ��еݹ���Ҳ������޸�
	return modifyNode(oldItem, newItem, subTree->nextSibling);
}

template<typename Type>
bool MyBinaryTree<Type>::insertAsFirstChild(TreeNode<Type>* current, const Type& item)
{
	if (current == NULL) return false;
	// �����µ����ڵ�
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

	// �ݹ�ɾ����������������
	deleteChildren(node->firstChild);
	deleteChildren(node->nextSibling);

	// ɾ���ӽڵ㲢��ָ������ΪNULL
	delete node->firstChild;
	node->firstChild = NULL;
	delete node->nextSibling;
	node->nextSibling = NULL;
}

// ���� = �����
template <typename Type>
MyBinaryTree<Type>& MyBinaryTree<Type>::operator=(const MyBinaryTree<Type>& other)
{
	if (this != &other) {
		destroy(root);
		root = copy(other.root);
	}
	return *this;
}
