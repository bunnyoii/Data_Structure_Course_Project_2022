#pragma once
#include <iostream>
using namespace std;

#define defaultSize 65536
/* �����㷨���õ���Ԥ���峣�������� */
// �������״̬����
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

// startus �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

/*	����
*	������������ַ���ɵ���������
*	�Ӵ���һ��������������ַ���ɵ������У����մ�����Ϊ�ô����Ӵ�
*	���Ӵ��ǲ���������������Ӵ�
*/

class AString {
private:
    char* ch;       //���������
    int curLength;  //����ʵ�ʳ���
    int maxSize;    //����������󳤶�
public:
    AString(int sz = defaultSize);              //���캯��������һ����󳤶�Ϊsz��ʵ�ʳ���Ϊ0���ַ���
    AString(const char* init);                  //���캯��������һ����󳤶�ΪmaxSize����init��ʼ�������ַ�������
    AString(const AString& ob);                 //���ƹ��캯������һ�����е��ַ�������ob����һ���µ��ַ���
    ~AString() { delete[]ch; }                  //�����������ͷŶ�̬����Ĵ��ռ䲢�������ַ�������
    int Length()const { return curLength; }     //���ش���ʵ�ʳ���
    void setString(const char* inputLine);      //���ַ���������ݴ�������
    void copyTo(char* target, int targetSize) const;
                                                //���������ݸ��Ƶ��ַ�������
    void clear() {
        ch[0] = '\0';  // ���õ�һ���ַ�Ϊ��ֹ�ַ����⽫����һ�����ַ���
        curLength = 0; // ���µ�ǰ����Ϊ0
    }
    AString& operator()(int pos, int len);      //��0<=pos<maxSize��0<=len��pos+len<maxSize��ʱ��
                                                //�ڴ���pos��ָ����λ�ÿ�ʼ����ȡlen���ַ�����Ӵ�����
    int operator == (AString& ob)const { return strcmp(ch, ob.ch) == 0; }
                                                //�жϴ��Ƿ���ȡ�1�ȣ�0����
    int operator != (AString& ob)const { return strcmp(ch, ob.ch) != 0; }
                                                //�жϴ��Ƿ񲻵ȡ�1���ȣ�0��
    int operator !()const { return curLength == 0; }
                                                //�жϴ��Ƿ�ա�1�գ�0����
    AString& operator=(AString& ob);            //��ob��ֵ����ǰ��
    AString& operator +=(const AString& ob);          //���Ϸ�������ob���ڵ�ǰ������  
    char& operator[](int i);                    //ȡ��ǰ����i���ַ�
    const char* getString() const {return ch;}  //�õ��ַ�������
    // ��һ���ַ�׷�ӵ��ַ���ĩβ
    void append(char c) {
        // ����Ƿ����㹻�Ŀռ�������ַ�
        if (curLength + 1 < maxSize) {
            ch[curLength] = c;      // ���ַ�׷�ӵ�ĩβ
            curLength++;            // ���ӵ�ǰ����
            ch[curLength] = '\0';   // ȷ���ַ�����null�ַ���β
        }
    }

    friend int countBF(AString S, AString T);
    friend void Nextval(const AString pattern, int next[]);
    friend int countKMP(const AString text, const AString pattern);
    friend std::ostream& operator<<(std::ostream& os, const AString& str);
};

AString::AString(int sz) {
    maxSize = (sz > 0) ? sz : defaultSize;
    ch = new char[maxSize];
    curLength = 0;
    ch[0] = '\0';
}

AString::AString(const char* init) {
    maxSize = strlen(init) + 1;
    ch = new char[maxSize];
    strcpy(ch, init);
    curLength = strlen(ch);
}

AString::AString(const AString& ob) {
    maxSize = ob.maxSize;
    curLength = ob.curLength;
    ch = new char[maxSize];
    strcpy(ch, ob.ch);
}

void AString::setString(const char* inputLine)
{
    // ȷ�����벻Ϊ��
    if (inputLine != nullptr) {
        // ���������ַ����ĳ���
        int inputLength = std::strlen(inputLine);

        // ȷ�����Ȳ�����maxSize
        if (inputLength >= maxSize) {
            inputLength = maxSize - 1; // Ϊ�˰�ȫ������һ���ַ��Ŀռ�����'\0'
        }

        // �����ַ�����ch
        std::strncpy(ch, inputLine, inputLength);

        // ������ֹ�ַ�
        ch[inputLength] = '\0';

        // ���µ�ǰ����
        curLength = inputLength;
    }
}

void AString::copyTo(char* target, int targetSize) const
{
    if (target != nullptr && targetSize > curLength) {
        std::strncpy(target, ch, curLength);
        target[curLength] = '\0'; // ȷ���ַ�����ȷ��ֹ
    }
}

AString& AString::operator()(int pos, int len) {
    static AString subStr;
    if (pos >= 0 && pos < maxSize && len >= 0 && pos + len <= curLength) {
        if (subStr.maxSize < len + 1) {
            delete[] subStr.ch;
            subStr.ch = new char[len + 1];
            subStr.maxSize = len + 1;
        }
        strncpy(subStr.ch, ch + pos, len);
        subStr.ch[len] = '\0';
        subStr.curLength = len;
    }
    return subStr;
}

AString& AString::operator=(AString& ob) {
    if (this != &ob) {
        delete[] ch;
        maxSize = ob.maxSize;
        curLength = ob.curLength;
        ch = new char[maxSize];
        strcpy(ch, ob.ch);
    }
    return *this;
}

AString& AString::operator+=(const AString& ob) {
    // ȷ������ob�󲻻ᳬ��maxSize
    int newLength = curLength + ob.curLength;
    if (newLength >= maxSize) {
        // �����������������չ���顢�ضϵ�
        // ...
    }
    else {
        // �����ַ���
        std::strcat(ch, ob.ch);
        curLength = newLength;
    }
    return *this; // ���ص�ǰ���������
}

char& AString::operator[](int i) {
    if (i >= 0 && i < curLength) {
        return ch[i];
    }
    else {
        static char nullchar = '\0';
        return nullchar;
    }
}

std::ostream& operator<<(std::ostream& os, const AString& str) {
    os << str.ch; // ���� ch �Ǵ洢�ַ������ַ�����
    return os;
}