#ifndef LHEAP
#define LHEAP

template <typename elemType>
struct Node
{
    Node *left;
    Node *right;
    elemType data;
    Node(elemType const &x, Node *l = nullptr, Node *r = nullptr)
    {
        left = l;
        right = r;
        data = x;
    }
};

template <typename elemType>
class LeftlistsHeap
{
private:
    static int Npl(Node<elemType> *r);
    static void maintain(Node<elemType> *r);
    Node<elemType> *root;
    void delTree(Node<elemType> *&r);

public:
    LeftlistsHeap() : root(nullptr) {}
    ~LeftlistsHeap();
    static Node<elemType> *mergeHeap(Node<elemType> *r1, Node<elemType> *r2);
    void enQueue(const elemType &x);
    elemType deQueue();
    bool isEmpty()
    {
        return !root;
    }
};

template <typename elemType>
LeftlistsHeap<elemType>::~LeftlistsHeap()
{
    delTree(root);
}

template <typename elemType>
void LeftlistsHeap<elemType>::delTree(Node<elemType> *&r)
{
    if (!r)
        return;
    delTree(r->left);
    delTree(r->right);
    delete r;
    r = nullptr;
}

template <typename elemType>
Node<elemType> *LeftlistsHeap<elemType>::mergeHeap(Node<elemType> *r1, Node<elemType> *r2)
{
    if (r1 == nullptr)
        return r2;
    if (r2 == nullptr)
        return r1;
    if (r1->data > r2->data)
    {
        r2->right = mergeHeap(r2->right, r1);
        maintain(r2);
        return r2;
    }
    else
    {
        r1->right = mergeHeap(r1->right, r2);
        maintain(r1);
        return r1;
    }
}

template <typename elemType>
void LeftlistsHeap<elemType>::maintain(Node<elemType> *r)
{
    if (Npl(r->left) < Npl(r->right))
    {
        std::swap(r->left, r->right);
    }
}

template <typename elemType>
void LeftlistsHeap<elemType>::enQueue(const elemType &x)
{
    Node<elemType> *r = new Node<elemType>(x);
    root = mergeHeap(root, r);
}

template <typename elemType>
elemType LeftlistsHeap<elemType>::deQueue()
{
    elemType temp = root->data;
    auto temproot = root;
    root = mergeHeap(root->left, root->right);
    delete temproot;
    return temp;
}

template <typename elemType>
int LeftlistsHeap<elemType>::Npl(Node<elemType> *r)
{
    if (!r)
        return -1;
    else
        return std::min(Npl(r->left), Npl(r->right)) + 1;
}

#endif