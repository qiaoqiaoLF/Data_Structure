#ifndef CLASS_BTree
#define CLASS_BTree

#include <iostream>
#include "seqStack.hpp"
#include "seqQueue.hpp"
using namespace std;

template <class elemType>
class BTree;
template <class elemType>
class Tree;
template <class elemType>
class Forest;

template <class elemType>
class Node
{
    friend class BTree<elemType>;
    friend class Tree<elemType>;
    friend class Forest<elemType>;
    elemType data;
    Node *left, *right;
    int leftFlag;  // 用于标识是否线索，0时left为左孩子节点，1时为前驱线索
    int rightFlag; // 用于标识是否线索，0时right为右孩子节点，1时为后驱线索
public:
    Node()
    {
        left = nullptr;
        right = nullptr;
        leftFlag = 0;
        rightFlag = 0;
    }
    Node(const elemType &x, Node *L = nullptr, Node *R = nullptr)
    {
        data = x;
        right = R;
        left = L;
        leftFlag = 0;
        rightFlag = 0;
    }
};

template <class elemType>
class BTree
{
private:
    Node<elemType> *root;
    //辅助函数
    int Size(Node<elemType> *t) const;                          // 以t为根的二叉树的结点个数
    int Height(Node<elemType> *t) const;                        // 以t为根的二叉树的高度
    void DelTree(Node<elemType> *t);                            // 删除以t为根的二叉树
    void PreOrder(Node<elemType> *t) const;                     // 按前序遍历输出以t为根的二叉树的数据值
    void InOrder(Node<elemType> *t) const;                      // 按中序遍历输出以t为根的二叉树的数据值
    void PostOrder(Node<elemType> *t) const;                    // 按层次遍历输出以t为根的二叉树的数据值
    bool DoesExist(const elemType &x, Node<elemType> *t) const; //判断以t为根的二叉树中某个元素是否存在
    int LevelOf(const elemType &x, Node<elemType> *t) const;    //计算某节点在以t为节点的二叉树中的层次数
public:
    //注意：函数名前面带有R的为递归实现
    BTree() { root = nullptr; }              //给属性赋初值
    virtual ~BTree() { DelTree(); }          //析构
    void createTree(const elemType &flag);   //创建一棵非空二叉树
    void changeRoot(Node<elemType> *newRoot) //更改根节点
    {
        root = newRoot;
    }
    bool isEmpty() const { return !root; }            // 判断二叉树是否为空
    Node<elemType> *GetRoot() const { return root; }; // 获取根节点
    int RSize() const { return Size(root); }          // 返回二叉树节点个数
    int RHeight() const { return Height(root); }      // 返回二叉树高度
    int Size() const;                                 //返回二叉树节点个数
    int Height() const;                               //返回二叉树高度
    bool DoesExist(const elemType &x) const;          //判断某个元素是否存在
    bool RDoesExist(const elemType &x) const          //判断某个元素是否存在
    {
        return DoesExist(x, root);
    }
    int LevelOf(const elemType &x) const; //计算某节点的层次数
    int RLevelOf(const elemType &x) const //计算某节点的层次数，以前序输出
    {
        return LevelOf(x, root);
    }
    void DescendantsOf(const elemType &x) const;                         //计算某个节点的所有子孙，从下向上输出
    void AncestorsOf(const elemType &x) const;                           //计算某个节点的所有祖先
    bool IsDescendantOf(const elemType &des, const elemType &anc) const; //判断des是不是ans的子孙
    bool IsAncestorOf(const elemType &anc, const elemType &des) const    //判断anc是不是des的祖先
    {
        return IsDescendantOf(des, anc);
    }
    void DelTree(); //删除二叉树
    void RDelTree() //删除二叉树
    {
        DelTree(root);
        root = nullptr;
    }
    void RPreOrder() const { PreOrder(root); }   //按前序遍历输出的二叉树的数据值
    void RInOrder() const { InOrder(root); }     //按中序遍历输出的二叉树的数据值
    void RPostOrder() const { PostOrder(root); } //按后序遍历输出的二叉树的数据值
    //非递归实现
    void PreOrder() const;   //按前序遍历输出的二叉树的数据值
    void InOrder() const;    //按中序遍历输出的二叉树的数据值
    void PostOrder() const;  //按后序遍历输出的二叉树的数据值
    void LevelOrder() const; //按层次遍历输出的二叉树的数据值
    static Node<elemType> *buildBTreePre_In(elemType pre[], int pl, int pr, elemType in[], int il, int ir);
    //以前序遍历与中序遍历构建二叉树，返回根节点
    //其中pre[]为前序遍历，pl为左边界，pr为右边界，in[]为中序遍历，il为左边界，ir为右边界
    static Node<elemType> *buildBTreeIn_Post(elemType in[], int il, int ir, elemType post[], int pl, int pr);
    // 以中序遍历与后序遍历构建二叉树，返回根节点
    // in[]为中序遍历，il为左边界，ir为右边界,其中post[]后序遍历，pl为左边界，pr为右边界
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &flag)
{
    seqQueue<Node<elemType> *> que;
    elemType e, el, er; // 根数据，左子数据，右子数据
    Node<elemType> *h;  //队列头
    cout << flag << " means none " << endl;
    cout << "data of root : ";
    cin >> e;
    if (e == flag)
        root = nullptr;
    else
    {
        root = new Node<elemType>(e);
        que.enQueue(root);
    }
    while (!que.isEmpty())
    {
        h = que.getHead();
        cout << "left child of  " << h->data << " : ";
        cin >> el;
        cout << "right child of " << h->data << " : ";
        cin >> er;
        if (el != flag)
        {
            h->left = new Node<elemType>(el);
            que.enQueue(h->left);
        }
        if (er != flag)
        {
            h->right = new Node<elemType>(er);
            que.enQueue(h->right);
        }
        que.deQueue();
    }
}

template <class elemType>
int BTree<elemType>::Size(Node<elemType> *t) const
{
    if (!t)
        return 0;
    else
        return 1 + Size(t->left) + Size(t->right);
}

template <class elemType>
int BTree<elemType>::Height(Node<elemType> *t) const
{
    if (!t)
        return 0;
    else
        return 1 + max(Height(t->left), Height(t->right));
}

template <class elemType>
void BTree<elemType>::DelTree(Node<elemType> *t)
{
    if (!t)
        return;
    else
    {
        DelTree(t->left);
        DelTree(t->right);
        delete t;
    }
}

template <class elemType>
void BTree<elemType>::PreOrder(Node<elemType> *t) const
{
    if (!t)
        return;
    else
    {
        cout << t->data << ' ';
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

template <class elemType>
void BTree<elemType>::InOrder(Node<elemType> *t) const
{
    if (!t)
        return;
    else
    {
        InOrder(t->left);
        cout << t->data << ' ';
        InOrder(t->right);
    }
}

template <class elemType>
void BTree<elemType>::PostOrder(Node<elemType> *t) const
{
    if (!t)
        return;
    else
    {
        PostOrder(t->left);
        PostOrder(t->right);
        cout << t->data << ' ';
    }
}

template <class elemType>
void BTree<elemType>::PreOrder() const
{
    if (!root)
        return;
    else
    {
        Node<elemType> *t; //栈顶
        seqStack<Node<elemType> *> stack;
        stack.push(root);
        while (!stack.isEmpty())
        {
            t = stack.pop();
            cout << t->data << ' ';
            if (t->right)
                stack.push(t->right);
            if (t->left)
                stack.push(t->left);
        }
    }
}

// template <class elemType>
// void BTree<elemType>::InOrder() const
// {
//     if (!root)
//         return;
//     else
//     {
//         Node<elemType> *t;                 // 栈顶
//         seqStack<Node<elemType> *> stack1; // 节点地址栈
//         seqStack<int> stack2;              // 标志栈
//         stack1.push(root);
//         stack2.push(0);
//         while (!stack1.isEmpty())
//         {
//             if (stack2.Top() == 1)
//             {
//                 stack2.pop();
//                 t = stack1.pop();
//                 cout << t->data << ' ';
//             }
//             else
//             {
//                 t = stack1.pop();
//                 stack2.pop();
//                 if (t->right)
//                 {
//                     stack1.push(t->right);
//                     stack2.push(0);
//                 }
//                 stack1.push(t);
//                 stack2.push(1);
//                 if (t->left)
//                 {
//                     stack1.push(t->left);
//                     stack2.push(0);
//                 }
//             }
//         }
//     }
// }

// another version
// template <class elemType>
// void BTree<elemType>::InOrder() const
// {
//     if (!root)
//         return;
//     else
//     {
//         Node<elemType> *t;                 // 栈顶
//         seqStack<Node<elemType> *> stack1; // 节点地址栈
//         seqStack<int> stack2;              // 标志栈
//         stack1.push(root);
//         stack2.push(0);
//         while (!stack1.isEmpty())
//         {
//             if (stack2.Top() == 1)
//             {
//                 stack2.pop();
//                 t = stack1.pop();
//                 cout << t->data << ' ';
//                 if (t->right)
//                 {
//                     stack1.push(t->right);
//                     stack2.push(0);
//                 }
//             }
//             else
//             {
//                 stack2.pop();
//                 stack2.push(1);
//                 t = stack1.Top();
//                 if (t->left)
//                 {
//                     stack1.push(t->left);
//                     stack2.push(0);
//                 }
//             }
//         }
//     }
// }

// another version 先让左子一直进队，直到左子为空，随后输出根节点，再让右子进栈，然后再让左子进栈到底
template <class elemType>
void BTree<elemType>::InOrder() const
{
    if (!root)
        return;
    else
    {
        Node<elemType> *t;
        seqStack<Node<elemType> *> stack;
        t = root;
        stack.push(t);
        while (t->left)
        {
            stack.push(t->left);
            t = t->left;
        }
        while (!stack.isEmpty())
        {
            t = stack.pop();
            cout << t->data << ' ';
            if (!t->right)
                continue;
            t = t->right;
            stack.push(t);
            while (t->left)
            {
                stack.push(t->left);
                t = t->left;
            }
        }
    }
}

// template <class elemType>
// void BTree<elemType>::PostOrder() const
// {
//     if (!root)
//         return;
//     else
//     {
//         Node<elemType> *t;                 // 栈顶
//         seqStack<Node<elemType> *> stack1; // 节点地址栈
//         seqStack<int> stack2;              // 标志栈
//         stack1.push(root);
//         stack2.push(0);
//         while (!stack1.isEmpty())
//         {
//             if (stack2.Top() == 1)
//             {
//                 stack2.pop();
//                 t = stack1.pop();
//                 cout << t->data << ' ';
//             }
//             else
//             {
//                 t = stack1.Top();
//                 stack2.pop();
//                 stack2.push(1);
//                 if (t->right)
//                 {
//                     stack1.push(t->right);
//                     stack2.push(0);
//                 }
//                 if (t->left)
//                 {
//                     stack1.push(t->left);
//                     stack2.push(0);
//                 }
//             }
//         }
//     }
// }

template <class elemType>
void BTree<elemType>::PostOrder() const
{
    if (!root)
        return;
    else
    {
        Node<elemType> *t;                 // 栈顶
        seqStack<Node<elemType> *> stack1; // 节点地址栈
        seqStack<int> stack2;              // 标志栈
        stack1.push(root);
        stack2.push(0);
        while (!stack1.isEmpty())
        {
            if (stack2.Top() == 0)
            {
                t = stack1.Top();
                stack2.pop();
                stack2.push(1);
                if (t->left)
                {
                    stack1.push(t->left);
                    stack2.push(0);
                }
            }
            else if (stack2.Top() == 1)
            {
                t = stack1.Top();
                stack2.pop();
                stack2.push(2);
                if (t->right)
                {
                    stack1.push(t->right);
                    stack2.push(0);
                }
            }
            else
            {
                t = stack1.pop();
                stack2.pop();
                cout << t->data << ' ';
            }
        }
    }
}

template <class elemType>
void BTree<elemType>::LevelOrder() const
{
    if (!root)
        return;
    else
    {
        Node<elemType> *h; //队列头
        seqQueue<Node<elemType> *> que;
        que.enQueue(root);
        while (!que.isEmpty())
        {
            h = que.getHead();
            cout << h->data << ' ';
            if (h->left)
                que.enQueue(h->left);
            if (h->right)
                que.enQueue(h->right);
            que.deQueue();
        }
    }
}

template <class elemType>
int BTree<elemType>::Size() const
{
    int count = 0;
    seqStack<Node<elemType> *> stack; //栈
    Node<elemType> *t;                // 栈顶
    if (!root)
        return count;
    else
    {
        stack.push(root);
        while (!stack.isEmpty())
        {
            t = stack.pop();
            count++;
            if (t->right)
            {
                stack.push(t->right);
            }
            if (t->left)
            {
                stack.push(t->left);
            }
        }
        return count;
    }
}

template <class elemType>
int BTree<elemType>::Height() const
{
    int max = 0;
    if (!root)
        return max;
    else
    {
        seqStack<Node<elemType> *> stack1; //储存结点指针
        seqStack<int> stack2;              //储存节点层次
        Node<elemType> *t1;                // stack1栈顶
        int t2;                            // stack2 栈顶
        stack1.push(root);
        stack2.push(1);
        while (!stack1.isEmpty())
        {
            t1 = stack1.pop();
            t2 = stack2.pop();
            if (t2 > max)
                max = t2;
            if (t1->right)
            {
                stack1.push(t1->right);
                stack2.push(t2 + 1);
            }
            if (t1->left)
            {
                stack1.push(t1->left);
                stack2.push(t2 + 1);
            }
        }
        return max;
    }
}

template <class elemType>
int BTree<elemType>::LevelOf(const elemType &x, Node<elemType> *t) const
{
    static int H = Height();
    if (!t)
        return H;
    if (t->data == x)
        return 1;

    else
        return min(LevelOf(x, t->left) + 1, LevelOf(x, t->right) + 1);
}

template <class elemType>
int BTree<elemType>::LevelOf(const elemType &x) const //默认存在，不在则返回-1
{
    if (!root)
        return -1;
    seqStack<Node<elemType> *> stack1; //指针栈
    seqStack<int> stack2;              //层次栈
    Node<elemType> *t1;
    int t2;
    stack1.push(root);
    stack2.push(1);
    while (!stack1.isEmpty())
    {
        t1 = stack1.pop();
        t2 = stack2.pop();
        if (t1->data == x)
            return t2;
        if (t1->right)
        {
            stack1.push(t1->right);
            stack2.push(t2 + 1);
        }
        if (t1->left)
        {
            stack1.push(t1->left);
            stack2.push(t2 + 1);
        }
    }
    return -1;
}

template <class elemType>
bool BTree<elemType>::DoesExist(const elemType &x) const
{
    if (!root)
        return false;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *t;
    stack.push(root);
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->data == x)
            return true;
        if (t->right)
            stack.push(t->right);
        if (t->left)
            stack.push(t->left);
    }
    return false;
}

template <class elemType>
bool BTree<elemType>::DoesExist(const elemType &x, Node<elemType> *t) const
{

    if (!t)
        return false;
    if (x == t->data)
        return true;
    return DoesExist(x, t->left) || DoesExist(x, t->right);
}

template <class elemType>
void BTree<elemType>::DelTree()
{
    if (!root)
        return;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *t;
    stack.push(root);
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->right)
            stack.push(t->right);
        if (t->left)
            stack.push(t->left);
        delete t;
    }
}

template <class elemType>
void BTree<elemType>::DescendantsOf(const elemType &x) const
{
    if (!root)
        return;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *t;
    stack.push(root);
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->data == x)
            break;
        if (t->right)
            stack.push(t->right);
        if (t->left)
            stack.push(t->left);
    }
    if (t->data == x)
        PreOrder(t->left);
    PreOrder(t->right);
}

template <class elemType>
void BTree<elemType>::AncestorsOf(const elemType &x) const
{
    if (!root)
        return;
    seqStack<Node<elemType> *> stack1; //储存指针的栈
    seqStack<int> stack2;              // 储存节点访问次数的栈
    Node<elemType> *t1;                // Top of stack1
    int t2;                            // Top of stack2
    stack1.push(root);
    stack2.push(0);
    while (!stack1.isEmpty())
    {
        t1 = stack1.Top();
        t2 = stack2.pop();
        if (t2 == 0)
        {
            stack2.push(t2 + 1);
            if (t1->left)
            {
                stack1.push(t1->left);
                stack2.push(0);
            }
        }
        if (t2 == 1)
        {
            stack2.push(t2 + 1);
            if (t1->right)
            {
                stack1.push(t1->right);
                stack2.push(0);
            }
        }
        if (t2 == 2)
        {
            stack1.pop();
            if (t1->data == x)
                break;
        }
    }
    if (t1->data == x)
    {
        while (!stack1.isEmpty())
            cout << stack1.pop()->data << ' ';
    }
}

template <class elemType>
bool BTree<elemType>::IsDescendantOf(const elemType &des, const elemType &anc) const //判断des是不是ans的子孙
{
    if (!root)
        return false;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *t;
    stack.push(root);
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->data == anc)
            break;
        if (t->right)
            stack.push(t->right);
        if (t->left)
            stack.push(t->left);
    }
    return DoesExist(des, t);
}

template <class elemType> // nlog2n
Node<elemType> *BTree<elemType>::buildBTreePre_In(elemType pre[], int pl, int pr, elemType in[], int il, int ir)
//其中pre[]为前序遍历，pl为左边界，pr为右边界，in[]为中序遍历，il为左边界，ir为右边界
{
    Node<elemType> *root;
    root = new Node<elemType>(pre[pl]);
    if (pl > pr)
        return nullptr; // base case
    else
    {
        int pos;
        for (int i = il; i <= ir; ++i)
        {
            if (pre[pl] == in[i])
            {
                pos = i;
                break;
            }
        }
        root->left = buildBTreePre_In(pre, pl + 1, pl + pos - il, in, il, pos - 1);
        root->right = buildBTreePre_In(pre, pl + pos - il + 1, pr, in, pos + 1, ir);
        return root;
    }
}

template <class elemType> // nlog2n
Node<elemType> *BTree<elemType>::buildBTreeIn_Post(elemType in[], int il, int ir, elemType post[], int pl, int pr)
// in[]为中序遍历，il为左边界，ir为右边界,其中post[]后序遍历，pl为左边界，pr为右边界
{
    Node<elemType> *root;
    root = new Node<elemType>(post[pr]);
    if (pl > pr)
        return nullptr; // base case
    else
    {
        int pos;
        for (int i = il; i <= ir; ++i)
        {
            if (post[pr] == in[i])
            {
                pos = i;
                break;
            }
        }
        root->left = buildBTreeIn_Post(in, il, pos - 1, post, pl, pos - il + pl - 1);
        root->right = buildBTreeIn_Post(in, pos + 1, ir, post, pos - il + pl, pr - 1);
        return root;
    }
}

#endif