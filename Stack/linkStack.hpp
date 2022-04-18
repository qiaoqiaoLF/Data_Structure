#ifndef CLASS_LINKSTACK
#define CLASS_LINKSTACK
#include "Stack.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class linkStack : public stack<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *N = nullptr)
        {
            data = x;
            next = N;
        }
        node() : next(nullptr){};
        ~node(){};
    };
    node *top;

public:
    linkStack()
    {
        top = new node();
    }
    ~linkStack()
    {
        clear();
        delete top;
        top = nullptr;
    }
    bool isEmpty() const
    {
        return (!top->next);
    }
    elemType Top() const
    {
        if (isEmpty())
            throw 1;
        return top->data;
    }
    elemType pop()
    {
        if (isEmpty())
            throw 1;
        elemType temp = top->data;
        node *tmp = top;
        top = top->next;
        delete tmp;
        return temp;
    }
    void push(const elemType &x)
    {
        top = new node(x, top);
    }
    void clear()
    {
        node *tmp;
        while (top->next)
        {
            tmp = top->next;
            delete top;
            top = tmp;
        }
    }
};
#endif