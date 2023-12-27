#pragma once

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
	CircList(const T& x);			// ���캯��
	CircList(CircList<T>& L);		// ���ƹ��캯��
	~CircList();					// ��������
	int Length()const;				// ����ѭ��������
    bool IsEmpty() { return (first == NULL && first == last) ? true : false; }
									// �жϿշ�
	CircLinkNode<T>* getHead()const {return first;};
									// ���ظ���ͷ����ַ
	void setHead(CircLinkNode<T>* p) { first = p; };
									//���ø���ͷ����ַ
	CircLinkNode<T>* search(T x);	// ����������x��Ԫ��
	CircLinkNode<T>* Locate(int i);	// ������i��Ԫ�صĵ�ַ
	T* getData(int i);				// ȡ����i��Ԫ�ص�ֵ
	void setData(int i, T& x);		// ��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, T& x);		// �ڵ�i��Ԫ�غ����x
	bool Remove(int i, T& x);		// ɾ����i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
    T FindMinValue(CircList<T>& L); // Ѱ�������е���Сֵ
};

// ���캯��
template<class T>
CircList<T>::CircList(const T& x)
{
	first = new CircLinkNode<T>(x);
	last = first;
	first->link = first;
}

// ���ƹ��캯��
template<class T>
CircList<T>::CircList(CircList<T>& L) {
	;
}

// ��������
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

// ����ѭ��������
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

// ������������x��Ԫ��
template<class T>
CircLinkNode<T>* CircList<T>::search(T x) {
	CircLinkNode<T>* current = first->link;
	while (current != first) {
		if (current->data == x) {
			return current;
		}
		current = current->link;
	}
	return nullptr; // ����nullptr��ʾδ�ҵ�ƥ���Ԫ��
}

// ������i��Ԫ�صĵ�ַ
template <class T>
CircLinkNode<T>* CircList<T>::Locate(int i) {
    if (i < 1 || i > Length()) {
        return nullptr; // i ������Χ������nullptr
    }
    CircLinkNode<T>* current = first->link;
    int index = 1;
    while (index < i) {
        current = current->link;
        index++;
    }
    return current;
}

// ȡ����i��Ԫ�ص�ֵ
template <class T>
T* CircList<T>::getData(int i) {
    CircLinkNode<T>* node = Locate(i);
    if (node) {
        return &(node->data);
    }
    return nullptr; // i ������Χ������nullptr
}

// ��x�޸ĵ�i��Ԫ�ص�ֵ
template <class T>
void CircList<T>::setData(int i, T& x) {
    CircLinkNode<T>* node = Locate(i);
    if (node) {
        node->data = x;
    }
}

// �ڵ�i��Ԫ�غ����x
template <class T>
bool CircList<T>::Insert(int i, T& x) {
    if (i < 1 || i > Length() + 1) {
        return false; // i ������Χ������ʧ��
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

// ɾ����i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
template <class T>
bool CircList<T>::Remove(int i, T& x) {
    if (i < 1 || i > Length()) {
        return false; // i ������Χ��ɾ��ʧ��
    }
    if (i == 1) {
        // ɾ��ͷ�ڵ�ʱ����Ҫ����ͷ�ڵ��β�ڵ�
        CircLinkNode<T>* to_delete = first->link;
        x = to_delete->data;
        if (to_delete == last) {
            last = first; // ���ɾ���������һ���ڵ㣬���� last ָ��
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
                last = prev; // ���ɾ���������һ���ڵ㣬���� last ָ��
            }
            prev->link = to_delete->link;
            delete to_delete;
        }
    }
    return true;
}

// Ѱ�������е���Сֵ
template <class T>
T CircList<T>::FindMinValue(CircList<T>& L) {
    if (L.IsEmpty()) {
        // �������Ϊ�գ�����һ��Ĭ��ֵ���׳��쳣
        // �������Ĭ��ֵΪ0������Ը���ʵ������޸�
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