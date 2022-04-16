#ifndef CLASS_TREE
#define CLASS_TREE
#include <iostream>
#include "BTree.hpp"
using namespace std;

template <class elemType>
class Tree : public BTree<elemType>
{
private:
public:
    Tree();
    void createTree(const elemType &flag);      //创建一棵非空树
    void PreOrder() const;                      //先根遍历
    void PostOrder() const;                     //后根遍历
    int Size() const;                           //返回节点数
    int Height() const;                         //返回高度
    bool DoesExist(const elemType &x) const;    //判断节点是否存在
    int NumOfChildren(const elemType &x) const; //返回节点的孩子数
    int LevelOf(const elemType &x) const;       //返回节点的层数，没有返回-1（1 based）
    int NumOfSiblings(const elemType &x) const; //返回兄弟的个数
    void SiblingsOf(const elemType &x) const;   //返回所有兄弟
    static Node<elemType> *buildTreePre_Post(elemType pre[], int pl, int pr, elemType in[], int il, int ir);
    //以先根遍历与后根遍历构建树，返回根节点
    //其中pre[]为先根遍历，pl为左边界，pr为右边界，in[]为后根遍历，il为左边界，ir为右边界
};

template <class elemType>
Tree<elemType>::Tree()
{
    BTree<elemType>();
}

template <class elemType>
void Tree<elemType>::createTree(const elemType &flag)
{
    seqQueue<Node<elemType> *> que; //队列
    elemType er, es;                //根数据，子数据
    Node<elemType> *h;              //队列头
    Node<elemType> *temp;
    cout << flag << " means none " << endl;
    cout << "data of root : ";
    cin >> er;
    if (er == flag)
        return;
    else
    {
        h = new Node<elemType>(er);
        BTree<elemType>::changeRoot(h);
        que.enQueue(BTree<elemType>::GetRoot());
    }
    while (!que.isEmpty())
    {
        h = que.deQueue();
        cout << "Child of " << h->data << " : ";
        cin >> es;
        if (es != flag)
        {
            h->left = new Node<elemType>(es);
            que.enQueue(h->left);
        }
        temp = h->left;
        while (es != flag)
        {
            cout << "Child of " << h->data << " : ";
            cin >> es;
            if (es != flag)
            {
                temp->right = new Node<elemType>(es);
                que.enQueue(temp->right);
                temp = temp->right;
            }
        }
    }
}

template <class elemType>
int Tree<elemType>::Size() const
{
    return BTree<elemType>::Size();
}

template <class elemType>
void Tree<elemType>::PreOrder() const
{
    BTree<elemType>::PreOrder();
}

template <class elemType>
void Tree<elemType>::PostOrder() const
{
    BTree<elemType>::InOrder();
}

template <class elemType>
bool Tree<elemType>::DoesExist(const elemType &x) const
{
    return BTree<elemType>::DoesExist(x);
}

template <class elemType>
int Tree<elemType>::LevelOf(const elemType &x) const
{
    Node<elemType> *tmproot = BTree<elemType>::GetRoot();
    if (!tmproot)
        return -1;
    seqStack<Node<elemType> *> stack1; //储存节点
    seqStack<int> stack2;              //储存层次数
    Node<elemType> *t1;                //栈顶元素
    int t2;                            //栈顶元素层次
    stack1.push(tmproot);
    stack2.push(1);
    while (!stack1.isEmpty())
    {
        t1 = stack1.pop();
        t2 = stack2.pop();
        if (t1->data == x)
            return t2;
        else
        {
            if (t1->right)
            {
                stack1.push(t1->right);
                stack2.push(t2);
            }
            if (t1->left)
            {
                stack1.push(t1->left);
                stack2.push(t2 + 1);
            }
        }
    }
    return -1;
}

template <class elemType>
int Tree<elemType>::Height() const
{
    int max = 0;
    Node<elemType> *tmproot = BTree<elemType>::GetRoot();
    if (!tmproot)
        return max;
    seqStack<Node<elemType> *> stack1; //储存节点
    seqStack<int> stack2;              //储存层次数
    Node<elemType> *t1;                //栈顶元素
    int t2;                            //栈顶元素层次
    stack1.push(tmproot);
    stack2.push(1);
    while (!stack1.isEmpty())
    {
        t1 = stack1.pop();
        t2 = stack2.pop();
        if (max < t2)
            max = t2;

        if (t1->right)
        {
            stack1.push(t1->right);
            stack2.push(t2);
        }
        if (t1->left)
        {
            stack1.push(t1->left);
            stack2.push(t2 + 1);
        }
    }
    return max;
}

template <class elemType>
int Tree<elemType>::NumOfChildren(const elemType &x) const
{
    int count = 0;
    Node<elemType> *tmproot = BTree<elemType>::GetRoot();
    if (!tmproot)
        return -1;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *top;
    stack.push(tmproot);
    while (!stack.isEmpty())
    {
        top = stack.pop();
        if (top->data == x)
        {
            if (top->left)
            {
                top = top->left;
                count++;
                while (top->right)
                {
                    top = top->right;
                    count++;
                }
            }
            return count;
        }
        if (top->right)
            stack.push(top->right);
        if (top->left)
            stack.push(top->left);
    }
    return -1;
}

template <class elemType>
int Tree<elemType>::NumOfSiblings(const elemType &x) const
{
    int count = 0;
    bool flag = false;
    Node<elemType> *tmproot = BTree<elemType>::GetRoot();
    Node<elemType> *t;
    if (!tmproot)
        return -1;
    seqStack<Node<elemType> *> stack;
    stack.push(tmproot);
    if (tmproot->data == x)
    {
        return count;
    }
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->right)
            stack.push(t->right);
        if (t->left)
        {
            stack.push(t->left);
            flag = false;
            count = 0;
            if (t->left->data == x)
                flag = true;
            t = t->left;
            count++;
            while (t->right)
            {
                if (t->right->data == x)
                    flag = true;
                t = t->right;
                count++;
            }
            if (flag)
                return count - 1;
        }
    }
    return -1;
}

template <class elemType>
void Tree<elemType>::SiblingsOf(const elemType &x) const
{
    bool flag = false;
    Node<elemType> *tmproot = BTree<elemType>::GetRoot();
    Node<elemType> *t;
    Node<elemType> *tempBig;
    Node<elemType> *tempSelf;
    if (!tmproot)
        return;
    seqStack<Node<elemType> *> stack;
    stack.push(tmproot);
    if (tmproot->data == x)
    {
        return;
    }
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->right)
            stack.push(t->right);
        if (t->left)
        {
            stack.push(t->left);
            flag = false;
            if (t->left->data == x)
            {
                flag = true;
                tempSelf = t->left;
            }
            t = t->left;
            tempBig = t;
            while (t->right)
            {
                if (t->right->data == x)
                {
                    flag = true;
                    tempSelf = t->right;
                }
                t = t->right;
            }
            if (flag)
            {
                while (tempBig)
                {
                    if (tempBig != tempSelf)
                    {
                        cout << tempBig->data << ' ';
                    }
                    tempBig = tempBig->right;
                }
                return;
            }
        }
    }
}
template <class elemType> // nlog2n
Node<elemType> *Tree<elemType>::buildTreePre_Post(elemType pre[], int pl, int pr, elemType in[], int il, int ir)
{
    return BTree<elemType>::buildBTreePre_In(pre, pl, pr, in, il, ir);
}
#endif