#pragma once
#include <iostream>
#include <assert.h>
typedef int Status;
/* ջ */
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
	Stack() :top(NULL) {}							//���캯��
	~Stack();										//��������
	void Push(const Type& item);					//��ջ
	Type Pop();										//��ջ
	Type GetTop();									//ȡջ��Ԫ��
	void MakeEmpty();								//�ÿ�ջ
	int IsEmpty()const { return top == NULL; }		//��ջ�շ�
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
	//�½������top֮ǰ������Ϊ��ջ��
}

template<class Type>
Type Stack<Type>::Pop()
{
	assert(!IsEmpty());
	StackNode<Type>* p = top;
	Type retvalue = p->data;	//�ݴ�ջ������
	top = top->link;			//�޸�ջ��ָ��
	delete p;
	return retvalue;			//�ͷţ���������
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

/* ѭ������ */
template<class T>
class SeqQueue {
protected:
	int rear, front;
	T* elements;
	int maxSize;
public:
	SeqQueue(int sz = 10) {
		maxSize = sz + 1; // Ϊ�˱�������Ͷӿճ�ͻ�����鳤����Ҫ��ʵ�ʳ��ȶ�1
		elements = new T[maxSize];
		rear = front = 0;
	}
	~SeqQueue() { delete[]elements; }
	//�����в�������x��ӣ�������������
	bool EnQueue(const T& x) {
		if (IsFull()) {
			return false; // ��������
		}
		elements[rear] = x;
		rear = (rear + 1) % maxSize; // ѭ������
		return true;
	}
	//�����в��գ����˳���ͷԪ��x���ɺ�������true,����ӿշ���false
	bool DeQueue() {
		if (IsEmpty()) {
			return false; // ����Ϊ��
		}
		front = (front + 1) % maxSize; // ѭ������
		return true;
	}					
	//�����в��գ���������true����ͷԪ�ص�ֵ�����򷵻�false
	bool GetFront(T& x) {
		if (IsEmpty()) {
			return false; // ����Ϊ��
		}
		x = elements[front];
		return true;
	}
	void makeEmpty(){ front = rear = 0; }	//�ÿղ�������ͷָ���βָ�붼Ϊ0
	bool IsEmpty()const { return (front == rear) ? true : false; }
										//�ж϶��пշ�
	bool IsFull()const { return((rear + 1) % maxSize == front) ? true : false; }
										//�ж϶�������
	int getSize()const { return (rear - front + maxSize) % maxSize; }
										//�����Ԫ�صĸ���								
};