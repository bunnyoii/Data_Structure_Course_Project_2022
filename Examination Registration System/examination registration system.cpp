#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <conio.h>

/* 操作算法中用到的预定义常量和类型 */
// 函数结果状态代码
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

// startus 是函数的类型，其值是函数结果状态代码
typedef int Status;
const int maxLength = (int)1e6;
const int minLength = 1;
const int maxAge = 35;
const int minAge = 18;
const int maxCategoryLength = 18;
const int maxSexLength = 3;
const int maxNameLength = 18;

/* 建立结构体存储考生信息 */
typedef struct studentInformation {
	int examNum;
	char name[maxNameLength];
	char sex[maxSexLength];
	int age;
	char applicationCategory[maxCategoryLength];
}SI;

/* 建立链表存储统计的报考类别信息 */
typedef struct ApplicationCategoryCount {
	char category[maxCategoryLength];
	int count;
	ApplicationCategoryCount* next;
}ACC;

/* 链表的建立 */
// 存储考生信息
typedef struct LNode {
	SI data;//结点的数据域
	struct LNode* next;//结点的指针域
} *LinkList;

/* getline函数自我实现 */
int myGetline(char s[], int lim)
{
	int c, i;// getchar()返回值为int型，故c用int型定义
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

class solution {
private:
	LNode* studentList;
	SI getStudentData;
	ACC* categoryCounts = nullptr;
	int personNum;//总人数
	int opt;//输入的操作数
	int operationNum;//输入的考号
	int locationNum;//输入的位置序号
	int operationLocation;//输入的考号所对应的位置序号
	int femaleNum = 0;//女性人数
	int maleNum = 0;//男性人数
	int searchExamNum = 0;//需要查找的学生的考号
	bool NumorInformation;//查找元素时需要返回序号还是值

public:
	// 初始化链表
	Status InitList() {
		studentList = new LNode;
		studentList->next = NULL;
		return OK;
	}
	~solution() {
		DestroyList();
	}
	// 销毁单链表L
	Status DestroyList() {
		LNode* p;
		while (studentList) {
			p = studentList;
			studentList = studentList->next;
			delete p;
		}
		return OK;
	}
	// 判断链表是否为空
	bool listEmpty() {
		if (studentList->next)
			return 0;
		else
			return 1;
	}
	// 输出考生信息
	void showData(SI studentData, bool opt) {
		if (opt) {
			std::cout << "| " << std::setw(18) << std::left << studentData.examNum;
			std::cout << "| " << std::setw(18) <<std::left << studentData.name;
			std::cout << "| " << std::setw(18) <<std::left << studentData.sex;
			std::cout << "| " << std::setw(18) <<std::left << studentData.age;
			std::cout << "| " << std::setw(18) <<std::left << studentData.applicationCategory;
			std::cout << "|\n";
		}
		else {
			std::cout << std::setw(18) <<std::left << studentData.examNum;
			std::cout << std::setw(18) <<std::left << studentData.name;
			std::cout << std::setw(18) <<std::left << studentData.sex;
			std::cout << std::setw(18) <<std::left << studentData.age;
			std::cout << std::setw(18) <<std::left << studentData.applicationCategory << std::endl;
		}
	}
	Status listInsert();
	Status listDelete();
	int getElem(bool InformationorNum);
	Status listRevise();
	void deletRepetitiveList();
	int listLength();
	void statsSexDistribution();
	void statsAge();
	void countApplicationCategory();
	void statsInformation();
	void createList();
	void inputPersonNum();
	bool inputPersonInformation(SI& studentData);
	void inputOperationLocation();
	void inputOperationNum();
	bool option();
	void output(bool opt);
};

/***************************************************************************
  函数名称：	deletRepetitiveList函数
  输入参数：	无
  功   能：	进行双重循环遍历，外循环当前遍历的结点为cur，内循环从cur开始遍历，相同则删除 
  返 回 值：	无
 ***************************************************************************/
void solution::deletRepetitiveList()
{
	LinkList p, q;
	p = studentList;
	while (p != NULL){
		q = p;
		while (q->next != NULL){
			if (p->data.examNum == q->next->data.examNum)//删除q这个节点
				q->next = q->next->next;//删除q->next这个节点 
			else
				q = q->next;
		}
		p = p->next;
	}		
}

/***************************************************************************
  函数名称：	listInsert函数
  输入参数：	无
  功   能：	在第i个元素前插入考生信息
  返 回 值：	无
 ***************************************************************************/
Status solution::listInsert()
{
	LNode* p = studentList;
	LNode* s;
	int j = 0;
	std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！\n";
	while (p && j < locationNum - 1) { p = p->next; ++j; }//寻找第i-1个结点，p指向i-1结点
	if (!p || j > locationNum - 1) return ERROR;//i大于表长+1或者小于1，插入位置非法
	s = new LNode;
	while (!inputPersonInformation(s->data)) continue;
	s->next = p->next;//将结点s插入L中
	p->next = s;
	return OK;
}

/***************************************************************************
  函数名称：	listDelete函数
  输入参数：	无
  功   能：	在第i个元素删除考生信息
  返 回 值：	无
 ***************************************************************************/
Status solution::listDelete() {
	LNode* p = studentList;
	int j = 0;
	while (p->next && j < operationLocation - 1) { p = p->next; ++j; }//寻找第i个结点，并令p指向其前驱
	if (!(p->next) || j > operationLocation - 1)return ERROR;
	LNode* q;
	q = p->next;//临时保存被删结点的地址以备释放
	p->next = q->next;//改变删除结点前驱结点的指针域
	getStudentData = q->data;//保存删除结点的数据域
	std::cout << "你删除的考生信息是：";
	showData(getStudentData, 0);
	delete q;//释放删除结点的空间
	return OK;
}

/***************************************************************************
  函数名称：	getElem函数
  输入参数：	InformationorNum -- 1 获得当前元素的值
							 -- 0 获得当前元素的序号
  功   能：	按值查找元素
  返 回 值：	ERROR -- 查找失败
			OK    -- 查找成功，返回所查找的考生的全部信息
			j     -- 查找成功，返回所要查找的排序序号
 ***************************************************************************/
int solution::getElem(bool InformationorNum) {
	LNode* p;
	p = studentList->next;
	int j = 1;
	while (p && p->data.examNum != operationNum) {
		p = p->next;
		j++;
	}
	if (!p || j > personNum) {
		std::cout << "无您所要查找的考生的信息！" << std::endl;
		return ERROR;
	}
	if (InformationorNum) {
		getStudentData = p->data;
		return OK;
	}
	else
		return j;
}

/***************************************************************************
  函数名称：	listRevise函数
  输入参数：	无
  功   能：	修改考生信息
  返 回 值：	无
 ***************************************************************************/
Status solution::listRevise() {
	LNode* p = studentList;
	int j = 0;
	while (p->next && j < operationLocation - 1) { p = p->next; ++j; }//寻找第i个结点，并令p指向其前驱
	if (!(p->next) || j > operationLocation - 1)return ERROR;
	std::cout << "请依次输入修改后的的考生的考号，姓名，性别，年龄及报考类别！\n";
	while (!inputPersonInformation(getStudentData)) continue;
	p->next->data = getStudentData;
	return OK;
}

/***************************************************************************
  函数名称：	listLength函数
  输入参数：	无
  功   能：	统计链表长度
  返 回 值：	链表长度length
 ***************************************************************************/
int solution::listLength() {
	LNode* p = studentList->next;
	int length = 0;
	while (p) {
		length++;
		p = p->next;
	}
	return length;
}

/***************************************************************************
  函数名称：	statsSexDistribution函数
  输入参数：	无
  功   能：	统计男女人数分布
  返 回 值：	无
 ***************************************************************************/
void solution::statsSexDistribution()
{
	LNode* p = studentList->next;
	while (p) {
		if (p->data.sex[0] == -59 && p->data.sex[1] == -82)//女
			femaleNum++;
		else if (p->data.sex[0] == -60 && p->data.sex[1] == -48)//男
			maleNum++;
		p = p->next;
	}
	std::cout << std::endl;
	std::cout << "考生总人数：" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| 性别种类";
	std::cout << std::setw(20) <<std::left << "| 性别人数";
	std::cout << std::setw(20) <<std::left << "| 性别比例          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << "| " << std::setw(18) <<std::left << "男";
	std::cout << "| " << std::setw(18) <<std::left << maleNum;
	std::cout << "| " << std::setw(17) <<std::left << maleNum * 100.0 / personNum << '%';
	std::cout << "|\n";
	std::cout << "| " << std::setw(18) <<std::left << "女";
	std::cout << "| " << std::setw(18) <<std::left << femaleNum;
	std::cout << "| " << std::setw(17) <<std::left << femaleNum * 100.0 / personNum << '%';
	std::cout << "|\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  函数名称：	statsAge函数
  输入参数：	无
  功   能：	统计年龄分布
  返 回 值：	无
 ***************************************************************************/
void solution::statsAge()
{
	int ageCounts[maxAge - minAge + 1];
	int flag = 0;
	for (int j = 0; j < maxAge - minAge + 1; j++)
		ageCounts[j] = 0;
	LNode* p = studentList->next;
	//遍历链表并统计每个年龄对应的学生数量
	while (p) {
		ageCounts[p->data.age - 18]++;
		p = p->next;
	}
	//输出结果
	std::cout << std::endl;
	std::cout << "考生总人数：" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| 年龄大小";
	std::cout << std::setw(20) <<std::left << "| 年龄人数";
	std::cout << std::setw(20) <<std::left << "| 年龄比例          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	for (int i = 0; i <= maxAge - minAge + 1; i++) {
		if (flag == personNum)
			break;
		if (ageCounts[i] > 0) {
			std::cout << "| " << std::setw(18) <<std::left << i + 18;
			std::cout << "| " << std::setw(18) <<std::left << ageCounts[i];
			std::cout << "| " << std::setw(17) <<std::left << ageCounts[i] * 100.0 / personNum << '%';
			std::cout << "|\n";
			flag+= ageCounts[i];
		}
	}
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  函数名称：	countApplicationCategory函数
  输入参数：	无
  功   能：	统计报考信息分布
  返 回 值：	无
 ***************************************************************************/
void solution::countApplicationCategory()
{
	LNode* p = studentList->next;
	while (p) {
		char* category = p->data.applicationCategory;

		// 寻找是否已存在该报考类型的统计
		ACC* current = categoryCounts;
		while (current != nullptr) {
			if (strcmp(category, current->category) == 0) {
				current->count++;
				break;
			}
			current = current->next;
		}

		// 该报考类型未统计过，添加新的统计项
		if (current == nullptr) {
			ACC* newCount = new ACC;
			strcpy(newCount->category, category);
			newCount->count = 1;
			newCount->next = categoryCounts;
			categoryCounts = newCount;
		}
		p = p->next;
	}

	// 输出统计结果
	std::cout << "报考类型统计:\n";
	ACC* current = categoryCounts;
	std::cout << std::endl;
	std::cout << "考生总人数：" << personNum << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| 报考种类";
	std::cout << std::setw(20) <<std::left << "| 报考人数";
	std::cout << std::setw(20) <<std::left << "| 报考比例          |\n";
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
	while (current != nullptr) {
		std::cout << "| " << std::setw(18) <<std::left << current->category;
		std::cout << "| " << std::setw(18) <<std::left << current->count;
		std::cout << "| " << std::setw(17) <<std::left << current->count * 100.0 / personNum << '%';
		std::cout << "|\n"; 
		ACC* temp = current;
		current = current->next;
		delete temp;
	}
	std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
}

/***************************************************************************
  函数名称：	statsInformation函数
  输入参数：	无
  功   能：	实现各项统计功能
  返 回 值： 无 
 ***************************************************************************/
void solution::statsInformation()
{
	int opt_5;
	int personNum = 0;
	std::cout << "\n请选择你要统计的信息：（1.考生总数 2.性别分布 3.年龄分布 4.报考类别）" << std::endl;
	while (1) {
		std::cin >> opt_5;
		if (std::cin.fail() || personNum < 0 || personNum > 4) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
	switch (opt_5) {
	case 1:
		/* 统计考生总数 */
		personNum = listLength();
		std::cout << "考生共有" << personNum << "人。\n";
		break;
	case 2:
		/* 统计性别分布 */
		statsSexDistribution();
		break;
	case 3:
		/* 统计年龄分布 */
		statsAge();
		break;
	case 4:
		/* 统计报考类别分布 */
		countApplicationCategory();
		break;
	default:
		break;
	}
}

/***************************************************************************
  函数名称：	createList函数
  输入参数：	无
  功   能：	尾插法建立链表
  返 回 值：	无
 ***************************************************************************/
void solution::createList() {
	LNode* r = studentList;
	LNode* p;
	std::cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别\n";
	std::cout << "注：年龄应在18~35之间，性别只可为男/女，相同考生将会被合并，英文名考生请用下划线链接全名\n";
	std::cout << "例如：1234567 张三 男 20 软件工程师\n";
	std::cout << "      2345678 李四 女 19 软件工程师\n";
	std::cout << "      1 Gabrielle_Bonheur 女 19 软件开发师\n";
	for (int i = 0; i < personNum; ++i) {
		p = new LNode;
		while (!inputPersonInformation(p->data)) continue;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	deletRepetitiveList();
}

/***************************************************************************
  函数名称：	inputPersonNum函数
  输入参数：	无
  功   能：	处理学生人数
  返 回 值：	无
 ***************************************************************************/
void solution::inputPersonNum()
{
	std::cout << "请输入考生人数：";
	while (1) {
		std::cin >> personNum;
		if (std::cin.fail() || personNum < minLength || personNum > maxLength) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "输入数据有误，请重新输入\n";
			}
		}
	}
}

/***************************************************************************
  函数名称：	inputPersonInformation函数
  输入参数：	SI studentData
  功   能：	输入考生信息
  返 回 值：	true --输入成功
			false --输入失败
 ***************************************************************************/
bool solution::inputPersonInformation(SI& studentData)
{
	while (true) {
		studentData.name[maxNameLength - 1] = '\0';
		/* 创建一个字符串存储输入 */ 
		char input_line[65536] = { 0 };
		/* 获取输入 */
		myGetline(input_line, 65536);
		std::istringstream iss(input_line);
		iss >> studentData.examNum >> studentData.name >> studentData.sex >> studentData.age >> studentData.applicationCategory;
		/* 非法输入、年龄过大或过小、性别不是男/女*/
		if (iss.fail() || studentData.examNum <=0 ||studentData.age < minAge || studentData.age > maxAge || !((studentData.sex[0] == -59 && studentData.sex[1] == -82) ||
			(studentData.sex[0] == -60 && studentData.sex[1] == -48))||studentData.name[maxNameLength - 1]!='\0' || studentData.applicationCategory[0]=='.') {
			std::cout << "输入数据非法，请重新输入（从头输入）\n";
			iss.str("");
			iss.clear();
			iss.ignore(65536, '\n');
			return false;
		}
		if (studentData.applicationCategory) break;  // 退出循环
	}
	return true;
}

/***************************************************************************
  函数名称：	inputOperationLocation函数
  输入参数：	无
  功   能：	输入你要进行的选项
  返 回 值：	无
 ***************************************************************************/
void solution::inputOperationLocation()
{
	while (1) {
		std::cin >> locationNum;
		if (std::cin.fail() || locationNum <= 0 || locationNum > personNum + 1) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
}

/***************************************************************************
  函数名称：	inputOperationNum函数
  输入参数：	无
  功   能：	输入你要进行操作的考号
  返 回 值：	无
 ***************************************************************************/
void  solution::inputOperationNum()
{
	while (1) {
		std::cin >> operationNum;
		operationLocation = getElem(0);
		if (std::cin.fail() || !operationLocation) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
}

/***************************************************************************
  函数名称：	option函数
  输入参数：	无
  功   能：	选择你要进行的操作
  返 回 值：	true --输入成功
			false --输入失败
 ***************************************************************************/
bool solution::option()
{
	std::cout << std::endl << std::endl << "请选择您要进行的操作：";
	while (1) {
		std::cin >> opt;
		if (std::cin.fail() || opt < 0 || opt > 5) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
		}
	}
	switch (opt) {
	case 0:
		return 0;
		break;
	case 1:
		std::cout << "请输入你要插入的考生的位置：";
		inputOperationLocation();
		listInsert();
		deletRepetitiveList();
		output(1);
		break;
	case 2:
		std::cout << "请输入你要删除的考生的考号：";
		inputOperationNum();
		listDelete();
		output(1);
		break;
	case 3:
		std::cout << "请输入你要查找的考生的考号：";
		inputOperationNum();
		if (getElem(1))
			output(0);
		break;
	case 4:
		std::cout << "请输入你要修改的考生的考号：";
		inputOperationNum();
		listRevise();
		deletRepetitiveList();
		output(1);
		break;
	case 5:
		std::cout << "统计的考生信息如下：\n";
		deletRepetitiveList();
		output(1);
		std::cout << "是否需要进一步统计具体信息？(Y/N)";
		while (1) {
			char ch1 = _getch();
			std::cout << ch1;
			if (ch1 == 'Y' || ch1 == 'y') {
				statsInformation();
				std::cout << "是否需要进一步统计具体信息？(Y/N)";
			}
			else if (ch1 == 'N' || ch1 == 'n') {
				std::cout << std::endl;
				break;
			}
			else {
				std::cout << "\n输入数据有误，请重新输入\n";
				continue;
			}
		}
		break;
	default:
		break;
	}
	personNum = listLength();
	return 1;
}

/***************************************************************************
  函数名称：	output函数
  输入参数：	opt -- 0 输出所要查找的考生信息
				-- 1 输出所有考生信息
  功   能：	输出考生信息
  返 回 值：	无
 ***************************************************************************/
void solution::output(bool opt)
{
	std::cout << std::endl;
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
	std::cout << std::setw(20) <<std::left << "| 考号";
	std::cout << std::setw(20) <<std::left << "| 姓名";
	std::cout << std::setw(20) <<std::left << "| 性别";
	std::cout << std::setw(20) <<std::left << "| 年龄";
	std::cout << std::setw(20) <<std::left << "| 报考类别          |\n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
	if (opt) {
		LNode* p;
		p = studentList->next;
		while (p) {
			showData(p->data,1);
			p = p->next;
		}
	}
	else
		showData(getStudentData,1);
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+" << std::endl;
}

int main() {
	solution ERS;
	bool flag = 1;
	std::cout << "·······················" << std::endl;
	std::cout << "·               考生报名系统               ·" << std::endl;
	std::cout << "·      Examination Registration System     ·" << std::endl;
	std::cout << "·······················" << std::endl;
	/* 初始化链表 */
	ERS.InitList();
	/* 输入考生总人数 */
	ERS.inputPersonNum();
	/* 尾插法创建链表 */
	ERS.createList();
	/* 输出学生信息 */
	ERS.output(1);
	while (flag) {
		if (ERS.listEmpty()) {
			std::cout << "学生名单已空，请问是否要继续进行操作？(Y/N)";
			while (true) {
				char ch1 = _getch();
				std::cout << ch1;
				if (ch1 == 'Y' || ch1 == 'y')
					break;
				else if (ch1 == 'N' || ch1 == 'n') {
					std::cout << std::endl;
					flag = 0;
					break;
				}
				else {
					std::cout << "\n输入数据有误，请重新输入\n";
					continue;
				}
			}
		}
		if (flag) {
			/* 选择操作 */
			std::cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)";
			flag = ERS.option();
		}
	}
	return 0;
}

/* 测试数据-软工1班名单
2251310 杜天乐 女 19 软件设计师
2251730 刘淑仪 女 19 软件开发师
2252444 赵思源 女 19 软件测试师
2252551 徐俊逸 女 19 软件运营师
2253893 苗君文 女 19 软件设计师
2250693 朱昱瑾 女 20 软件开发师
2254282 张唯来 女 20 软件测试师
2251742 孙静怡 女 20 软件运营师
2251338 何升阳 男 20 软件设计师
2252956 岳叶晋川 男 20 软件开发师
2253896 张文健 男 21 软件测试师
2251321 徐嘉豪 男 21 软件运营师
2251948 许经宝 男 21 软件设计师
2250944 谌乐俊杰 男 21 软件开发师
2251556 张昊宸 男 21 软件测试师
2252088 孙少杰 男 22 软件运营师
2251324 王骏禹 男 22 软件设计师
2252073 刘一彤 男 22 软件开发师
2253106 霍钇澄 男 22 软件测试师
2253640 黄俊哲 男 22 软件运营师
2250288 岳文卓 男 23 软件设计师
2253226 任厚霖 男 23 软件开发师
2252841 邱嘉政 男 23 软件测试师
2252700 李一鑫 男 23 软件运营师
2250758 林继申 男 23 软件设计师
2253333 王沫涵 男 24 软件开发师
2250931 李明哲 男 24 软件测试师
2252712 杨兆镇 男 24 软件运营师
2251648 张凯 男 24 软件设计师
2254198 段子涛 男 24 软件开发师
2253537 余欣然 男 25 软件测试师
2253637 白广烨 男 25 软件运营师
2254267 周志远 男 25 软件设计师
2253715 陈甫彬 男 25 软件开发师
2254285 王智 男 25 软件测试师
2151422 武芷朵 女 26 软件运营师
2152140 王钦洋 女 26 软件设计师
2153085 马立欣 女 26 软件开发师
2256223 冯浩军 男 26 软件测试师
*/