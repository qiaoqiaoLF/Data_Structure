#ifndef AVLTREE
#define AVLTREE
#include ".\DynamicSearchTable.hpp"
// Recursive Version

template <typename elemType, typename Key>
class AvlTree : public dynamicSearchTable<elemType, Key>
{
private:
    struct AvlNode
    {
        AvlNode *left;
        AvlNode *right;
        elemType data;
        Key key;
        int height;
        AvlNode() = default;
        AvlNode(const elemType &x, const Key &k, AvlNode *l = nullptr, AvlNode *r = nullptr, int h = 1)
            : data(x), key(k), left(l), right(r), height(h) {}
    };
    void delTree(AvlNode *t);
    void insert(const elemType &x, const Key &k, AvlNode *&t);
    bool remove(const Key &k, AvlNode *&t);
    elemType *find(const Key &k, AvlNode *t) const;
    int Height(AvlNode *t) const { return t ? t->height : 0; }
    void LL(AvlNode *&t);
    void RR(AvlNode *&t);
    void LR(AvlNode *&t);
    void RL(AvlNode *&t);
    bool Ladjust(AvlNode *&t);
    bool Radjust(AvlNode *&t);
    AvlNode *root;
    void InOrder(AvlNode *t) const
    {
        if (!t)
            return;
        InOrder(t->left);
        std::cout << t->data << ' ';
        InOrder(t->right);
    }

public:
    AvlTree() { root = nullptr; }
    ~AvlTree()
    {
        delTree(root);
        root = nullptr;
    }
    void clear()
    {
        delTree(root);
        root = nullptr;
    }
    void insert(const elemType &x, const Key &k) { insert(x, k, root); }
    elemType *find(const Key &k) const { return find(k, root); }
    void remove(const Key &k) { remove(k, root); }
    void InOrder() const
    {
        InOrder(root);
    }
};

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::delTree(AvlNode *t)
{
    if (!t)
        return;
    delTree(t->left);
    delTree(t->right);
    delete t;
    t = nullptr;
}

template <typename elemType, typename Key>
elemType *AvlTree<elemType, Key>::find(const Key &k, AvlNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else if (k == t->key)
        return &(t->data);
    else if (k < t->key)
        return find(k, t->left);
    else
        return find(k, t->right);
}

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::insert(const elemType &x, const Key &k, AvlNode *&t)
{
    if (t == nullptr)
        t = new AvlNode(x, k);
    else if (k < t->key)
    {
        insert(x, k, t->left);
        if (Height(t->left) == Height(t->right) + 2)
            (k < t->left->key) ? LL(t) : LR(t);
    }
    else
    {
        insert(x, k, t->right);
        if (Height(t->left) == Height(t->right) - 2)
            (k > t->right->key) ? RR(t) : RL(t);
    }
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
}

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::LL(AvlNode *&t)
{
    auto t1 = t;
    t = t->left;
    t1->left = t->right;
    t->right = t1;
    t1->height = std::max(Height(t1->left), Height(t1->right)) + 1;
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
}

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::RR(AvlNode *&t)
{
    auto t1 = t;
    t = t->right;
    t1->right = t->left;
    t->left = t1;
    t1->height = std::max(Height(t1->left), Height(t1->right)) + 1;
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
}

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::LR(AvlNode *&t)
{
    RR(t->left);
    LL(t);
}

template <typename elemType, typename Key>
void AvlTree<elemType, Key>::RL(AvlNode *&t)
{
    LL(t->right);
    RR(t);
}

template <typename elemType, typename Key>
bool AvlTree<elemType, Key>::remove(const Key &k, AvlNode *&t)
{
    if (!t)
        return true;
    else if (k < t->key)
    {
        if (remove(k, t->left))
            return true;
        return Ladjust(t);
    }
    else if (k > t->key)
    {
        if (remove(k, t->right))
            return true;
        return Radjust(t);
    }
    else
    {
        if (t->left && t->right)
        {
            auto temp = t->right;
            while (temp->left)
                temp = temp->left;
            t->data = temp->data;
            t->key = temp->key;
            if (remove(t->key, t->right))
                return true;
            return Radjust(t);
        }
        else
        {
            auto temp = t;
            t = t->left ? t->left : t->right;
            delete temp;
            temp = nullptr;
            return false;
        }
    }
}

template <typename elemType, typename Key>
bool AvlTree<elemType, Key>::Ladjust(AvlNode *&t)
{
    if (Height(t->left) == Height(t->right) - 1)
        return true;
    if (Height(t->left) == Height(t->right))
    {
        --t->height;
        return false;
    }
    else
    {
        if (Height(t->right->right) == Height(t->right->left) + 1)
        {
            RR(t);
            return false;
        }
        if (Height(t->right->right) == Height(t->right->left) - 1)
        {

            RL(t);
            return false;
        }
        else
        {
            RR(t);
            return true;
        }
    }
}

template <typename elemType, typename Key>
bool AvlTree<elemType, Key>::Radjust(AvlNode *&t)
{
    if (Height(t->right) == Height(t->left) - 1)
        return true;
    if (Height(t->right) == Height(t->left))
    {
        --t->height;
        return false;
    }
    if (Height(t->left->left) == Height(t->left->right) + 1)
    {
        LL(t);
        return false;
    }
    if (Height(t->left->left) == Height(t->left->right) - 1)
    {
        LR(t);
        return false;
    }
    else
    {
        LL(t);
        return true;
    }
}

#endif