#ifndef CLASS_LINKQUEUE
#define CLASS_LINKQUEUE
#include"Queue.hpp"
#include<iostream>
using namespace std;

template <class elemType>
class linkQueue : public queue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *n = nullptr)
        {
            data = x;
            next = n;
        }
        node()
        {
            next = nullptr;
        }
        ~node(){};
    };
    node *front, *rear;

public:
    linkQueue()
    {
        front = nullptr;
        rear = nullptr;
    };
    ~linkQueue()
    {
        while (!isEmpty())
        {
            deQueue();
        }
    };
    elemType getHead()
    {
        return front->data;
    }
    bool isEmpty()
    {
        return !front;
    }
    elemType deQueue()
    {
        if (!front)
            throw 1;
        elemType tmp;
        if (front == rear && front)
        {
            tmp = front->data;
            delete front;
            front = nullptr;
            rear = nullptr;
            return tmp;
        }
        else
        {
            node *temp;
            tmp = front->data;
            temp = front;
            front = front->next;
            delete temp;
            temp = nullptr;
            return tmp;
        }
    }
    void enQueue(const elemType &x)
    {
        if (!(front || rear))
        {
            rear = new node(x);
            front = rear;
        }
        else
        {
            rear->next = new node(x);
            rear = rear->next;
        }
    }
};

#endif