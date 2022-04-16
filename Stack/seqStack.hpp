#ifndef CLASS_SEQSTACK
#define CLASS_SEQSTACK
#include "Stack.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class seqStack : public stack<elemType>
{
private:
    int top;
    elemType *elem;
    int maxsize;
    void doublespace()
    {
        elemType *temp;
        temp = new elemType[maxsize * 2];
        maxsize = maxsize * 2;
        for (int i = 0; i < maxsize; ++i)
            temp[i] = elem[i];
        delete[] elem;
        elem = temp;
    }

public:
    seqStack(int m = 10)
    {
        maxsize = m;
        top = -1;
        elem = new elemType[maxsize];
    }
    ~seqStack()
    {
        delete[] elem;
        top = -1;
    }
    elemType Top() const
    {
        return elem[top];
    }
    void push(const elemType &x)
    {
        top++;
        if (top == maxsize - 1)
            doublespace();
        elem[top] = x;
    }
    elemType pop()
    {

        elemType &temp = elem[top];
        top--;
        return temp;
    }
    bool isEmpty() const
    {
        if (top == -1)
            return true;
        return false;
    }
};

#endif