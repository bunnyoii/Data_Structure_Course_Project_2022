#pragma once

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

template <class T>
struct CircLinkNode {
	T data;
	CircLinkNode<T>* link;
	CircLinkNode(CircLinkNode<T>* ptr = NULL) :link(ptr) {}
	CircLinkNode(T d, CircLinkNode<T>* ptr = NULL) :data(d), link(ptr) {}
};

template <class T>
class CircList{
private:
	CircLinkNode<T>* first, * last;
public:
    CircList() : first(nullptr), last(nullptr) {};
	CircList(const T& x);			// 构造函数
	CircList(CircList<T>& L);		// 复制构造函数
	~CircList();					// 析构函数
	int Length()const;				// 计算循环链表长度
    bool IsEmpty() { return (first == NULL && first == last) ? true : false; }
									// 判断空否
	CircLinkNode<T>* getHead()const {return first;};
									// 返回附加头结点地址
	void setHead(CircLinkNode<T>* p) { first = p; };
									//设置附加头结点地址
	CircLinkNode<T>* search(T x);	// 搜索含数据x的元素
	CircLinkNode<T>* Locate(int i);	// 搜索第i个元素的地址
	T* getData(int i);				// 取出第i个元素的值
	void setData(int i, T& x);		// 用x修改第i个元素的值
	bool Insert(int i, T& x);		// 在第i个元素后插入x
	bool Remove(int i, T& x);		// 删除第i个元素，x返回该元素的值
    T FindMinValue(CircList<T>& L); // 寻找链表中的最小值
};

// 构造函数
template<class T>
CircList<T>::CircList(const T& x)
{
	first = new CircLinkNode<T>(x);
	last = first;
	first->link = first;
}

// 复制构造函数
template<class T>
CircList<T>::CircList(CircList<T>& L) {
	;
}

// 析构函数
template<class T>
CircList<T>::~CircList(){
	CircLinkNode<T>* current = first->link;
	while (current != first) {
		CircLinkNode<T>* temp = current;
		current = current->link;
		delete temp;
	}
	delete first;
}

// 计算循环链表长度
template<class T>
int CircList<T>::Length() const
{
	int length = 1;
	CircLinkNode<T>* current = first->link;
	while (current != first) {
		length++;
		current = current->link;
	}
	return length;
}

// 搜索含有数据x的元素
template<class T>
CircLinkNode<T>* CircList<T>::search(T x) {
	CircLinkNode<T>* current = first->link;
	while (current != first) {
		if (current->data == x) {
			return current;
		}
		current = current->link;
	}
	return nullptr; // 返回nullptr表示未找到匹配的元素
}

// 搜索第i个元素的地址
template <class T>
CircLinkNode<T>* CircList<T>::Locate(int i) {
    if (i < 1 || i > Length()) {
        return nullptr; // i 超出范围，返回nullptr
    }
    CircLinkNode<T>* current = first->link;
    int index = 1;
    while (index < i) {
        current = current->link;
        index++;
    }
    return current;
}

// 取出第i个元素的值
template <class T>
T* CircList<T>::getData(int i) {
    CircLinkNode<T>* node = Locate(i);
    if (node) {
        return &(node->data);
    }
    return nullptr; // i 超出范围，返回nullptr
}

// 用x修改第i个元素的值
template <class T>
void CircList<T>::setData(int i, T& x) {
    CircLinkNode<T>* node = Locate(i);
    if (node) {
        node->data = x;
    }
}

// 在第i个元素后插入x
template <class T>
bool CircList<T>::Insert(int i, T& x) {
    if (i < 1 || i > Length() + 1) {
        return false; // i 超出范围，插入失败
    }
    CircLinkNode<T>* new_node = new CircLinkNode<T>(x);
    CircLinkNode<T>* prev = first;
    int index = 1;
    while (index < i) {
        prev = prev->link;
        index++;
    }
    new_node->link = prev->link;
    prev->link = new_node;
    if (prev == last) {
        last = new_node;
    }
    return true;
}

// 删除第i个元素，x返回该元素的值
template <class T>
bool CircList<T>::Remove(int i, T& x) {
    if (i < 1 || i > Length()) {
        return false; // i 超出范围，删除失败
    }
    if (i == 1) {
        // 删除头节点时，需要更新头节点和尾节点
        CircLinkNode<T>* to_delete = first->link;
        x = to_delete->data;
        if (to_delete == last) {
            last = first; // 如果删除的是最后一个节点，更新 last 指针
        }
        first->link = to_delete->link;
        delete to_delete;
    }
    else {
        CircLinkNode<T>* prev = Locate(i - 1);
        if (prev) {
            CircLinkNode<T>* to_delete = prev->link;
            x = to_delete->data;
            if (to_delete == last) {
                last = prev; // 如果删除的是最后一个节点，更新 last 指针
            }
            prev->link = to_delete->link;
            delete to_delete;
        }
    }
    return true;
}

// 寻找链表中的最小值
template <class T>
T CircList<T>::FindMinValue(CircList<T>& L) {
    if (L.IsEmpty()) {
        // 如果链表为空，返回一个默认值或抛出异常
        // 这里假设默认值为0，你可以根据实际情况修改
        return T();
    }

    CircLinkNode<T>* current = L.getHead()->link;
    T minValue = current->data;

    while (current != L.getHead()) {
        if (current->data < minValue) {
            minValue = current->data;
        }
        current = current->link;
    }

    return minValue;
}