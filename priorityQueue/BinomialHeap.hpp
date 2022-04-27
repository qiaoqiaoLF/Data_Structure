#ifndef BINOHEAP
#define BINOHEAP
#include <vector>

template <typename elemType>
struct Node
{
    elemType data;
    Node *left;
    Node *right;
    Node(const elemType &x, Node *l = nullptr, Node *r = nullptr) : data(x), left(l), right(r){};
};

template <typename elemType>
class Tree
{
private:
    Node<elemType> *root;
    void DelTree(Node<elemType> *r);

public:
    static Tree<elemType> *AddSubTree(Tree<elemType> *t1, Tree<elemType> *t2);

    Tree(const elemType &x) { root = new Node<elemType>(x); }
    Tree(Node<elemType> *r) { root = r; }
    Tree() { root = nullptr; }
    Node<elemType> *GetRoot() { return root; }
    std::vector<Tree<elemType> *> GetChild() const;
    ~Tree()
    {
        DelTree(root);
        root = nullptr;
    }
};

template <typename elemType>
std::vector<Tree<elemType> *> Tree<elemType>::GetChild() const
{
    std::vector<Tree<elemType> *> temp;
    if (!root->left)
        return temp;
    Tree *tmp;
    auto r = root->left;
    while (r->right)
    {
        tmp = new Tree(r);
        r = r->right;
        tmp->root->right = nullptr;
        temp.push_back(tmp);
    }
    tmp = new Tree(r);
    tmp->root->right = nullptr;
    temp.push_back(tmp);
    return temp;
}

template <typename elemType>
void Tree<elemType>::DelTree(Node<elemType> *r)
{
    if (!r)
        return;
    DelTree(r->left);
    DelTree(r->right);
    delete r;
}

template <typename elemType>
Tree<elemType> *Tree<elemType>::AddSubTree(Tree<elemType> *t1, Tree<elemType> *t2)
{
    if (t1 == nullptr || t2 == nullptr)
        return t1 ? t1 : t2;
    if (t1->root->data > t2->root->data)
    {
        if (!t2->root->left)
            t2->root->left = t1->root;
        else
        {
            auto temp = t2->root->left;
            while (temp->right)
                temp = temp->right;
            temp->right = t1->root;
        }
        return t2;
    }
    else
    {
        if (!t1->root->left)
            t1->root->left = t2->root;
        else
        {
            auto temp = t1->root->left;
            while (temp->right)
                temp = temp->right;
            temp->right = t2->root;
        }
        return t1;
    }
}

template <typename elemType>
class BinomialHeap
{
private:
    std::vector<Tree<elemType> *> Trees;

public:
    ~BinomialHeap();
    void enQueue(const elemType &x);
    elemType deQueue();
    std::vector<Tree<elemType> *> mergeHeap(std::vector<Tree<elemType> *> vec1, std::vector<Tree<elemType> *> vec2);
    bool isEmpty() const { return Trees.empty(); }
};

template <typename elemType>
BinomialHeap<elemType>::~BinomialHeap()
{
    for (auto i : Trees)
    {
        i->~Tree();
    }
    Trees.clear();
}

template <typename elemType>
std::vector<Tree<elemType> *> BinomialHeap<elemType>::mergeHeap(std::vector<Tree<elemType> *> vec1, std::vector<Tree<elemType> *> vec2)
{
    std::vector<Tree<elemType> *> vec3;
    auto size1 = vec1.size();
    auto size2 = vec2.size();
    size_t maxSize = std::max(size1, size2);
    size_t minSize = std::min(size1, size2);
    for (size_t i = 0; i < maxSize + 1; ++i)
        vec3.push_back(nullptr);
    for (size_t i = 0; i < minSize; ++i)
    {
        if (vec1[i] == nullptr && vec2[i] == nullptr)
        {
            continue;
        }
        else if (vec1[i] == nullptr || vec2[i] == nullptr)
        {
            if (vec3[i] == nullptr)
                vec3[i] = vec1[i] ? vec1[i] : vec2[i];
            else
            {
                vec3[i + 1] = Tree<elemType>::AddSubTree(vec1[i] ? vec1[i] : vec2[i], vec3[i]);
                vec3[i] = nullptr;
            }
        }
        else
        {
            vec3[i + 1] = Tree<elemType>::AddSubTree(vec1[i], vec2[i]);
        }
    }
    if (size1 > size2)
    {
        for (size_t i = size2; i < size1; ++i)
        {
            if (vec3[i] && vec1[i])
            {
                vec3[i + 1] = Tree<elemType>::AddSubTree(vec1[i], vec3[i]);
                vec3[i] = nullptr;
            }
            else
                vec3[i] = Tree<elemType>::AddSubTree(vec1[i], vec3[i]);
        }
    }
    else
    {
        for (size_t i = size1; i < size2; ++i)
        {
            if (vec3[i] && vec2[i])
                vec3[i + 1] = Tree<elemType>::AddSubTree(vec2[i], vec3[i]);
            else
                vec3[i] = Tree<elemType>::AddSubTree(vec2[i], vec3[i]);
        }
    }
    while (!vec3.empty() && vec3.back() == nullptr)
        vec3.pop_back();
    return vec3;
}

template <typename elemType>
void BinomialHeap<elemType>::enQueue(const elemType &x)
{
    Tree<elemType> *temp = new Tree<elemType>(x);
    Trees = mergeHeap(Trees, std::vector<Tree<elemType> *>{temp});
}
template <typename elemType>
elemType BinomialHeap<elemType>::deQueue()
{
    size_t pos;
    pos = 0;
    elemType min;
    for (auto i : Trees)
    {
        if (i != nullptr)
        {
            min = i->GetRoot()->data;
            break;
        }
    }
    for (int i = 0; i < Trees.size(); ++i)
    {
        if (Trees[i] != nullptr)
            if (min >= Trees[i]->GetRoot()->data)
            {
                min = Trees[i]->GetRoot()->data;
                pos = i;
            }
    }
    std::vector<Tree<elemType> *> temp = Trees[pos]->GetChild();
    Trees[pos] = nullptr;
    Trees = mergeHeap(temp, Trees);
    return min;
}

#endif