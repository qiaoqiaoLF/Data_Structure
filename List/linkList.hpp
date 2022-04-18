#ifndef CLASS_LINKLIST
#define CLASS_LINKLIST
#include "List.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class linkList : public List<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *p = NULL)
        {
            data = x;
            next = p;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *head;

public:
    linkList();
    ~linkList()
    {
        clear();
        delete head;
        head = nullptr;
    }
    int length() const;
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear();
    void traverse() const;
    void reverse();
};

template <class elemType>
linkList<elemType>::linkList()
{
    head = new node();
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
    if (i < 0)
        return;
    node *p, *temp;
    p = head;
    int j = 0;
    while (j < i)
    {
        if (p == NULL)
            return;
        p = p->next;
        ++j;
    }
    temp = new node(x, p->next);
    p->next = temp;
}

template <class elemType>
void linkList<elemType>::remove(int i)
{
    if (i < 0)
        return;
    node *p, *temp;
    p = head;
    int j = 0;
    while (j < i)
    {
        if (p->next == NULL)
            return;
        p = p->next;
        ++j;
    }
    temp = p->next;
    p->next = temp->next;
    delete temp;
}

template <class elemType>
int linkList<elemType>::length() const
{
    node *p = head;
    int j = 0;
    while (p->next != NULL)
    {
        p = p->next;
        ++j;
    }
    return j;
}

template <class elemType>
int linkList<elemType>::search(const elemType &x) const
{
    node *p = head;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->data == x)
            return 1;
    }
    return 0;
}

template <class elemType>
elemType linkList<elemType>::visit(int i) const
{
    if (i < 0)
        throw 1;
    node *p = head;
    int j = 0;
    while (j < i)
    {
        if (p->next == NULL)
            throw 1;
        p = p->next;
        ++j;
    }
    return p->next->data;
}

template <class elemType>
void linkList<elemType>::clear()
{
    node *p, *q;
    p = head->next;
    head->next = NULL;
    while (p)
    {
        q = p->next;
        delete p;
        p = q;
    }
}

template <class elemType>
void linkList<elemType>::traverse() const
{
    node *p;
    p = head->next;
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

template <class elemType>
void linkList<elemType>::reverse()
{
    node *p;
    node *q;
    p = head->next;
    head->next = NULL;
    while (p)
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

#endif