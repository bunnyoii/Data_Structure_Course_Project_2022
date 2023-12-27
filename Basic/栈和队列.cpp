#include <iostream>

using namespace std;
#define MAXSIZE 100
/* 操作算法中用到的预定义常量和类型 */
// 函数结果状态代码
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	
#define OVERFLOW		-2

// startus 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char SElemType;
typedef char QElemType;

/*	栈(stack)是一个特殊的线性表
*	是限定仅在一端(通常是表尾)进行插入和删除操作的线性表。
*	又称后进先出的线性表，简称LIFO结构。
*	表尾-栈顶Top		表头-栈底Base
*	入栈：PUSH(x)	出栈：POP(x)
*/


/*	队列(queue)是一种先进先出的线性表(FIFO)
*	在表一段插入（表尾），在另一端（表头）删除
*	若要对数据按行处理/有序处理，要考虑队列
*/


/* 顺序栈的表示和实现 */
/* 存储方式：痛一般线性表的顺序存储结构。*/
// top指针：指示栈顶位置（通常为了方便，top指示的是栈顶元素之上的下标地址）
// base指针：指示栈底位置
// stacksize：栈可使用最大容量
// 空栈：base == top
// 栈满：top - base == stacksize
// 上溢(overflow)：栈已满，但依然要压入元素
// 下溢(underflow)：栈已空，但依然要弹出元素

/*栈满时的处理方法：
* 1.报错返回操作系统
* 2.分配更大的空间
* 3.多栈处理：栈浮动技术-双栈共享一个栈空间
* 根除：使用链栈 */

// 顺序栈的表示
typedef struct {
	SElemType* base;//栈底指针
	SElemType* top;//栈顶指针
	int stacksize;//栈可用最大容量
}SqStack;

// 顺序栈的初始化
Status InitStack(SqStack& S) {
	S.base = new SElemType[MAXSIZE];
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

// 顺序栈判断是否为空
Status StackEmpty(SqStack S) {
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// 求顺序栈长度
int StackLength(SqStack S) {
	return S.top - S.base;
}

// 清空顺序栈
Status ClearStack(SqStack S) {
	if (S.base)S.top == S.base;
	return OK;
}

// 销毁顺序栈
Status DestroyStack(SqStack& S) {
	if (S.base) {
		delete S.base;
		S.stacksize = 0;
		S.base = S.top = NULL;
	}
	return OK;
}

// 顺序栈的入栈
// 判断是否栈满，满则上溢出错
// 元素e压入栈顶
// 栈顶指针 + 1
Status Push(SqStack& S, SElemType e) {
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top++ = e;//(first: e = *S.top; second: S.top++)
	return OK;
}

// 顺序栈的出栈
// 判断是否栈空，满则下溢出错
// 获取栈顶元素e
// 栈顶指针 - 1
Status Pop(SqStack& S, SElemType& e) {
	if (S.top == S.base) return ERROR;
	e = *--S.top;//(first: --S.top; second: e = *S.top)
	return OK;
}


/*	链栈的表示和实现 */
/*	链栈是运算受限的单链表，只能在链表头部进行操作 */
/*	链表的头指针就是栈顶 
*	不需要头结点
*	基本不存在栈满的现象
*	空栈相当于头指针指向空
*	插入和删除仅在栈顶处执行 */
typedef struct StackNode {
	SElemType data;
	struct StackNode* next;
}StackNode,*LinkStack;

// 链栈的初始化
void InitStack(LinkStack& S) {
	S = NULL;
}

// 判断链栈是否为空
Status StackEmpty(LinkStack S) {
	if (S == NULL) return TRUE;
	else return FALSE;
}
// 链栈的入栈
Status Push(LinkStack& S, SElemType e) {
	LinkStack p;
	p = new StackNode;//生成新结点p
	p->data = e;//将新结点的数据域置为e
	p->next = S;//将新结点插入栈顶
	S = p;//修改栈顶指针
	return OK;
}

// 链栈的出栈
Status Pop(LinkStack& S, SElemType& e) {
	LinkStack p;
	if (S = NULL)return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return OK;
}

// 取栈顶元素
SElemType GetTop(LinkStack S) {
	if (S != NULL)
		return S->data;
}

/* 栈与递归 */
/*	void p(参数表){
*		if(递归结束条件) 可直接求解步骤			-----基本项
*		else p(较小的参数);					-----归纳项
*	}
*/

/* 队列的表示和操作的实现 */
/* 队列的顺序表示和实现 */
typedef struct {
	QElemType* base;//初始化的动态分配存储空间
	int front;//头指针,若队列不空，指向队列头元素
	int rear;//尾指针，若队列不空，指向队尾元素的下一个位置
}SqQueue;

// 解决假上溢的方法
// 1.引入循环队列
// base[0]接在base[MAXQSIZE - 1]之后，若rear + 1 == M,则令rear == 0；
// 实现方法：利用模(%)运算
/*	插入元素:Q.base[Q.rear] = x;
			Q.rear = (Q.rear + 1) % MAXSIZE
	删除元素:x = Q.base[s.front]
			Q.front = (Q.front + 1) % MAXSIZE
*/
// 2.少用一个元素空间
// 队空： front == rear
// 队满: (raer + 1) % MAXSIZE == front (队尾指针再 + 1，就与队头指针重合)

/* 循环队列 */
// 初始化队列
Status InitQueue(SqQueue& Q) {
	Q.base = new QElemType[MAXSIZE];//分配数组空间
	if (!Q.base)exit(OVERFLOW);//存储空间分配失败
	Q.front = Q.rear = 0;//头指针尾指针置0，队列为空
	return OK;
}

// 求队列的长度
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// 循环队列入队
Status EnQueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;//队满
	Q.base[Q.rear] = e;//新元素加入队尾
	Q.rear = (Q.rear + 1) % MAXSIZE;//队尾指针 + 1
	return OK;
}

// 循环队列出队
Status DeQueue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return OK;
}

/*	链队 
*	若用户无法估计所用队列长度，采用链队 */
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;

// 链队列的初始化
Status InitQueue(LinkQueue& Q) {
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

// 销毁链队列
Status DestroyQueue(LinkQueue& Q) {
	QueuePtr p;
	while (Q.front) {
		p = Q.front->next; free(Q.front); Q.front = p;
	}
	return OK;
}

// 将元素e入队
Status EnQueue(LinkQueue& Q, QElemType e) {
	QNode* p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

// 链队列出队
Status DeQueue(LinkQueue& Q, QElemType e) {
	QNode* p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next; e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)Q.rear = Q.front;
	free(p);
	return OK;
}

// 求链队列的队头元素
Status GetHead(LinkQueue Q, QElemType e) {
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->next->data;
	return OK;
}