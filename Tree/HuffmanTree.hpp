#ifndef CLASS_HFTREE
#define CLASS_HFTREE
#include <iostream>
#include <string>
using namespace std;
const double MAX_WEIGHT = 10000;

template <class elemType>
class HfTree
{
private:
    struct Node //存储节点
    {
        elemType name; //名字
        double weight; //出现频率（权值）
        int parent;
        int leftChild;
        int rightChild;
    };
    Node *elem; //存储HuffmanTree的数组
    int length; //数组的长度
public:
    struct HfCode //储存对应的编码,其中左边的树枝为1，右边树枝为0
    {
        elemType name;
        string code;
    };
    HfTree(const elemType *inputname, const double *inputweight, int size);
    ~HfTree() { delete[] elem; }
    void getCode(HfCode *container); //传入一个容器，将其填满对应哈夫曼编码
};

template <class elemType>
HfTree<elemType>::HfTree(const elemType *inputname, const double *inputweight, int size)
{
    elem = new Node[size * 2]; //其中0位置不存数据，1~n-1位置存中间节点，n~2n-1位置存叶子节点
    length = 2 * size;
    //填入数据，同时初始化父亲为0
    for (int i = size; i < length; i++)
    {
        elem[i].name = inputname[i - size];
        elem[i].weight = inputweight[i - size];
        elem[i].parent = elem[i].leftChild = elem[i].rightChild = 0;
    }
    //开始填入中间节点，填入其左子(最小）右子（次小）以及权值，初始化其父亲为0
    double min1 = MAX_WEIGHT; //最小权值
    double min2 = MAX_WEIGHT; //次小权值
    int posmin1;              //最小权值点的下标
    int posmin2;              //次小权值点的下标
    for (int k = size - 1; k > 0; k--)
    {
        posmin1 = 0;
        posmin2 = 0;
        min1 = MAX_WEIGHT;
        min2 = MAX_WEIGHT;
        for (int i =k + 1; i < length; i++)
        {
            if (elem[i].parent == 0)
            {
                if (elem[i].weight < min1)
                {
                    min2 = min1;
                    posmin2 = posmin1;
                    min1 = elem[i].weight;
                    posmin1 = i;
                }
                else if (elem[i].weight < min2 && elem[i].weight >= min1)
                {
                    min2 = elem[i].weight;
                    posmin2 = i;
                }
            }
        }
        elem[k].weight = min1 + min2;
        elem[k].parent = 0;
        elem[k].leftChild = posmin1;
        elem[k].rightChild = posmin2;
        elem[posmin1].parent = k;
        elem[posmin2].parent = k;
    }
}

template <class elemType>
void HfTree<elemType>::getCode(HfCode *container)
{
    int size = length / 2;
    int currentPos;
    int parentPos;
    for (int i = 0; i < size; i++)
    {
        container[i].name = elem[i + size].name;
        container[i].code = "";
        currentPos = i + size;
        parentPos = elem[currentPos].parent;
        while (parentPos != 0)
        {
            if (elem[parentPos].leftChild == currentPos)
                container[i].code = '1' + container[i].code;
            else
                container[i].code = '0' + container[i].code;
            currentPos = parentPos;
            parentPos = elem[currentPos].parent;
        }
    }
}

#endif