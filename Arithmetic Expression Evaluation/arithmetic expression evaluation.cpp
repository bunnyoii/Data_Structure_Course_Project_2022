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
	// �Ƿ��������
	bool isOperator(char token) { return (token == '+' || token == '-' || token == '*' || token == '/'); }
	// �Ƿ�������/����
	bool isOperand(char c) { return c >= '0' && c <= '9'; }
	// ��������ȼ�
	int precedence(char op) {
		if (op == '+' || op == '-') return 1;
		if (op == '*' || op == '/') return 2;
		return 0;
	}
	// �������ʽ����׺->��׺
	void parseExpression();
	// �������ʽ��
	void buildExpressionTree();
	char evaluateExpressionTree(TreeNode<char>* node);
	void Exit() {
		std::cout << "�����������...\n";
		// ������뻺����
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// �ȴ��û�����
		std::cin.get();
	}
}ET;

// �˵�
void ExpressionTree::menu()
{
	std::cout << "����������������������������������������\n";
	std::cout << "��             ���ʽ����             ��\n";
	std::cout << "��  Arithmetic Expression Evaluation  ��\n";
	std::cout << "����������������������������������������\n\n";
}

// �����������
void ExpressionTree::operation()
{
	std::cout << "\n�������ʽ��";
    preOrder(root);
	std::cout << std::endl;
	std::cout << "\n��׺���ʽ��";
    // inOrder(root);
	for (int i = 0; expr[i] != '\0'; i++)
		std::cout<<expr[i] << ' ';
	std::cout << std::endl;
	std::cout << "\n�沨�����ʽ��";
    postOrder(root);
	std::cout << std::endl;
	std::cout << "\n���ʽ��ֵΪ��";
	int result = evaluateExpressionTree(root);
	std::cout << result;
	std::cout << std::endl;
	Exit();
}

// ������ʽ
void ExpressionTree::enterExpression()
{
	std::cout << "************         ע�� ���ʽ����Ҫ��         ************\n";
	std::cout << "**    ��ֻ���������ֺ�+ - * / ( )                          **\n";
	std::cout << "**    ���������볬��100���ַ����򲻼���                    **\n";
	std::cout << "**    ��������ֻ�����ڼ����λ�����㣬����������λ�������� **\n";
	std::cout << "**********  WARNING Expression Input Requirements  **********\n\n";
	std::cout << ">>>��������ʽ��";
	std::cin.getline(expr, MAX_SIZE);
	parseExpression();
    buildExpressionTree();
}

// �������ʽ ��׺->��׺
void ExpressionTree::parseExpression()
{
	Stack<char> opStack;		// �洢������
	int parsedIndex = 0;		// ����ַ����ĵ�ǰ����
	for (int i = 0; expr[i] != '\0'; i++) {
		char token = expr[i];
		if (isOperand(token)) {
			// ����ǲ�������ֱ�������parsedExpr
			parsedExpr[parsedIndex++] = token;
		}
		else if (token == '(') { opStack.Push(token); }
		else if (token == ')') {
			while (!opStack.IsEmpty() && opStack.GetTop() != '(') { parsedExpr[parsedIndex++] = opStack.Pop(); }
			opStack.Pop(); // ����������
		}
		else if (isOperator(token)) {
			// ����������
			while (!opStack.IsEmpty() && precedence(opStack.GetTop()) >= precedence(token)) {
				parsedExpr[parsedIndex++] = opStack.Pop();
			}
			opStack.Push(token);
		}
	}

	// ��ջ��ʣ��Ĳ����������parsedExpr
	while (!opStack.IsEmpty()) {
		parsedExpr[parsedIndex++] = opStack.Pop();
	}
	parsedExpr[parsedIndex] = '\0'; // �Կ��ַ������ַ���
}

// �������ʽ��
void ExpressionTree::buildExpressionTree() {
	Stack<TreeNode<char>*> nodeStack; // ջ�洢���ڵ�

	for (int i = 0; parsedExpr[i] != '\0'; i++) {
		char token = parsedExpr[i];
		if (isOperand(token)) {
			// ������ -> ����һ���ڵ㲢ѹ��ջ
			TreeNode<char>* operandNode = new TreeNode<char>(token);
			nodeStack.Push(operandNode);
		}
		else if (isOperator(token)) {
			// ������ -> ջ�е��������ڵ���Ϊ�ӽڵ�
			TreeNode<char>* rightChild = NULL;
			TreeNode<char>* leftChild = NULL;
			// ���ӽڵ�	
			if (!nodeStack.IsEmpty()) { rightChild = nodeStack.Pop();}
			// ���ӽڵ�
			if (!nodeStack.IsEmpty()) { leftChild = nodeStack.Pop();}

			TreeNode<char>* operatorNode = new TreeNode<char>(token, leftChild, rightChild);
			nodeStack.Push(operatorNode); // ���������ڵ�ѹ��ջ
		}
		// �������ﵯ��ջ��Ԫ��
	}

	// ѭ��������ջ��Ԫ�ؼ�Ϊ��������ڵ�
	if (!nodeStack.IsEmpty()) {
		root = nodeStack.Pop();
	}
}

// ������ʽ
char ExpressionTree::evaluateExpressionTree(TreeNode<char>* node)
{
	// ���ڵ��Ƿ�Ϊ��
	if (node == nullptr) {
		return 0; // �����׳��쳣
	}

	// �����Ҷ�ӽڵ㣨����������ֱ�ӷ�������ֵ
	if (!isOperator(node->value)) {
		return node->value - '0'; // ���ַ�ת��Ϊ����
	}

	// �ݹ������������
	char left = evaluateExpressionTree(node->firstChild);
	char right = evaluateExpressionTree(node->nextSibling);

	// ���ݲ�����ִ����Ӧ������
	switch (node->value) {
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		// ע�⴦�����Ϊ0�����
		if (right == 0) {
			throw std::runtime_error("Division by zero");
		}
		return left / right;
	default:
		// ����δ֪������
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