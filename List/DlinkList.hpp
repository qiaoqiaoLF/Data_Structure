#ifndef CLASS_DLINKLIST
#define CLASS_DLINKLIST
#include "List.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class DlinkList : public List<elemType>
{
private:
    struct node
    {
        elemType data;
        node *prior, *next;
        node() : prior(NULL), next(NULL) {}
        node(const elemType &x, node *p = NULL, node *n = NULL)
        {
            data = x;
            prior = p;
            next = n;
        }
        
        ~node() {}
    };
    node *head, *tail;
    int currentLength;

public:
    DlinkList();
    ~DlinkList()
    {
        clear();
        delete head;
        delete tail;
    }
    int length() const
    {
        return currentLength;
    }
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear();
    void traverse() const;
};


template <class elemType>
DlinkList<elemType>::DlinkList()
{
    head = new node();
    tail = new node();
    head->next = tail;
    tail->prior = head;
    currentLength = 0;
}

template <class elemType>
void DlinkList<elemType>::insert(int i, const elemType &x)
{
    if (i < 0 || i > currentLength)
        return;
    node *p;
    if (i > currentLength / 2)
    {
        p = tail;
        for (int j = 0; j < currentLength - i; j++)
        {
            p = p->prior;
        }
        p->prior = new node(x, p->prior, p);
        if (!p->prior)
            return;
        p->prior->prior->next = p->prior;
    }
    else
    {
        p = head;
        for (int j = 0; j < i; ++j)
        {
            p = p->next;
        }
        p->next = new node(x, p, p->next);
        if (!p->next)
            return;
        p->next->next->prior = p->next;
    }
    currentLength++;
}

template <class elemType>
void DlinkList<elemType>::remove(int i)
{
    if (i < 0 || i > currentLength - 1)
        return;
    node *p;
    node *temp;
    if (i > currentLength / 2)
    {
        p = tail;
        for (int j = 0; j < currentLength - i -1; j++)
        {
            p = p->prior;
        }

        temp = p->prior;
        temp->prior->next = p;
        p->prior = temp->prior;
        delete temp;
    }
    else
    {
        p = head;
        for (int j = 0; j < i; ++j)
        {
            p = p->next;
        }
        temp = p->next;
        temp->next->prior = p;
        p->next = temp->next;
        delete temp;
    }
    currentLength--;
}

template <class elemType>
void DlinkList<elemType>::clear()
{
    node *p;
    node *q;
    p = head->next;
    head->next = NULL;
    tail->prior = NULL;
    q = p;
    for (int i = 0; i < currentLength; ++i)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class elemType>
void DlinkList<elemType>::traverse() const
{
    node *p;
    p = head->next;
    while (p && p!= tail)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

template <class elemType>
elemType DlinkList<elemType>::visit(int i) const
{
    if (i < 0 || i > currentLength)
        throw 1;
    node *p;
    if (i > currentLength / 2)
    {
        p = tail;
        for (int j = 0; j < currentLength - i; j++)
        {
            p = p->prior;
        }
        return p->data;
    }
    else
    {
        p = head;
        for (int j = 0; j < i; ++j)
        {
            p = p->next;
        }
        return p->next->data;
    }
}

template <class elemType>
int DlinkList<elemType>::search(const elemType &x ) const
{
    node *p;
        p = head ->next;
        for (int j = 0; j < currentLength; j++)
        {
            if(p->data == x)
            return 1;
            p = p->next;
        }
        return 0;
        
    
    
}

#endif