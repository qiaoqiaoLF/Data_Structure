#ifndef CLASS_SEQLIST
#define CLASS_SEQLIST
#include "List.hpp"
#include <iostream>
using namespace std;

template <class elemType>
class seqList : public List<elemType>
{
private:
    elemType *data; //指向数组的指针
    int currentLength;
    int maxSize;
    void doubleSpace();

public:
    seqList(int initSize = 10); //构造函数
    ~seqList() { delete[] data; }
    int length() const;
    int search(const elemType &x) const; //存在返回第一个下标，不存在返回-1
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear();
    void traverse() const;
    void quicksort(int low = 0, int high = -2);
};

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    if (!data)
        throw 1;
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

template <typename elemType>
int seqList<elemType>::search(const elemType &x) const
{
    for (int i = 0; i < currentLength; ++i)
    {
        if (data[i] == x)
            return i;
    }
    return 0;
}

template <typename elemType>
elemType seqList<elemType>::visit(int i) const
{
    if (i < 0 || i >= currentLength)
        throw 1;
    return data[i];
}

template <typename elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    if (i < 0 || i > currentLength)
        return;
    if (currentLength == maxSize)
        doubleSpace();
    for (int j = i; j < currentLength; ++j)
    {
        data[j + 1] = data[j];
    }
    data[i] = x;
    currentLength++;
}

template <typename elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *temp;
    temp = new elemType[2 * maxSize];
    for (int i = 0; i < currentLength; ++i)
    {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    maxSize *= 2;
}

template <typename elemType>
void seqList<elemType>::remove(int i)
{
    if (i < 0 || i >= currentLength)
        return;
    for (int j = i; j < currentLength - 1; ++j)
    {
        data[j] = data[j + 1];
    }
    currentLength--;
}

template <typename elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

template <typename elemType>
void seqList<elemType>::traverse() const
{
    for (int i = 0; i < currentLength; ++i)
        cout << data[i] << " ";
    cout << endl;
}
template <typename elemType>
void seqList<elemType>::quicksort(int low, int high)
{
    if (high == -2)
        high = currentLength - 1;
    int mid;
    int inilow = low;
    int inihigh = high;
    if (low >= high)
        return;
    elemType key;
    key = data[low];

    do
    {
        while (low < high && data[high] >= key)
            --high;
        if (low < high)
        {
            data[low] = data[high];
            ++low;
        }
        while (low < high && data[low] <= key)
            ++low;
        if (low < high)
        {
            data[high] = data[low];
            --high;
        }
    } while (low != high);
    data[low] = key;
    mid = low;
    quicksort(inilow, mid - 1);
    quicksort(mid + 1, inihigh);
}

#endif
