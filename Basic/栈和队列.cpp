#include <iostream>

using namespace std;
#define MAXSIZE 100
/* �����㷨���õ���Ԥ���峣�������� */
// �������״̬����
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	
#define OVERFLOW		-2

// startus �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char SElemType;
typedef char QElemType;

/*	ջ(stack)��һ����������Ա�
*	���޶�����һ��(ͨ���Ǳ�β)���в����ɾ�����������Ա�
*	�ֳƺ���ȳ������Ա����LIFO�ṹ��
*	��β-ջ��Top		��ͷ-ջ��Base
*	��ջ��PUSH(x)	��ջ��POP(x)
*/


/*	����(queue)��һ���Ƚ��ȳ������Ա�(FIFO)
*	�ڱ�һ�β��루��β��������һ�ˣ���ͷ��ɾ��
*	��Ҫ�����ݰ��д���/������Ҫ���Ƕ���
*/


/* ˳��ջ�ı�ʾ��ʵ�� */
/* �洢��ʽ��ʹһ�����Ա��˳��洢�ṹ��*/
// topָ�룺ָʾջ��λ�ã�ͨ��Ϊ�˷��㣬topָʾ����ջ��Ԫ��֮�ϵ��±��ַ��
// baseָ�룺ָʾջ��λ��
// stacksize��ջ��ʹ���������
// ��ջ��base == top
// ջ����top - base == stacksize
// ����(overflow)��ջ����������ȻҪѹ��Ԫ��
// ����(underflow)��ջ�ѿգ�����ȻҪ����Ԫ��

/*ջ��ʱ�Ĵ�������
* 1.�����ز���ϵͳ
* 2.�������Ŀռ�
* 3.��ջ����ջ��������-˫ջ����һ��ջ�ռ�
* ������ʹ����ջ */

// ˳��ջ�ı�ʾ
typedef struct {
	SElemType* base;//ջ��ָ��
	SElemType* top;//ջ��ָ��
	int stacksize;//ջ�����������
}SqStack;

// ˳��ջ�ĳ�ʼ��
Status InitStack(SqStack& S) {
	S.base = new SElemType[MAXSIZE];
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

// ˳��ջ�ж��Ƿ�Ϊ��
Status StackEmpty(SqStack S) {
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// ��˳��ջ����
int StackLength(SqStack S) {
	return S.top - S.base;
}

// ���˳��ջ
Status ClearStack(SqStack S) {
	if (S.base)S.top == S.base;
	return OK;
}

// ����˳��ջ
Status DestroyStack(SqStack& S) {
	if (S.base) {
		delete S.base;
		S.stacksize = 0;
		S.base = S.top = NULL;
	}
	return OK;
}

// ˳��ջ����ջ
// �ж��Ƿ�ջ���������������
// Ԫ��eѹ��ջ��
// ջ��ָ�� + 1
Status Push(SqStack& S, SElemType e) {
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top++ = e;//(first: e = *S.top; second: S.top++)
	return OK;
}

// ˳��ջ�ĳ�ջ
// �ж��Ƿ�ջ�գ������������
// ��ȡջ��Ԫ��e
// ջ��ָ�� - 1
Status Pop(SqStack& S, SElemType& e) {
	if (S.top == S.base) return ERROR;
	e = *--S.top;//(first: --S.top; second: e = *S.top)
	return OK;
}


/*	��ջ�ı�ʾ��ʵ�� */
/*	��ջ���������޵ĵ�����ֻ��������ͷ�����в��� */
/*	�����ͷָ�����ջ�� 
*	����Ҫͷ���
*	����������ջ��������
*	��ջ�൱��ͷָ��ָ���
*	�����ɾ������ջ����ִ�� */
typedef struct StackNode {
	SElemType data;
	struct StackNode* next;
}StackNode,*LinkStack;

// ��ջ�ĳ�ʼ��
void InitStack(LinkStack& S) {
	S = NULL;
}

// �ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S) {
	if (S == NULL) return TRUE;
	else return FALSE;
}
// ��ջ����ջ
Status Push(LinkStack& S, SElemType e) {
	LinkStack p;
	p = new StackNode;//�����½��p
	p->data = e;//���½�����������Ϊe
	p->next = S;//���½�����ջ��
	S = p;//�޸�ջ��ָ��
	return OK;
}

// ��ջ�ĳ�ջ
Status Pop(LinkStack& S, SElemType& e) {
	LinkStack p;
	if (S = NULL)return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return OK;
}

// ȡջ��Ԫ��
SElemType GetTop(LinkStack S) {
	if (S != NULL)
		return S->data;
}

/* ջ��ݹ� */
/*	void p(������){
*		if(�ݹ��������) ��ֱ����ⲽ��			-----������
*		else p(��С�Ĳ���);					-----������
*	}
*/

/* ���еı�ʾ�Ͳ�����ʵ�� */
/* ���е�˳���ʾ��ʵ�� */
typedef struct {
	QElemType* base;//��ʼ���Ķ�̬����洢�ռ�
	int front;//ͷָ��,�����в��գ�ָ�����ͷԪ��
	int rear;//βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ��
}SqQueue;

// ���������ķ���
// 1.����ѭ������
// base[0]����base[MAXQSIZE - 1]֮����rear + 1 == M,����rear == 0��
// ʵ�ַ���������ģ(%)����
/*	����Ԫ��:Q.base[Q.rear] = x;
			Q.rear = (Q.rear + 1) % MAXSIZE
	ɾ��Ԫ��:x = Q.base[s.front]
			Q.front = (Q.front + 1) % MAXSIZE
*/
// 2.����һ��Ԫ�ؿռ�
// �ӿգ� front == rear
// ����: (raer + 1) % MAXSIZE == front (��βָ���� + 1�������ͷָ���غ�)

/* ѭ������ */
// ��ʼ������
Status InitQueue(SqQueue& Q) {
	Q.base = new QElemType[MAXSIZE];//��������ռ�
	if (!Q.base)exit(OVERFLOW);//�洢�ռ����ʧ��
	Q.front = Q.rear = 0;//ͷָ��βָ����0������Ϊ��
	return OK;
}

// ����еĳ���
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// ѭ���������
Status EnQueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;//����
	Q.base[Q.rear] = e;//��Ԫ�ؼ����β
	Q.rear = (Q.rear + 1) % MAXSIZE;//��βָ�� + 1
	return OK;
}

// ѭ�����г���
Status DeQueue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return OK;
}

/*	���� 
*	���û��޷��������ö��г��ȣ��������� */
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ��
}LinkQueue;

// �����еĳ�ʼ��
Status InitQueue(LinkQueue& Q) {
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

// ����������
Status DestroyQueue(LinkQueue& Q) {
	QueuePtr p;
	while (Q.front) {
		p = Q.front->next; free(Q.front); Q.front = p;
	}
	return OK;
}

// ��Ԫ��e���
Status EnQueue(LinkQueue& Q, QElemType e) {
	QNode* p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

// �����г���
Status DeQueue(LinkQueue& Q, QElemType e) {
	QNode* p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next; e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)Q.rear = Q.front;
	free(p);
	return OK;
}

// �������еĶ�ͷԪ��
Status GetHead(LinkQueue Q, QElemType e) {
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->next->data;
	return OK;
}