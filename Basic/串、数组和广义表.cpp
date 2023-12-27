#include <iostream>
using namespace std;
#define MAXSIZE 255
#define CHUNKSIZE 80
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

/*	串：
*	零个或多个任意字符组成的有限序列
*	子串：一格串中任意个连续字符组成的子序列（含空串）称为该串的子串
*	真子串是不包含自身的所有子串
*/

// 串的顺序存储结构
typedef struct {
	char ch[MAXSIZE + 1]; //存储串的一维数组
	int length;//串的当前长度
}SString;

// 串的链式存储结构 ---- 块链结构
typedef struct Chunk{
	char ch[CHUNKSIZE];
	struct Chunk* next;
};

typedef struct {
	Chunk* head, * tail; // 串的头指针和尾指针
	int curlen; //串的当前长度
}LString; // 字符串的块链结构

//	串的模式匹配算法 
/*	---- BF算法
	将主串的第pos个字符和模式串的第一个字符比较，
	若相等，则继续逐个比较后续字符；
	若不等，从主串的下一字符起，重新与模式串的第一个字符比较 */
int Index_BF(SString S, SString T) {
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length) {
		if (S.ch[i] == T.ch[j]) { ++i; ++j; }// 主串和子串依次匹配下一个字符
		else { i = i - j + 2; j = 1; }// 主串、子串指针回溯重新开始下一次匹配
	}
	if (j >= T.length)return i - T.length;// 返回匹配的第一个字符下标
	else return 0;//模式匹配不成功
}

/*	---- KMP算法
	利用已经部分匹配的结果而加快模式串的滑动速度
	且主串的指针i不必回溯，可以提速到O(n+m)*/

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
			j = next[j];/* i不变，j后退 */
	}
	if (j > T.length)return i - T.length;
	else return 0;
}

/*	数组：
*	按一定格式排列起来的具有相同类型的数据元素的集合
*	一维数组：若线性表钟的数据元素为非结构的简单元素，则称为一维数组
*	一维数组的逻辑结构：线性结构--定长的线性表。
*	二维数组：若一维数组的数据元素又是一维数组结构，则成为二维数组
*	二维数组的逻辑结构：非线性结构：每一个元素既在一个行表中，又在一个列表中
*					 线性结构：定长的线性表
*/

/*	特殊矩阵的压缩存储
*	1.对称矩阵：
*		只存储下（或者上）三角（包括主对角线）的数据元素。
*		共占用n(n+1)/2个元素空间。
*	·可以以行序为主序将元素存放在一个一维数组sa[n(n+1)/2]中
*	2.三角矩阵
*		重复元素c共享一个元素存储空间，共占用n(n+1)/2+1个元素
*	3.对角矩阵（带状矩阵）
*		以对角线的顺序存储
*/

/*	稀疏矩阵的存储
*	稀疏矩阵的压缩存储方法 ---- 顺序存储结构
*	1.三元组顺序表
*		利用col row value进行行列值存储
*	2.十字链表
*		除了row col value以外，还有rigt\down;
*		right:用于链接同一行中的下一个非零元素;
*		down:用以链接同一列中的下一个非零元素。
*/

/*	广义表（又称列表Lists）是n>=0个元素的有限序列，
*	其中每一个a或是原子，或者是一个广义表
*	广义表中的数据元素有相对次序；一个前驱和一个直接后继
*	广义表的长度定义为最外层所包含的元素个数
*	广义表的深度定义为该广义表展开后所含括号的重数
*	广义表可以为其他广义表共享，如B=(A);
*	广义表可以是一个递归的表。递归表的深度是无穷值，长度是有限值
*	广义表是多层次结构-广义表的元素可以是单元素，也可以是子表
*/
 