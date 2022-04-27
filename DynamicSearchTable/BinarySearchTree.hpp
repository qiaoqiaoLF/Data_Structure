#ifndef BIANRY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include <iostream>
#include ".\DynamicSearchTable.hpp"

template <typename elemType, typename Key>
class BinarySearchTree : public dynamicSearchTable<elemType, Key>
{
private:
    struct Node
    {
        elemType data;
        Key key;
        Node *left;
        Node *right;
        Node() : left(nullptr), right(nullptr){};
        Node(const elemType &D, const Key &K, Node *L = nullptr, Node *R = nullptr)
            : data(D), key(K), left(L), right(R){};
    };
    Node *root;

    void deleteTree(Node *t);
    elemType *find(const Key &k, Node *t) const;
    void insert(const elemType &x, const Key &k, Node *&t);
    void remove(const Key &k, Node *&t);
    void InOrder(Node *t) const
    {
        if (!t)
            return;
        InOrder(t->left);
        std::cout << t->data << ' ';
        InOrder(t->right);
    }

public:
    elemType *find(const Key &k) const;
    void insert(const elemType &x, const Key &k);
    void remove(const Key &k);
    void InOrder() const
    {
        InOrder(root);
    }
    BinarySearchTree();
    ~BinarySearchTree();
};

template <typename elemType, typename Key>
BinarySearchTree<elemType, Key>::BinarySearchTree()
{
    root = nullptr;
}

template <typename elemType, typename Key>
BinarySearchTree<elemType, Key>::~BinarySearchTree()
{
    deleteTree(root);
}

template <typename elemType, typename Key>
void BinarySearchTree<elemType, Key>::deleteTree(Node *t)
{
    if (t == nullptr)
        return;
    deleteTree(t->left);
    deleteTree(t->right);
    delete t;
    t = nullptr;
}

// recursion
// template <typename elemType, typename Key>
// elemType *BinarySearchTree<elemType, Key>::find(const Key &k) const
// {
//     return find(k, root);
// }

// iteration
template <typename elemType, typename Key>
elemType *BinarySearchTree<elemType, Key>::find(const Key &k) const
{
    Node *p = root;
    while (p && p->key != k)
    {
        if (p->key < k)
            p = p->right;
        else
            p = p->left;
    }
    if (p)
        return &(p->data);
    return nullptr;
}

// recursion
//  template <typename elemType, typename Key>
//  void BinarySearchTree<elemType, Key>::insert(const elemType &x, const Key &k)
//  {
//      insert(x, k, root);
//  }

// iteration
template <typename elemType, typename Key>
void BinarySearchTree<elemType, Key>::insert(const elemType &x, const Key &k)
{
    if (!root)
    {
        root = new Node(x, k);
        return;
    }
    Node *p = root;
    while (p)
    {
        if (p->key > k)
            if (p->left)
                p = p->left;
            else
            {
                p->left = new Node(x, k);
                return;
            }
        else if (p->key < k)
            if (p->right)
                p = p->right;
            else
            {
                p->right = new Node(x, k);
                return;
            }
        else
            return;
    }
}

// recursion
template <typename elemType, typename Key>
void BinarySearchTree<elemType, Key>::remove(const Key &k)
{
    remove(k, root);
}

// iteration
// template <typename elemType, typename Key>
// void BinarySearchTree<elemType, Key>::remove(const Key &k)
// {
//     Node *p = root;
//     Node **parent = &root;
//     Node *temp = nullptr;
//     while (p && p->key != k)
//     {
//         parent = (p->key > k)?&(p->left) : &(p->right);
//         p = *parent;
//     }
//     if (!p)
//         return;
//     else
//     {
//         if(p->left && p->right)
//         {
//             temp = p;
//             p = p->right;
//             while (p->left)
//             {
//                 temp = p;
//                 p = p->left;
//             }
//             (*parent)->data = p->data;
//             (*parent)->key = p->key;
//             temp->left = p->right;
//             delete p;
//             p = nullptr;
//         }
//         else
//         {
//             *parent = (p->left)?p->left:p->right;
//             delete p;
//             p = nullptr;
//         }
//     }
// }

template <typename elemType, typename Key>
elemType *BinarySearchTree<elemType, Key>::find(const Key &k, Node *t) const
{
    if (!t)
        return nullptr;
    if (t->key == k)
        return &(t->data);
    else
        return (k > t->key) ? find(k, t->right) : find(k, t->left);
}

template <typename elemType, typename Key>
void BinarySearchTree<elemType, Key>::insert(const elemType &x, const Key &k, Node *&t)
{
    if (!t)
    {
        t = new Node(x, k);
        return;
    }
    if (k > t->key)
        insert(x, k, t->right);
    else if (k < t->key)
        insert(x, k, t->left);
    else
        return;
}

template <typename elemType, typename Key>
void BinarySearchTree<elemType, Key>::remove(const Key &k, Node *&t)
{
    Node *temp;
    if (!t)
        return;
    if (t->key == k)
    {
        if (t->left && t->right)
        {
            temp = t->right;
            while (temp->left)
                temp = temp->left;
            t->data = temp->data;
            t->key = temp->key;
            remove(t->key, t->right);
            return;
        }
        else
        {

            temp = t;
            t = (t->left) ? t->left : t->right;
            delete temp;
            return;
        }
    }

    if (t->key > k)
        remove(k, t->left);
    else
        remove(k, t->right);
}
#endif