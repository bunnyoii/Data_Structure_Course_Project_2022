#include <iostream>
#include "Expression Tree.h"

#define MAX_SIZE 100
typedef class ExpressionTree :public MyBinaryTree<char> {
private:
	char expr[MAX_SIZE];
	char parsedExpr[MAX_SIZE];
public:
	void menu();
	void enterExpression();
	void operation();
	// 是否是运算符
	bool isOperator(char token) { return (token == '+' || token == '-' || token == '*' || token == '/'); }
	// 是否是数字/变量
	bool isOperand(char c) { return c >= '0' && c <= '9'; }
	// 运算符优先级
	int precedence(char op) {
		if (op == '+' || op == '-') return 1;
		if (op == '*' || op == '/') return 2;
		return 0;
	}
	// 解析表达式：中缀->后缀
	void parseExpression();
	// 构建表达式树
	void buildExpressionTree();
	char evaluateExpressionTree(TreeNode<char>* node);
	void Exit() {
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
		std::cin.get();
	}
}ET;

// 菜单
void ExpressionTree::menu()
{
	std::cout << "····················\n";
	std::cout << "·             表达式计算             ·\n";
	std::cout << "·  Arithmetic Expression Evaluation  ·\n";
	std::cout << "····················\n\n";
}

// 输出操作界面
void ExpressionTree::operation()
{
	std::cout << "\n波兰表达式：";
    preOrder(root);
	std::cout << std::endl;
	std::cout << "\n中缀表达式：";
    // inOrder(root);
	for (int i = 0; expr[i] != '\0'; i++)
		std::cout<<expr[i] << ' ';
	std::cout << std::endl;
	std::cout << "\n逆波兰表达式：";
    postOrder(root);
	std::cout << std::endl;
	std::cout << "\n表达式的值为：";
	int result = evaluateExpressionTree(root);
	std::cout << result;
	std::cout << std::endl;
	Exit();
}

// 输入表达式
void ExpressionTree::enterExpression()
{
	std::cout << "************         注意 表达式输入要求         ************\n";
	std::cout << "**    ·只可输入数字和+ - * / ( )                          **\n";
	std::cout << "**    ·不可输入超过100个字符否则不计入                    **\n";
	std::cout << "**    ·本程序只适用于计算个位数运算，不可输入两位数及以上 **\n";
	std::cout << "**********  WARNING Expression Input Requirements  **********\n\n";
	std::cout << ">>>请输入表达式：";
	std::cin.getline(expr, MAX_SIZE);
	parseExpression();
    buildExpressionTree();
}

// 解析表达式 中缀->后缀
void ExpressionTree::parseExpression()
{
	Stack<char> opStack;		// 存储操作符
	int parsedIndex = 0;		// 输出字符串的当前索引
	for (int i = 0; expr[i] != '\0'; i++) {
		char token = expr[i];
		if (isOperand(token)) {
			// 如果是操作数，直接输出到parsedExpr
			parsedExpr[parsedIndex++] = token;
		}
		else if (token == '(') { opStack.Push(token); }
		else if (token == ')') {
			while (!opStack.IsEmpty() && opStack.GetTop() != '(') { parsedExpr[parsedIndex++] = opStack.Pop(); }
			opStack.Pop(); // 弹出左括号
		}
		else if (isOperator(token)) {
			// 遇到操作符
			while (!opStack.IsEmpty() && precedence(opStack.GetTop()) >= precedence(token)) {
				parsedExpr[parsedIndex++] = opStack.Pop();
			}
			opStack.Push(token);
		}
	}

	// 将栈中剩余的操作符输出到parsedExpr
	while (!opStack.IsEmpty()) {
		parsedExpr[parsedIndex++] = opStack.Pop();
	}
	parsedExpr[parsedIndex] = '\0'; // 以空字符结束字符串
}

// 构建表达式树
void ExpressionTree::buildExpressionTree() {
	Stack<TreeNode<char>*> nodeStack; // 栈存储树节点

	for (int i = 0; parsedExpr[i] != '\0'; i++) {
		char token = parsedExpr[i];
		if (isOperand(token)) {
			// 操作数 -> 创建一个节点并压入栈
			TreeNode<char>* operandNode = new TreeNode<char>(token);
			nodeStack.Push(operandNode);
		}
		else if (isOperator(token)) {
			// 操作符 -> 栈中弹出两个节点作为子节点
			TreeNode<char>* rightChild = NULL;
			TreeNode<char>* leftChild = NULL;
			// 右子节点	
			if (!nodeStack.IsEmpty()) { rightChild = nodeStack.Pop();}
			// 左子节点
			if (!nodeStack.IsEmpty()) { leftChild = nodeStack.Pop();}

			TreeNode<char>* operatorNode = new TreeNode<char>(token, leftChild, rightChild);
			nodeStack.Push(operatorNode); // 将操作符节点压入栈
		}
		// 不在这里弹出栈顶元素
	}

	// 循环结束后，栈顶元素即为表达树根节点
	if (!nodeStack.IsEmpty()) {
		root = nodeStack.Pop();
	}
}

// 计算表达式
char ExpressionTree::evaluateExpressionTree(TreeNode<char>* node)
{
	// 检查节点是否为空
	if (node == nullptr) {
		return 0; // 或者抛出异常
	}

	// 如果是叶子节点（操作数），直接返回其数值
	if (!isOperator(node->value)) {
		return node->value - '0'; // 将字符转换为整数
	}

	// 递归计算左右子树
	char left = evaluateExpressionTree(node->firstChild);
	char right = evaluateExpressionTree(node->nextSibling);

	// 根据操作符执行相应的运算
	switch (node->value) {
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		// 注意处理除数为0的情况
		if (right == 0) {
			throw std::runtime_error("Division by zero");
		}
		return left / right;
	default:
		// 处理未知操作符
		throw std::runtime_error("Unknown operator");
	}
}

int main()
{
	ET Solution;
	Solution.menu();
	Solution.enterExpression();
	Solution.operation();
}