#ifndef CLASS_CLINKLIST
#define CLASS_CLINKLIST
#include "List.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class Clinklist : public List<elemType>
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
    Clinklist();
    ~Clinklist()
    {
        clear();
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
Clinklist<elemType>::Clinklist()
{
    head = NULL;
}

template <class elemType>
void Clinklist<elemType>::insert(int i, const elemType &x)
{
    if (i < 0)
        return;
    node *p = head;
    if (i == 0 && head == NULL)
    {
        head = new node(x, head);
        head->next = head;
        return;
    }
    if (i == 0 && head != NULL)
    {
        int n = length();
        for(int i = 0;i < n -1; ++ i)
        {
            p = p->next;
        }
        head = new node(x, head);
        p->next = head;
        return;
    }
    for (int j = 1; j < i; ++j)
    {
        p = p->next;
        if (j > 1 && p == head)
            return;
    }
    p->next  = new node(x, p->next);
}

template <class elemType>
void Clinklist<elemType>::remove(int i)
{
    if (i < 0)
        return;
    node *p, *temp;
    p = head;
    if (i == 0)
    {
        temp = head;
        while (p->next != head)
            p = p->next;
        p->next = head->next;
        head = head->next;
        delete temp;
        return;
    }

    for (int j = 1; j < i; ++j)
    {
        p = p->next;
        if (p->next == head)
            return;
    }
    temp = p->next;
    p->next = temp->next;
    delete temp;
}

template <class elemType>
int Clinklist<elemType>::length() const
{
    if (head == NULL)
        return 0;
    node *p = head;
    int j = 1;
    while (p->next != head)
    {
        p = p->next;
        ++j;
    }
    return j;
}

template <class elemType>
int Clinklist<elemType>::search(const elemType &x) const
{
    node *p = head;
    if (head == NULL)
        return 0;
    do
    {
        if (p->data == x)
            return 1;
        p = p->next;
    } while (p != head);
    return 0;
}

template <class elemType>
elemType Clinklist<elemType>::visit(int i) const
{
    if (i < 0)
        throw 1;
    if (head == NULL)
        return 0;
    node *p = head;
    for (int j = 0; j < i; j++)
    {
        if (j > 0 && p == head)
            throw 1;
        p = p->next;
    }
    return p->data;
}

template <class elemType>
void Clinklist<elemType>::clear()
{
    if (head == NULL)
        return;
    node *p, *q;
    p = head;
    do
    {
        q = p->next;
        delete p;
        p = q;
    } while (p != head);
    head = NULL;
}

template <class elemType>
void Clinklist<elemType>::traverse() const
{
    if (head == NULL)
        return;
    node *p;
    p = head;
    do
    {
        cout << p->data << " ";
        p = p->next;
    } while (p != head);
    cout << endl;
}

template <class elemType>
void Clinklist<elemType>::reverse()
{
    if (head == NULL)
        return;
    if (head->next == head)
        return;
    node *p, *q;
    p = head->next;
    head->next = head;
    while (p != head)
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}
#endif