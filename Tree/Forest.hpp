#ifndef CLASS_FOREST
#define CLASS_FOREST
#include <iostream>
#include "Tree.hpp"
using namespace std;

template <class elemType>
class Forest : public Tree<elemType>
{
public:
    Forest();
    void createForest(const elemType &flag);             //创建一棵非空森林
    void PreOrder() const;                               //先序遍历：对每一棵树先根遍历
    void InOrder() const;                                //中序遍历：对每一棵树后根遍历
    int Size() const;                                    //返回节点数
    int NumOfTrees() const;                              //返回树的个数
    bool DoesExist(const elemType &x) const;             //判断节点是否存在
    int NumOfChildren(const elemType &x) const;          //返回节点的孩子数
    int LevelOf(const elemType &x) const;                //返回节点的层数，没有返回-1（1 based）
    int NumOfSiblings(const elemType &x) const;          //返回x的兄弟的个数
    void SiblingsOf(const elemType &x) const;            //返回x的所有兄弟
    elemType No_ChildOf(int i, const elemType &x) const; //返回x的第x个孩子
    static Node<elemType> *buildForestPre_In(elemType pre[], int pl, int pr, elemType in[], int il, int ir);
    //以前序遍历与中序遍历构建森林，返回第一棵树的根节点
    //其中pre[]为前序遍历，pl为左边界，pr为右边界，in[]为中序遍历，il为左边界，ir为右边界
};
template <class elemType>
Forest<elemType>::Forest()
{
    Tree<elemType>();
}

template <class elemType>
void Forest<elemType>::createForest(const elemType &flag)
{
    seqQueue<Node<elemType> *> que; //队列
    elemType er, es;                //根数据，子数据
    Node<elemType> *h;              //队列头
    Node<elemType> *temp;
    cout << flag << " means none " << endl;
    cout << "Root of Tree : ";
    cin >> er;
    if (er == flag)
        return;
    h = new Node<elemType>(er);
    BTree<elemType>::changeRoot(h);
    que.enQueue(BTree<elemType>::GetRoot());
    while (er != flag)
    {
        cout << "Root of Tree : ";
        cin >> er;
        if (er != flag)
        {
            h->right = new Node<elemType>(er);
            que.enQueue(h->right);
            h = h->right;
        }
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
void Forest<elemType>::PreOrder() const
{
    Tree<elemType>::PreOrder();
}

template <class elemType>
void Forest<elemType>::InOrder() const
{
    Tree<elemType>::PostOrder();
}

template <class elemType>
int Forest<elemType>::Size() const
{
    return Tree<elemType>::Size();
}

template <class elemType>
int Forest<elemType>::NumOfTrees() const
{
    int count = 0;
    Node<elemType> *temproot = BTree<elemType>::GetRoot();
    if (!temproot || !temproot->left)
        return count;
    temproot = temproot->left;
    while (!temproot)
    {
        temproot = temproot->right;
        count++;
    }
    return count;
}

template <class elemType>
bool Forest<elemType>::DoesExist(const elemType &x) const
{
    return Tree<elemType>::DoesExist(x);
}

template <class elemType>
int Forest<elemType>::NumOfChildren(const elemType &x) const
{
    return Tree<elemType>::NumOfChildren(x);
}

template <class elemType>
int Forest<elemType>::LevelOf(const elemType &x) const
{
    return Tree<elemType>::LevelOf(x);
}

template <class elemType>
int Forest<elemType>::NumOfSiblings(const elemType &x) const
{
    Node<elemType> *temproot = BTree<elemType>::GetRoot();
    if (!temproot)
        return -1;
    if (temproot->data == x)
    {
        return 0;
    }
    temproot = temproot->right;
    while (!temproot)
    {
        temproot = temproot->right;
        if (temproot->data == x)
        {
            return 0;
        }
    }
    return Tree<elemType>::NumOfSiblings(x);
}

template <class elemType>
void Forest<elemType>::SiblingsOf(const elemType &x) const
{
    Node<elemType> *temproot = BTree<elemType>::GetRoot();
    if (!temproot)
        return;
    if (temproot->data == x)
    {
        return;
    }
    temproot = temproot->right;
    while (!temproot)
    {
        temproot = temproot->right;
        if (temproot->data == x)
        {
            return;
        }
    }
    return Tree<elemType>::SiblingsOf(x);
}

template <class elemType> // nlog2n
Node<elemType> *Forest<elemType>::buildForestPre_In(elemType pre[], int pl, int pr, elemType in[], int il, int ir)
{
    return BTree<elemType>::buildForestPre_In(pre, pl, pr, in, il, ir);
}

template <class elemType>
elemType Forest<elemType>::No_ChildOf(int i, const elemType &x) const
{
    Node<elemType> *temproot = BTree<elemType>::GetRoot();
    if (!temproot)
        throw 1;
    seqStack<Node<elemType> *> stack;
    Node<elemType> *t;
    stack.push(temproot);
    while (!stack.isEmpty())
    {
        t = stack.pop();
        if (t->data == x)
        {
            t = t->left;
            i--;
            while (i)
            {
                t = t->right;
                i--;
            }
            return t->data;
        }
        if (t->right)
            stack.push(t->right);
        if (t->left)
            stack.push(t->left);
    }
    return temproot->data;
}

#endif