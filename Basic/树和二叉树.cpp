#include <iostream>

using namespace std;
typedef int TElemType;
typedef int Status;
#define MAXSIZE 100
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	
#define OVERFLOW		-2
/*	树
*	树(Tree)是n(n>=0)个结点的有限集。
*	若n = 0，则为空树；
*	若n > 0,则它满足如下两个条件：
*	(1)有且仅有一个特定的称为根(Root)的结点；
*	(2)其余结点可分为m(m>=0)个互不相交的有限集T1,T2,T3...,Tm，
*	   其中每一个集合本身又是一棵树，并称为根的子树(SubTree)
*/

/*	树的基本术语
*	根结点：非空树中无前驱结点的结点
*		结点的度：结点拥有的子树数
*	度 = 0：叶子(终端结点)
*	度 != 0：分支节点(非终端结点)--根结点以外的分支结点称为内部结点
*	树的度：树内各结点的度的最大值。
*	结点的子树的根称为该结点的孩子，该结点称为孩子的双亲
*	树的深度：树中结点的最大层次
*	有序树：树中结点的各子树从左至右有次序(最左边为第一个孩子)
*	无序树：树中结点的各子树无次序
*	森林：是m(m>=0)棵互不相交的树的集合
*	把根结点删除树就变成了森林
*	一棵树可以看作一个特殊的森林
*	给森林中的各子树加上一个双亲结点，森林就变成了树
*/

/*	二叉树
*	二叉树是n(n>=0)个结点的有限集，它或者是空集(n = 0),
*	或者是由一个根结点及两棵互不相交的
*	分别称作这个根的左子树和右子树的二叉树组成
* 
*	特点：
*	1.每个结点最多有俩孩子(二叉树中不存在度大于2的结点)
*	2.子树有左右之分，其次序不能颠倒。
*	3.二叉树可以是空集合，根可以有空的左子树或空的右子树
* 
*	二叉树的五种基本形态：
*	空二叉树   根和空的左右子树   根和左子树   根和右子树   根和左右子树
*/

/*	二叉树的抽象数据类型定义 */
/*	ADT BinaryTree{
*	数据对象D：	D是具有相同特性的数据元素的集合
*	数据关系R：	若D非空，则R = {H}；H是如下二元关系“
*				1.root唯一		//关于根的说明
*				2.Dj交Dk为空		//关于子树不相交的说明
*				3....			//关于数据元素的说明
*				4....			//关于左子树和右子树的说明
*	基本操作P：	CreateBiTree(&T,definition)
*	}ADT BinaryTree
*/

/*	二叉树的性质和存储结构	
*	1.在二叉树的第i层上至多右2^i-1个结点(i>=1)，至少有1个结点
*	2.深度为k的二叉树至多有2^k - 1个结点(k>=1)，至少有k个结点
*	3.对任何一棵二叉树T，如果其叶子数为n0，度为2的结点数为n2，则n0=n2+1
*	4.具有n个结点的完全二叉树的深度为[log2 n] + 1
*	5.如果对一棵树有n个结点的完全二叉树的结点按层序编号(从第1层到第[log2 n] + 1层，每层从左到右)
*	  则对任一结点i(1<=i<=n)，有：
*		(1)如果i = 1,则结点i是二叉树的根，无双亲；
*		   如果i > 1，则其双亲是结点[i / 2]。
*		(2)如果2i > n，则结点i为叶子结点，无左孩子，否则，其左孩子结点为
*/

// 二叉链表
// 在n个结点的二叉链表中，有n+1个空指针域
typedef struct BiNode {
	TElemType data;
	struct BiNode* lchild, * rchild;//左右孩子指针
}BiNode, * BiTree;

// 三叉链表
// 多了一个指向父母的指针
typedef struct TriTNode {
	TElemType data;
	struct TriTNode* lchild, * parent, * rchild;
}TriTNode, * TriTree;

/* 遍历二叉树 */
/* DLR - 先序遍历
*  LDR - 中序遍历
*  LRD - 后序遍历*/
// 二叉树先序遍历算法
Status PreOrderTraverse(BiTree T) {
	if (T == NULL)return OK;//空二叉树
	else {
		//visit(T);	//访问根节点
		PreOrderTraverse(T->lchild);//递归遍历左子树
		PreOrderTraverse(T->rchild);//递归遍历右子树

	}
}
