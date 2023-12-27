#pragma once
#include <iostream>
#include <assert.h>
typedef int Status;
/* 栈 */
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
public:
	Stack() :top(NULL) {}							//构造函数
	~Stack();										//析构函数
	void Push(const Type& item);					//进栈
	Type Pop();										//出栈
	Type GetTop();									//取栈顶元素
	void MakeEmpty();								//置空栈
	int IsEmpty()const { return top == NULL; }		//判栈空否
	void OverturnStack();
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
	//新结点链入top之前，并成为新栈顶
}

template<class Type>
Type Stack<Type>::Pop()
{
	assert(!IsEmpty());
	StackNode<Type>* p = top;
	Type retvalue = p->data;	//暂存栈顶数据
	top = top->link;			//修改栈顶指针
	delete p;
	return retvalue;			//释放，返回数据
}

template<class Type>
Type Stack<Type>::GetTop()
{
	assert(!IsEmpty());
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

/* 循环队列 */
template<class T>
class SeqQueue {
protected:
	int rear, front;
	T* elements;
	int maxSize;
public:
	SeqQueue(int sz = 10) {
		maxSize = sz + 1; // 为了避免队满和队空冲突，数组长度需要比实际长度多1
		elements = new T[maxSize];
		rear = front = 0;
	}
	~SeqQueue() { delete[]elements; }
	//若队列不满，则x入队，否则队溢出处理
	bool EnQueue(const T& x) {
		if (IsFull()) {
			return false; // 队列已满
		}
		elements[rear] = x;
		rear = (rear + 1) % maxSize; // 循环队列
		return true;
	}
	//若队列不空，则退出队头元素x并由函数返回true,否则队空返回false
	bool DeQueue() {
		if (IsEmpty()) {
			return false; // 队列为空
		}
		front = (front + 1) % maxSize; // 循环队列
		return true;
	}					
	//若队列不空，则函数返回true及队头元素的值，否则返回false
	bool GetFront(T& x) {
		if (IsEmpty()) {
			return false; // 队列为空
		}
		x = elements[front];
		return true;
	}
	void makeEmpty(){ front = rear = 0; }	//置空操作：队头指针和尾指针都为0
	bool IsEmpty()const { return (front == rear) ? true : false; }
										//判断队列空否
	bool IsFull()const { return((rear + 1) % maxSize == front) ? true : false; }
										//判断队列满否
	int getSize()const { return (rear - front + maxSize) % maxSize; }
										//求队列元素的个数								
};