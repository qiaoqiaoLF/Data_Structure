#ifndef OPENHT
#define OPENHT
#include "DynamicSearchTable.hpp"

template <typename elemType, typename Key>
class OpenHashTable : public dynamicSearchTable<elemType, Key>
{
private:
    int size;
    struct Node
    {
        elemType data;
        Key key;
        Node *next;
        Node(const elemType &x, const Key &k, Node *n = nullptr)
            : data(x), key(k), next(n) {}
    };
    Node **table;
    static int defaultKey(const int &x) { return x; }
    int (*func)(const Key &k);

public:
    void insert(const elemType &x, const Key &k);
    void remove(const Key &k);
    elemType *find(const Key &k) const;
    void makeEmpty();
    ~OpenHashTable();
    OpenHashTable(int length = 100, int (*f)(const Key &k) = defaultKey);
};

template <typename elemType, typename Key>
OpenHashTable<elemType, Key>::OpenHashTable(int length, int (*f)(const Key &k))
{
    size = length;
    func = f;
    table = new Node *[size]();
}
template <typename elemType, typename Key>
OpenHashTable<elemType, Key>::~OpenHashTable()
{
    Node *temp1 = nullptr;
    Node *temp2 = nullptr;
    for (int j = 0; j < size; j++)
    {
        Node* i;
        i = table[j];
        temp1 = i;
        while (temp1 != nullptr)
        {
            temp2 = temp1;
            temp1 = temp1->next;
            delete temp2;
            temp2 = nullptr;
        }
        i = nullptr;
    }
    delete[] table;
}

template <typename elemType, typename Key>
void OpenHashTable<elemType, Key>::insert(const elemType &x, const Key &k)
{
    int pos = func(k) % size;
    table[pos] = new Node(x, k, table[pos]);
}

template <typename elemType, typename Key>
void OpenHashTable<elemType, Key>::remove(const Key &k)
{
    int pos = func(k) % size;
    Node *temp1 = nullptr;
    Node *temp2 = nullptr;
    if (table[pos] == nullptr)
        return;
    if (table[pos]->key == k)
    {
        temp2 = table[pos]->next;
        delete table[pos];
        table[pos] = temp2;
        return;
    }
    temp1 = table[pos];
    while (temp1->next != nullptr && !(temp1->next->key == k))
        temp1 = temp1->next;
    if (temp1->next == nullptr)
        return;
    temp2 = temp1->next->next;
    delete temp1->next;
    temp1->next = temp2;
}

template <typename elemType, typename Key>
elemType *OpenHashTable<elemType, Key>::find(const Key &k) const
{
    int pos = func(k) % size;
    Node *temp = table[pos];
    while (temp != nullptr && temp->key != k)
        temp = temp->next;
    if (temp == nullptr)
        return nullptr;
    return &(temp->data);
}

template <typename elemType, typename Key>
void OpenHashTable<elemType, Key>::makeEmpty()
{
    Node *temp1 = nullptr;
    Node *temp2 = nullptr;
    for (auto i : table)
    {
        temp1 = i;
        while (temp1 != nullptr)
        {
            temp2 = temp1;
            temp1 = temp1->next;
            delete temp2;
            temp2 = nullptr;
        }
        i = nullptr;
    }
}

#endif