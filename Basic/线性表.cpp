#include <iostream>

using namespace std;
#define MAXSIZE 10
/* �����㷨���õ���Ԥ���峣�������� */
//�������״̬����
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	
#define OVERFLOW		-2

//startus �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char ElemType;


/* ˳���Ľ��� */
typedef struct {
	ElemType* elem;
	int length;
}SqList;

/* ����Ľ��� */
typedef struct LNode{
	ElemType data;//����������
	struct LNode* next;//����ָ����
} *LinkList;

/* ˫������Ľ��� */
typedef struct DulNode {
	ElemType data;
	struct DulNode* prior, * next;
}*DuLinkList;

/* ѭ������Ľ��� */
typedef struct CircleNode {
	ElemType data;
	struct CircleNode* next;
}*CircleLinkList;

/* ˳���Ļ���������ʵ�� */
//���Ա�L�ĳ�ʼ�������������ã�
Status InitList_Sq(SqList& L) {	//����һ���յ�˳���L
	L.elem = new ElemType[MAXSIZE];//Ϊ˳������ռ�
	if (!L.elem) exit(OVERFLOW);//�洢����ʧ��
	L.length = 0;//�ձ���Ϊ0
	return OK;
}

//�������Ա�L
void DestroyList(SqList& L) {
	if (L.elem)
		delete L.elem;
}

//������Ա�L
void ClearList(SqList& L) {
	L.length = 0;
}

//�����Ա�ĳ���
int GetLength(SqList L) {
	return(L.length);
}

//�ж����Ա�L�Ƿ�Ϊ��
int IsEmpty(SqList L) {
	if (L.length == 0) return 1;
	else return 0;
}

//˳����ȡֵ������λ��i��ȡ��Ӧλ������Ԫ�ص����ݣ�
int GetElem(SqList L, int i, ElemType& e) {
	if (i<1 || i>L.length) return ERROR;//�ж�i�Ƿ����
	e = L.elem[i - 1];//��i-1�ĵ�Ԫ�洢��i������
	return OK;
}

//˳���Ĳ����㷨
int LocateElem(SqList L, ElemType e) {
	//�����Ա�L�в���ֵΪe������Ԫ�أ����������
	for (int i = 0; i < L.length; i++)
		if (L.elem[i] == e) return i + 1;
	return 0;
}

//˳���Ĳ���
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length == MAXSIZE) return ERROR;
	for (int j = L.length - 1; j >= i - 1; j--)
		L.elem[j + 1] = L.elem[j];
	L.elem[i - 1] = e;
	L.length++;
	return OK;
}

// ˳����ɾ��
Status ListDelete_Sq(SqList& L, int i) {
	if (i < 1 || i > L.length + 1) return ERROR;
	for (int j = 1; j <= L.length - 1; j++)
		L.elem[j - 1] = L.elem[j];
	L.length--;
	return OK;
}

/* ������Ļ�������ʵ�� */
// ��ʼ��������
Status InitList_L(LinkList& L) {
	L = new LNode;
	L->next = NULL;
	return OK;
}

// �ж������Ƿ�Ϊ��
int ListEmpty(LinkList L) {
	if (L->next)
		return 0;
	else
		return 1;
}

// ���ٵ�����L
Status DestroyList_L(LinkList& L) {
	LNode* p;
	while (L) {
		p = L;
		L = L->next;
		delete p;
	}
}

// �������
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

// ������ı�
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

//����Ų���
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

//��ֵ����
LNode* LocateElem_L_1(LinkList L, ElemType e) {
	LNode* p;
	p = L->next;
	while (p && p->data != e)
		p = p->next;
	return p;//���ص�ַ
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
	else return 0;//�������
}

//�ڵ�i��Ԫ��ǰ��������Ԫ��e
Status ListInsert_L(LinkList& L, int i, ElemType e) {
	LNode* p = L;
	LNode* s;
	int j = 0;
	while (p && j < i - 1) {p = p->next; ++j;}//Ѱ�ҵ�i-1����㣬pָ��i-1���
	if (!p || j > i - 1) return ERROR;//i���ڱ�+1����С��1������λ�÷Ƿ�
	s = new LNode;
	s->data = e;//�����½��s�������s����������Ϊe
	s->next = p->next;//�����s����L��
	p->next = s;
	return OK;
}

//ɾ����i�����
Status ListDelete_L(LinkList& L, int i, ElemType& e) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) { p = p->next; ++j; }//Ѱ�ҵ�i����㣬����pָ����ǰ��
	if (!(p->next) || j > i - 1)return ERROR;
	LNode* q;
	q = p->next;//��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
	p->next = q->next;//�ı�ɾ�����ǰ������ָ����
	e = q->data;//����ɾ������������
	delete q;//�ͷ�ɾ�����Ŀռ�
	return OK;
}

//�޸ĵ�i�����
Status ListRevise_L(LinkList& L, int i, ElemType e) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) { p = p->next; ++j; }//Ѱ�ҵ�i����㣬����pָ����ǰ��
	if (!(p->next) || j > i - 1)return ERROR;
	p->next-> data = e;
	return OK;
}

//����������
//��ͷ�巨
void CreateList_H(LinkList& L, int n) {
	LNode* p;
	L = new LNode;
	L->next = NULL;//�Ƚ���һ����ͷ���ĵ�����
	for (int i = n; i > 0; --i) {
		p = new LNode;//�����½��p
		cin >> p->data;//����Ԫ��ֵ
		p->next = L->next;
		L->next = p;
	}
}
//��β�巨
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

/* ѭ������ */
/* �ӱ��е���һ�����������ҵ������������.*/
//��βָ��ѭ������ĺϲ�
LinkList Connect(LinkList Ta, LinkList Tb) {
	LinkList p;
	p = Ta->next;//p���ͷ���
	Ta->next = Tb->next->next;//Tb��ͷ����Ta��β
	delete Tb->next;//�ͷ�Tb��ͷ���
	Tb->next = p;//�޸�ָ��
	return Tb;
}
//����ѭ������
//��ͷ�巨
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
//β�巨
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

//����ѭ������
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

//����������С����ȥͷ��㣩
int GetLength_C(CircleLinkList L)
{
	int num = 1;
	CircleNode* head = L;
	if (L->next == head) {
		cout << "����Ľ�����Ϊ0" << endl;
		return 0;
	}
	else {
		L = L->next;
		while (L->next != head) {
			num++;
			L = L->next;
		}
		cout << "����Ľ�����Ϊ" << num << endl;
		return num;
	}
}

//ָ��λ�ò�����
void CircleListInsert(CircleLinkList major, CircleLinkList minior, int n)
{
	int size = GetLength_C(major);
	CircleNode* MajorHead = major;
	CircleNode* MiniorHead = minior;
	if (n >= size)//ָ��λ�ô��ڽ�������ֱ�Ӳ��뵽���
	{
		// ���majorβ���
		CircleNode* p = major->next;
		while (p->next != MajorHead) { p = p->next; }
		// ���miniorβ���
		CircleNode* q = minior->next;
		while (q->next != MiniorHead) { q = q->next; }
		p->next = MiniorHead->next;// ��majorβ��� -> minior�ڶ����
		q->next = MajorHead; // ��miniorβ��� -> majorͷ���
		free(MiniorHead); //�ͷ�miniorͷ���
	}
	else {
		int num = 0;//������
		// ��ȡҪ�����λ�õĽ��
		while (major->next != MajorHead && num < n) {
			num++;
			major = major->next;
		}
		//���miniorβ���
		while (minior->next != MiniorHead) { minior = minior->next; }
		if (num == n) {
			minior->next = major->next; // ��miniorβ���->major�������λ��
			major->next = MiniorHead->next; // ��major����λ�õĽ��->minior��ͷ���
			free(MiniorHead);
		}
	}
}
/* ˫������ */
/* ˫������ṹ�ĶԳ��ԣ�
p -> prior -> next 
= p 
= p -> next -> prior 
�ڲ���/ɾ��ʱ������ͬʱ�޸����������ϵ�ָ�� */

//˫������Ĳ���
void ListInsert_Dul(DuLinkList& L/*, int i*/, ElemType e) {
	/* ����Ԫ�ز��뵽��i��Ԫ��֮��
	*  �����i��Ԫ��Ϊa����i+1��Ԫ��Ϊb��Ҫ�����Ԫ��Ϊx�����ַΪs.
	*  p��ָ��b��ָ��
	*/
	//if(!(p=GetElemP_Dul(L,i))) return ERROR;
	DulNode* s;
	s = new DulNode;
	s->data = e;
	s->prior = L->prior;//x��ǰ��Ҫ���a��㣬��s->prior=a.��a=p->prior
	L->prior->next = s;//a���ĺ��Ҫ���x.��a->next=p->prior->next
	s->next = L;//x�ĺ��ӦΪb.
	L->prior = s;//b��ǰ��ӦΪx
}

//˫�������ɾ��
void ListDelet_Dul(DuLinkList& L, ElemType e) {
	//if(!(p=GetElemP_Dul(L,i))) return ERROR;
	DulNode* e;
	e = L->data;//�洢P�����ݷ�ֹ����ʹ��
	L->prior->next = L->next;
	L->next->prior = L->prior;
	free(L);
}

/* ���Ա��Ӧ�� */
//���Ա�ĺϲ�
//˳���
void ListUnion_Sq(SqList& La, SqList& Lb,ElemType e) {
	int La_len, Lb_len;
	La_len = GetLength(La);
	Lb_len = GetLength(Lb);
	for (int i = 1; i <= Lb_len; i++) {
		GetElem(Lb, i, e);
		if (!LocateElem(La, e)) ListInsert_Sq(La, ++La_len, e);
	}
}

//�����ĺϲ�
//˳���
void MergeList_Sq(SqList La, SqList Lb, SqList& Lc) {
	ElemType* pa, * pb, * pc, * pa_last, * pb_last;
	pa = La.elem;
	pb = Lb.elem;						//ָ��pa��pb�ֱ�ָ����еĵ�һ��Ԫ��
	Lc.length = La.length + Lb.length;
	Lc.elem = new ElemType[Lc.length];
	pc = Lc.elem;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	/* ����ժȡ�����н�С�Ľ�㣬ֱ��һ�������β */
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	/* ��δ�ﵽ��β��ʣ��Ԫ�ؼ�������Lc�� */
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}

//����
void MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc) {
	LinkList pa, pb, pc, pa_last, pb_last;
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;//��La��ͷ�����ΪLc��ͷ���
	while (pa && pb) {
		if (pa->data <= pb->data) { pc->next = pa; pc = pa; pa = pa->next; }
		else { pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;
	delete Lb;
}
