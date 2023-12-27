#include <iostream>

using namespace std;
#define MAXSIZE 10
/* 操作算法中用到的预定义常量和类型 */
//函数结果状态代码
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	
#define OVERFLOW		-2

//startus 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;


/* 顺序表的建立 */
typedef struct {
	ElemType* elem;
	int length;
}SqList;

/* 链表的建立 */
typedef struct LNode{
	ElemType data;//结点的数据域
	struct LNode* next;//结点的指针域
} *LinkList;

/* 双向链表的建立 */
typedef struct DulNode {
	ElemType data;
	struct DulNode* prior, * next;
}*DuLinkList;

/* 循环链表的建立 */
typedef struct CircleNode {
	ElemType data;
	struct CircleNode* next;
}*CircleLinkList;

/* 顺序表的基本操作的实现 */
//线性表L的初始化（参数用引用）
Status InitList_Sq(SqList& L) {	//构造一个空的顺序表L
	L.elem = new ElemType[MAXSIZE];//为顺序表分配空间
	if (!L.elem) exit(OVERFLOW);//存储分配失败
	L.length = 0;//空表长度为0
	return OK;
}

//销毁线性表L
void DestroyList(SqList& L) {
	if (L.elem)
		delete L.elem;
}

//清空线性表L
void ClearList(SqList& L) {
	L.length = 0;
}

//求线性表的长度
int GetLength(SqList L) {
	return(L.length);
}

//判断线性表L是否为空
int IsEmpty(SqList L) {
	if (L.length == 0) return 1;
	else return 0;
}

//顺序表的取值（根据位置i获取相应位置数据元素的内容）
int GetElem(SqList L, int i, ElemType& e) {
	if (i<1 || i>L.length) return ERROR;//判断i是否合理
	e = L.elem[i - 1];//第i-1的单元存储第i个数据
	return OK;
}

//顺序表的查找算法
int LocateElem(SqList L, ElemType e) {
	//在线性表L中查找值为e的数据元素，返回其序号
	for (int i = 0; i < L.length; i++)
		if (L.elem[i] == e) return i + 1;
	return 0;
}

//顺序表的插入
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length == MAXSIZE) return ERROR;
	for (int j = L.length - 1; j >= i - 1; j--)
		L.elem[j + 1] = L.elem[j];
	L.elem[i - 1] = e;
	L.length++;
	return OK;
}

// 顺序表的删除
Status ListDelete_Sq(SqList& L, int i) {
	if (i < 1 || i > L.length + 1) return ERROR;
	for (int j = 1; j <= L.length - 1; j++)
		L.elem[j - 1] = L.elem[j];
	L.length--;
	return OK;
}

/* 单链表的基本操作实现 */
// 初始化单链表
Status InitList_L(LinkList& L) {
	L = new LNode;
	L->next = NULL;
	return OK;
}

// 判断链表是否为空
int ListEmpty(LinkList L) {
	if (L->next)
		return 0;
	else
		return 1;
}

// 销毁单链表L
Status DestroyList_L(LinkList& L) {
	LNode* p;
	while (L) {
		p = L;
		L = L->next;
		delete p;
	}
}

// 清空链表
Status ClearList(LinkList& L) {
	LNode* p,*q;
	p = L->next;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
	L->next = NULL;
	return OK;
}

// 求单链表的表长
int ListLength(LinkList L) {
	LinkList p;
	p = L->next;
	int i = 0;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

//按序号查找
Status GetElem_L(LinkList L, int i,ElemType& e) {
	LinkList p;
	p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

//按值查找
LNode* LocateElem_L_1(LinkList L, ElemType e) {
	LNode* p;
	p = L->next;
	while (p && p->data != e)
		p = p->next;
	return p;//返回地址
}
int LocateElem_L_2(LinkList L, ElemType e) {
	LNode* p;
	p = L->next;
	int j = 1;
	while (p && p->data != e) {
		p = p->next;
		j++;
	}
	if (p) return j;
	else return 0;//返回序号
}

//在第i个元素前插入数据元素e
Status ListInsert_L(LinkList& L, int i, ElemType e) {
	LNode* p = L;
	LNode* s;
	int j = 0;
	while (p && j < i - 1) {p = p->next; ++j;}//寻找第i-1个结点，p指向i-1结点
	if (!p || j > i - 1) return ERROR;//i大于表长+1或者小于1，插入位置非法
	s = new LNode;
	s->data = e;//生成新结点s，将结点s的数据域置为e
	s->next = p->next;//将结点s插入L中
	p->next = s;
	return OK;
}

//删除第i个结点
Status ListDelete_L(LinkList& L, int i, ElemType& e) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) { p = p->next; ++j; }//寻找第i个结点，并令p指向其前驱
	if (!(p->next) || j > i - 1)return ERROR;
	LNode* q;
	q = p->next;//临时保存被删结点的地址以备释放
	p->next = q->next;//改变删除结点前驱结点的指针域
	e = q->data;//保存删除结点的数据域
	delete q;//释放删除结点的空间
	return OK;
}

//修改第i个结点
Status ListRevise_L(LinkList& L, int i, ElemType e) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) { p = p->next; ++j; }//寻找第i个结点，并令p指向其前驱
	if (!(p->next) || j > i - 1)return ERROR;
	p->next-> data = e;
	return OK;
}

//建立单链表
//·头插法
void CreateList_H(LinkList& L, int n) {
	LNode* p;
	L = new LNode;
	L->next = NULL;//先建立一个带头结点的单链表
	for (int i = n; i > 0; --i) {
		p = new LNode;//生成新结点p
		cin >> p->data;//输入元素值
		p->next = L->next;
		L->next = p;
	}
}
//·尾插法
void CreateList_R(LinkList& L, int n) {
	L = new LNode;
	L->next = NULL;
	LNode* r = L;
	LNode* p;
	for (int i = 0; i < n; ++i) {
		p = new LNode;
		cin >> p->data;
		p->next = NULL;
		r->next = p;
		r = p;
	}
}

/* 循环链表 */
/* 从表中的任一结点出发均可找到表中其他结点.*/
//带尾指针循环链表的合并
LinkList Connect(LinkList Ta, LinkList Tb) {
	LinkList p;
	p = Ta->next;//p存表头结点
	Ta->next = Tb->next->next;//Tb表头连结Ta表尾
	delete Tb->next;//释放Tb表头结点
	Tb->next = p;//修改指针
	return Tb;
}
//建立循环链表
//·头插法
CircleNode* CreateCircleList_H()
{
	CircleNode* head, * node;
	head = new CircleNode;
	head->next = head;
	for (int i = 0; i < MAXSIZE; i++) {
		node = new CircleNode;
		node->data = i;
		node->next = head->next;
		head->next = node;
	}
	return head;
}
//尾插法
CircleNode* CreateCircleList_R()
{
	CircleNode* head, * node, * end;
	head = new CircleNode;
	head->next = head;
	end = head;
	for (int i = 0; i < MAXSIZE; i++) {
		node = new CircleNode;
		node->data = i;
		end->next = node;
		end = node;
	}
	end->next = head;
	return head;
}

//遍历循环链表
void OutputCircleLinkList(CircleLinkList L)
{
	CircleNode* head = L;
	L = L->next;
	while (L->next != head) {
		cout << L->data << endl;
		L = L->next;
	}
	cout << L->data << endl;
}

//获得链表结点大小（除去头结点）
int GetLength_C(CircleLinkList L)
{
	int num = 1;
	CircleNode* head = L;
	if (L->next == head) {
		cout << "链表的结点个数为0" << endl;
		return 0;
	}
	else {
		L = L->next;
		while (L->next != head) {
			num++;
			L = L->next;
		}
		cout << "链表的结点个数为" << num << endl;
		return num;
	}
}

//指定位置插入结点
void CircleListInsert(CircleLinkList major, CircleLinkList minior, int n)
{
	int size = GetLength_C(major);
	CircleNode* MajorHead = major;
	CircleNode* MiniorHead = minior;
	if (n >= size)//指定位置大于结点个数，直接插入到最后
	{
		// 获得major尾结点
		CircleNode* p = major->next;
		while (p->next != MajorHead) { p = p->next; }
		// 获得minior尾结点
		CircleNode* q = minior->next;
		while (q->next != MiniorHead) { q = q->next; }
		p->next = MiniorHead->next;// 将major尾结点 -> minior第二结点
		q->next = MajorHead; // 将minior尾结点 -> major头结点
		free(MiniorHead); //释放minior头结点
	}
	else {
		int num = 0;//计数器
		// 获取要插入的位置的结点
		while (major->next != MajorHead && num < n) {
			num++;
			major = major->next;
		}
		//获得minior尾结点
		while (minior->next != MiniorHead) { minior = minior->next; }
		if (num == n) {
			minior->next = major->next; // 将minior尾结点->major插入结点的位置
			major->next = MiniorHead->next; // 将major插入位置的结点->minior的头结点
			free(MiniorHead);
		}
	}
}
/* 双向链表 */
/* 双向链表结构的对称性：
p -> prior -> next 
= p 
= p -> next -> prior 
在插入/删除时，则需同时修改两个方向上的指针 */

//双向链表的插入
void ListInsert_Dul(DuLinkList& L/*, int i*/, ElemType e) {
	/* 将新元素插入到第i个元素之后
	*  假设第i个元素为a，第i+1个元素为b，要插入的元素为x，其地址为s.
	*  p是指向b的指针
	*/
	//if(!(p=GetElemP_Dul(L,i))) return ERROR;
	DulNode* s;
	s = new DulNode;
	s->data = e;
	s->prior = L->prior;//x的前驱要变成a结点，则s->prior=a.而a=p->prior
	L->prior->next = s;//a结点的后继要变成x.而a->next=p->prior->next
	s->next = L;//x的后继应为b.
	L->prior = s;//b的前驱应为x
}

//双向链表的删除
void ListDelet_Dul(DuLinkList& L, ElemType e) {
	//if(!(p=GetElemP_Dul(L,i))) return ERROR;
	DulNode* e;
	e = L->data;//存储P的数据防止后期使用
	L->prior->next = L->next;
	L->next->prior = L->prior;
	free(L);
}

/* 线性表的应用 */
//线性表的合并
//顺序表
void ListUnion_Sq(SqList& La, SqList& Lb,ElemType e) {
	int La_len, Lb_len;
	La_len = GetLength(La);
	Lb_len = GetLength(Lb);
	for (int i = 1; i <= Lb_len; i++) {
		GetElem(Lb, i, e);
		if (!LocateElem(La, e)) ListInsert_Sq(La, ++La_len, e);
	}
}

//有序表的合并
//顺序表
void MergeList_Sq(SqList La, SqList Lb, SqList& Lc) {
	ElemType* pa, * pb, * pc, * pa_last, * pb_last;
	pa = La.elem;
	pb = Lb.elem;						//指针pa、pb分别指向表中的第一个元素
	Lc.length = La.length + Lb.length;
	Lc.elem = new ElemType[Lc.length];
	pc = Lc.elem;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	/* 依次摘取两表中较小的结点，直到一方到达表尾 */
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	/* 将未达到表尾的剩余元素继续加入Lc中 */
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}

//链表
void MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc) {
	LinkList pa, pb, pc, pa_last, pb_last;
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;//用La的头结点作为Lc的头结点
	while (pa && pb) {
		if (pa->data <= pb->data) { pc->next = pa; pc = pa; pa = pa->next; }
		else { pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;
	delete Lb;
}
