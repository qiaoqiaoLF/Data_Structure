#ifndef SKEWHEAP
#define SKEWHEAP

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
class SkewHeap
{
private:
    Node<elemType> *root;
    void delTree(Node<elemType> *r);

public:
    SkewHeap() : root(nullptr) {}
    ~SkewHeap()
    {
        delTree(root);
        root = nullptr;
    }
    static Node<elemType> *mergeHeap(Node<elemType> *r1, Node<elemType> *r2);
    void enQueue(const elemType &x);
    elemType deQueue();
    bool isEmpty() { return !root; }
};

template <typename elemType>
void SkewHeap<elemType>::delTree(Node<elemType> *r)
{
    if (!r)
        return;
    delTree(r->left);
    delTree(r->right);
    delete r;
}

template <typename elemType>
Node<elemType> *SkewHeap<elemType>::mergeHeap(Node<elemType> *r1, Node<elemType> *r2)
{
    if (r1 == nullptr)
        return r2;
    if (r2 == nullptr)
        return r1;
    if (r1->data < r2->data)
    {
        r1->right = mergeHeap(r1->right, r2);
        std::swap(r1->left, r1->right);
        return r1;
    }
    else
    {
        r2->right = mergeHeap(r2->right, r1);
        std::swap(r2->left, r2->right);
        return r2;
    }
}

template <typename elemType>
void SkewHeap<elemType>::enQueue(const elemType &x)
{
    Node<elemType> *r = new Node<elemType>(x);
    root = mergeHeap(root, r);
}

template <typename elemType>
elemType SkewHeap<elemType>::deQueue()
{
    elemType temp = root->data;
    auto temproot = root;
    root = mergeHeap(root->left, root->right);
    delete temproot;
    return temp;
}

#endif