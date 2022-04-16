#ifndef CLASS_SEQQUEUE
#define CLASS_SEQQUEUE
#include "Queue.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class seqQueue : public queue<elemType>
{
private:
    elemType *elem;
    int front, rear;
    int maxsize;
    void doublespace()
    {
        elemType *temp = new elemType[maxsize * 2];
        int i;
        for (i = 0; !isEmpty(); ++i)
        {
            temp[i] = deQueue();
        }
        delete[] elem;
        elem = temp;
        front = -1;
        rear = i - 1;
        maxsize *= 2;
    }

public:
    seqQueue()
    {
        elem = new elemType[10];
        maxsize = 10;
        front = -1;
        rear = -1;
    }
    ~seqQueue()
    {
        delete[] elem;
    }
    bool isEmpty()
    {
        return front == rear;
    }
    elemType getHead()
    {
        if (isEmpty())
            throw 1;
        return elem[(front + 1) % maxsize];
    }
    elemType deQueue()
    {
        if (isEmpty())
            throw 1;
        front = (front + 1) % maxsize;
        return elem[front];
    }
    void enQueue(const elemType &x)
    {
        if ((rear + 1) % maxsize == front || (front == -1 && rear == maxsize - 2))
            doublespace();
        rear = (rear + 1) % maxsize;
        elem[rear] = x;
    }
};

#endif