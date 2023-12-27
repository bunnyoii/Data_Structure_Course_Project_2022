#pragma once
#include <iostream>
using namespace std;

#define defaultSize 65536
/* 操作算法中用到的预定义常量和类型 */
// 函数结果状态代码
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1	

// startus 是函数的类型，其值是函数结果状态代码
typedef int Status;

/*	串：
*	零个或多个任意字符组成的有限序列
*	子串：一格串中任意个连续字符组成的子序列（含空串）称为该串的子串
*	真子串是不包含自身的所有子串
*/

class AString {
private:
    char* ch;       //串存放数组
    int curLength;  //串的实际长度
    int maxSize;    //存放数组的最大长度
public:
    AString(int sz = defaultSize);              //构造函数，构造一个最大长度为sz，实际长度为0的字符串
    AString(const char* init);                  //构造函数，构造一个最大长度为maxSize，由init初始化的新字符串对象
    AString(const AString& ob);                 //复制构造函数，由一个已有的字符串对象ob构造一个新的字符串
    ~AString() { delete[]ch; }                  //析构函数，释放动态分配的串空间并撤销该字符串对象
    int Length()const { return curLength; }     //返回串的实际长度
    void setString(const char* inputLine);      //将字符串里的数据传入类里
    void copyTo(char* target, int targetSize) const;
                                                //将串的内容复制到字符数组里
    void clear() {
        ch[0] = '\0';  // 设置第一个字符为终止字符，这将创建一个空字符串
        curLength = 0; // 更新当前长度为0
    }
    AString& operator()(int pos, int len);      //当0<=pos<maxSize且0<=len且pos+len<maxSize的时候，
                                                //在串从pos所指出的位置开始连续取len个字符组成子串返回
    int operator == (AString& ob)const { return strcmp(ch, ob.ch) == 0; }
                                                //判断串是否相等。1等，0不等
    int operator != (AString& ob)const { return strcmp(ch, ob.ch) != 0; }
                                                //判断串是否不等。1不等，0等
    int operator !()const { return curLength == 0; }
                                                //判断串是否空。1空，0不空
    AString& operator=(AString& ob);            //串ob赋值给当前串
    AString& operator +=(const AString& ob);          //若合法，将串ob接在当前串后面  
    char& operator[](int i);                    //取当前串第i个字符
    const char* getString() const {return ch;}  //得到字符串内容
    // 将一个字符追加到字符串末尾
    void append(char c) {
        // 检查是否有足够的空间添加新字符
        if (curLength + 1 < maxSize) {
            ch[curLength] = c;      // 将字符追加到末尾
            curLength++;            // 增加当前长度
            ch[curLength] = '\0';   // 确保字符串以null字符结尾
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
    // 确保输入不为空
    if (inputLine != nullptr) {
        // 计算输入字符串的长度
        int inputLength = std::strlen(inputLine);

        // 确保长度不超过maxSize
        if (inputLength >= maxSize) {
            inputLength = maxSize - 1; // 为了安全，保留一个字符的空间用于'\0'
        }

        // 复制字符串到ch
        std::strncpy(ch, inputLine, inputLength);

        // 设置终止字符
        ch[inputLength] = '\0';

        // 更新当前长度
        curLength = inputLength;
    }
}

void AString::copyTo(char* target, int targetSize) const
{
    if (target != nullptr && targetSize > curLength) {
        std::strncpy(target, ch, curLength);
        target[curLength] = '\0'; // 确保字符串正确终止
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
    // 确保加上ob后不会超出maxSize
    int newLength = curLength + ob.curLength;
    if (newLength >= maxSize) {
        // 处理超长情况，例如扩展数组、截断等
        // ...
    }
    else {
        // 连接字符串
        std::strcat(ch, ob.ch);
        curLength = newLength;
    }
    return *this; // 返回当前对象的引用
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
    os << str.ch; // 假设 ch 是存储字符串的字符数组
    return os;
}