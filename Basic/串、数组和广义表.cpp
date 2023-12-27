#include <iostream>
using namespace std;
#define MAXSIZE 255
#define CHUNKSIZE 80
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

/*	����
*	������������ַ���ɵ���������
*	�Ӵ���һ��������������ַ���ɵ������У����մ�����Ϊ�ô����Ӵ�
*	���Ӵ��ǲ���������������Ӵ�
*/

// ����˳��洢�ṹ
typedef struct {
	char ch[MAXSIZE + 1]; //�洢����һά����
	int length;//���ĵ�ǰ����
}SString;

// ������ʽ�洢�ṹ ---- �����ṹ
typedef struct Chunk{
	char ch[CHUNKSIZE];
	struct Chunk* next;
};

typedef struct {
	Chunk* head, * tail; // ����ͷָ���βָ��
	int curlen; //���ĵ�ǰ����
}LString; // �ַ����Ŀ����ṹ

//	����ģʽƥ���㷨 
/*	---- BF�㷨
	�������ĵ�pos���ַ���ģʽ���ĵ�һ���ַ��Ƚϣ�
	����ȣ����������ȽϺ����ַ���
	�����ȣ�����������һ�ַ���������ģʽ���ĵ�һ���ַ��Ƚ� */
int Index_BF(SString S, SString T) {
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length) {
		if (S.ch[i] == T.ch[j]) { ++i; ++j; }// �������Ӵ�����ƥ����һ���ַ�
		else { i = i - j + 2; j = 1; }// �������Ӵ�ָ��������¿�ʼ��һ��ƥ��
	}
	if (j >= T.length)return i - T.length;// ����ƥ��ĵ�һ���ַ��±�
	else return 0;//ģʽƥ�䲻�ɹ�
}

/*	---- KMP�㷨
	�����Ѿ�����ƥ��Ľ�����ӿ�ģʽ���Ļ����ٶ�
	��������ָ��i���ػ��ݣ��������ٵ�O(n+m)*/

void get_next(SString T, int*& next)
{
	next = new int[T.length + 1];
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T.length) {
		if (j == 0 || T.ch[i] == T.ch[j]) {
			++i; ++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

void get_nextval(SString T, int (&nextval)[])
{
	int i = 1;
	nextval[1] = 0; 
	int j = 0;
	while (i < T.length) {
		if (j == 0 || T.ch[i] == T.ch[j]) {
			++i; ++j;
			if (T.ch[i] != T.ch[j])nextval[i] = j;
			else nextval[i] == nextval[j];
		}
		else j = nextval[j];
	}
}

int Index_KMP(SString S, SString T, int pos)
{
	int i = pos, j = 1;
	int* next;
	get_next(T, next);
	while (i < S.length && j < T.length) {
		if (j == 0 || S.ch[i] == T.ch[i]) { i++; j++; }
		else
			j = next[j];/* i���䣬j���� */
	}
	if (j > T.length)return i - T.length;
	else return 0;
}

/*	���飺
*	��һ����ʽ���������ľ�����ͬ���͵�����Ԫ�صļ���
*	һά���飺�����Ա��ӵ�����Ԫ��Ϊ�ǽṹ�ļ�Ԫ�أ����Ϊһά����
*	һά������߼��ṹ�����Խṹ--���������Ա�
*	��ά���飺��һά���������Ԫ������һά����ṹ�����Ϊ��ά����
*	��ά������߼��ṹ�������Խṹ��ÿһ��Ԫ�ؼ���һ���б��У�����һ���б���
*					 ���Խṹ�����������Ա�
*/

/*	��������ѹ���洢
*	1.�Գƾ���
*		ֻ�洢�£������ϣ����ǣ��������Խ��ߣ�������Ԫ�ء�
*		��ռ��n(n+1)/2��Ԫ�ؿռ䡣
*	������������Ϊ����Ԫ�ش����һ��һά����sa[n(n+1)/2]��
*	2.���Ǿ���
*		�ظ�Ԫ��c����һ��Ԫ�ش洢�ռ䣬��ռ��n(n+1)/2+1��Ԫ��
*	3.�ԽǾ��󣨴�״����
*		�ԶԽ��ߵ�˳��洢
*/

/*	ϡ�����Ĵ洢
*	ϡ������ѹ���洢���� ---- ˳��洢�ṹ
*	1.��Ԫ��˳���
*		����col row value��������ֵ�洢
*	2.ʮ������
*		����row col value���⣬����rigt\down;
*		right:��������ͬһ���е���һ������Ԫ��;
*		down:��������ͬһ���е���һ������Ԫ�ء�
*/

/*	������ֳ��б�Lists����n>=0��Ԫ�ص��������У�
*	����ÿһ��a����ԭ�ӣ�������һ�������
*	������е�����Ԫ������Դ���һ��ǰ����һ��ֱ�Ӻ��
*	�����ĳ��ȶ���Ϊ�������������Ԫ�ظ���
*	��������ȶ���Ϊ�ù����չ�����������ŵ�����
*	��������Ϊ�������������B=(A);
*	����������һ���ݹ�ı��ݹ������������ֵ������������ֵ
*	������Ƕ��νṹ-������Ԫ�ؿ����ǵ�Ԫ�أ�Ҳ�������ӱ�
*/
 