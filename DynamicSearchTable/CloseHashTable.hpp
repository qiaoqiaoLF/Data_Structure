#ifndef CLOSEHT
#define CLOSEHT
#include "DynamicSearchTable.hpp"
const int EMPTY = 0;
const int ACTIVE = 1;
const int DELETED = 2;

template <typename elemType, typename Key>
class CloseHashTable : public dynamicSearchTable<elemType,Key>
{
private:
    int size;
    struct Node
    {
        elemType data;
        Key key;
        int state;
        Node(const elemType &x, const elemType &k, int s = 1)
            : data(x), key(k), state(s) {}
        Node(int s = 0)
            : state(s) {}
    };
    Node *table;
    static int defaultKey(const int &x) { return x; }
    int (*func)(const Key &k);

public:
    void insert(const elemType &x, const Key &k);
    void remove(const Key &k);
    elemType *find(const Key &k) const;
    void makeEmpty();
    ~CloseHashTable(){delete[] table;};
    CloseHashTable(int length = 100, int (*f)(const Key &k) = defaultKey);
};

template <typename elemType, typename Key>
CloseHashTable<elemType, Key>::CloseHashTable(int length, int (*f)(const Key &k))
{
    size = length;
    func = f;
    table = new Node[size]();
}

template <typename elemType, typename Key>
void CloseHashTable<elemType, Key>::insert(const elemType &x, const Key &k)
{
    int initPos = func(k) % size;
    int pos = initPos;
    do
    {
        if (table[pos].state != 1)
        {
            table[pos].state = 1;
            table[pos].key = k;
            table[pos].data = x;
            return;
        }
        else
            pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <typename elemType, typename Key>
void CloseHashTable<elemType, Key>::remove(const Key &k)
{
    int initPos = func(k) % size;
    int pos = initPos;
    do
    {
        if (table[pos].state == 0)
            return;
        if (table[pos].state == 1 && table[pos].key == k)
        {
            table[pos].state = 2;
            return;
        }
        else
            pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <typename elemType, typename Key>
elemType *CloseHashTable<elemType, Key>::find(const Key &k) const
{
    int initPos = func(k) % size;
    int pos = initPos;
    do
    {
        if (table[pos].state == 0)
            return nullptr;
        if (table[pos].state == 1 && table[pos].key == k)
            return &(table[pos].data);
        else
            pos = (pos + 1) % size;
    } while (pos != initPos);
    return nullptr;
}
template <typename elemType, typename Key>
void CloseHashTable<elemType, Key>::makeEmpty()
{
    for (auto i : table)
        i.state = 0;
}

#endif