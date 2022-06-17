#ifndef SORT
#define SORT
#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;


struct ListNode
{
    explicit ListNode(int i = 0) : mData(i), mNext(nullptr) {}
    ListNode *mNext;
    int mData;
};
template <typename elemType>
class Sort
{
private:
    static ListNode *Merge(ListNode *head1, ListNode *head2);
    static ListNode *insert(ListNode *head, int val);

    static void QuickSort(elemType a[], int low, int high);
    static int Division(elemType a[], int low, int high);
    static void BuildHeap(elemType a[], int size);
    static elemType deQueue(elemType a[], int size);
    static void percolateDown(elemType a[], int size, int hole);
    static void MergeSort(elemType a[], int low, int high);
    static void Merge(elemType a[], int low1, int high1, int low2, int high2);

public:
    static void InsertionSort(elemType a[], int size); // O(N^2)
    static void ShellSort(elemType a[], int size);     // Really fast!

    static void SelectionSort(elemType a[], int size); // O(N^2)
    static void HeapSort(elemType a[], int size);      // O(N*logN)

    static void BubbleSort(elemType a[], int size); // O(N^2)
    static void QuickSort(elemType a[], int size);  // O(N*logN) ~ O(N^2)

    static void MergeSort(elemType a[], int size); // O(N*logN)

    static void CountingSort(int a[], int size); // O(N)
    static void BucketSort(int a[], int size);   // O(N)
    static void RandixSort(int a[], int size);   // O(N)
};

template <typename elemType>
void Sort<elemType>::InsertionSort(elemType a[], int size)
{
    int j;
    elemType tmp;
    for (int i = 1; i < size; ++i)
    {
        tmp = a[i];
        for (j = i; a[j - 1] > tmp && j > 0; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

template <typename elemType>
void Sort<elemType>::ShellSort(elemType a[], int size)
{
    int gap = size;
    int time = 1;
    int tmp;
    int j;
    while (gap > 1)
    {
        gap = size / std::pow(2, time);
        time++;
        gap = (gap % 2 == 0) ? gap - 1 : gap;
        for (int i = gap; i < size; i++)
        {
            tmp = a[i];
            for (j = i; j - gap >= 0 && a[j - gap] > tmp; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
    }
}

template <typename elemType>
void Sort<elemType>::SelectionSort(elemType a[], int size)
{
    int pos;
    for (int i = 0; i < size; i++)
    {
        pos = i;
        for (int j = i; j < size; j++)
        {
            if (a[j] < a[pos])
                pos = j;
        }
        std::swap(a[i], a[pos]);
    }
}

template <typename elemType>
void Sort<elemType>::BubbleSort(elemType a[], int size)
{
    int j;
    elemType tmp;
    bool flag = true;
    for (int i = 1; i < size && flag; i++)
    {
        flag = false;
        j = 0;
        while (j < size - i)
        {
            tmp = a[j];
            for (; a[j + 1] < tmp && j < size - i; j++)
            {
                a[j] = a[j + 1];
                flag = true;
            }
            a[j] = tmp;
            j++;
        }
    }

    // int i, j;
    // bool flag = true;
    // for (i = 1; i < size && flag; ++i)
    // {
    //     flag = false;
    //     for (j = 0; j < size - i; ++j)
    //         if (a[j + 1] < a[j])
    //         {
    //             std::swap(a[j], a[j + 1]);
    //             flag = true;
    //         }
    // }
}

template <typename elemType>
void Sort<elemType>::QuickSort(elemType a[], int size)
{
    QuickSort(a, 0, size - 1);
}

template <typename elemType>
void Sort<elemType>::QuickSort(elemType a[], int low, int high)
{
    if (low >= high)
        return;
    int mid = Division(a, low, high);
    QuickSort(a, mid + 1, high);
    QuickSort(a, low, mid - 1);
}

template <typename elemType>
int Sort<elemType>::Division(elemType a[], int low, int high)
{
    elemType key = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= key)
            high--;
        a[low] = a[high];

        while (low < high && a[low] <= key)
            low++;
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}
template <typename elemType>
void Sort<elemType>::HeapSort(elemType a[], int size)
{
    elemType tmp;
    BuildHeap(a, size);
    for (int i = 0; i < size; i++)
    {
        tmp = deQueue(a, size - i);
        a[size - i - 1] = tmp;
    }
}
template <typename elemType>
void Sort<elemType>::BuildHeap(elemType a[], int size)
{
    for (int i = (size + 1) / 2 - 1; i >= 0; i--)
        percolateDown(a, size, i);
}
template <typename elemType>
elemType Sort<elemType>::deQueue(elemType a[], int size)
{
    elemType tmp = a[0];
    a[0] = a[size - 1];
    percolateDown(a, size - 1, 0);
    return tmp;
}
template <typename elemType>
void Sort<elemType>::percolateDown(elemType a[], int size, int hole)
{
    elemType key = a[hole];
    int child = (hole + 1) * 2 - 1;
    while (child <= size - 1)
    {
        if (child != size - 1 && a[child] < a[child + 1])
            child++;
        if (key < a[child])
        {
            a[hole] = a[child];
            hole = child;
            child = (hole + 1) * 2 - 1;
        }
        else
            break;
    }
    a[hole] = key;
}

template <typename elemType>
void Sort<elemType>::MergeSort(elemType a[], int size)
{
    MergeSort(a, 0, size - 1);
}
template <typename elemType>
void Sort<elemType>::MergeSort(elemType a[], int low, int high)
{
    if (low == high)
        return;
    int mid = (low + high) / 2;
    MergeSort(a, low, mid);
    MergeSort(a, mid + 1, high);
    Merge(a, low, mid, mid + 1, high);
}
template <typename elemType>
void Sort<elemType>::Merge(elemType a[], int low1, int high1, int low2, int high2)
{
    elemType *temp = new elemType[high2 - low1 + 1];
    int i = low1, j = low2;
    int pos = 0;
    while (i <= high1 && j <= high2)
    {
        if (a[i] <= a[j])
            temp[pos++] = a[i++];
        else
            temp[pos++] = a[j++];
    }
    while (j <= high2)
        temp[pos++] = a[j++];
    while (i <= high1)
        temp[pos++] = a[i++];
    for (i = low1; i <= high2; i++)
        a[i] = temp[i - low1];
    delete[] temp;
}

template <typename elemType>
void Sort<elemType>::CountingSort(int a[], int size)
{
    int max = a[0], min = a[0];
    for (int i = 0; i < size; i++)
    {
        if (a[i] > max)
            max = a[i];
        else if (a[i] < min)
            min = a[i];
    }
    int *count = new int[max - min + 1]();

    for (int i = 0; i < size; i++)
        count[a[i] - min]++;

    for (int i = 1; i <= max - min; i++)
        count[i] = count[i] + count[i - 1]; // count[i] == number of element equal or less than i + min

    int *result = new int[size];
    for (int i = size - 1; i >= 0; i--)
        result[(count[a[i] - min]--) - 1] = a[i];

    for (int i = 0; i < size; i++)
        a[i] = result[i];
    delete[] count;
    delete[] result;
}

template <typename elemType>
ListNode *Sort<elemType>::insert(ListNode *head, int val)
{
    ListNode dummyNode;
    ListNode *newNode = new ListNode(val);
    ListNode *pre, *curr;
    dummyNode.mNext = head;
    pre = &dummyNode;
    curr = head;
    while (NULL != curr && curr->mData <= val)
    {
        pre = curr;
        curr = curr->mNext;
    }
    newNode->mNext = curr;
    pre->mNext = newNode;
    return dummyNode.mNext;
}

template <typename elemType>
ListNode *Sort<elemType>::Merge(ListNode *head1, ListNode *head2)
{
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;
    while (NULL != head1 && NULL != head2)
    {
        if (head1->mData <= head2->mData)
        {
            dummy->mNext = head1;
            head1 = head1->mNext;
        }
        else
        {
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }
    if (NULL != head1)
        dummy->mNext = head1;
    if (NULL != head2)
        dummy->mNext = head2;

    return dummyNode.mNext;
}

template <typename elemType>
void Sort<elemType>::BucketSort(int arr[], int n)
{
    ListNode *head = new ListNode{a[0]};
    ListNode *tail = head;

    ListNode *HEAD[10]{nullptr};
    ListNode *TAIL[10]{nullptr};
    for (int i = 1; i < size; i++)
    {
        tail->mNext = new ListNode{a[i]};
        tail = tail->mNext;
    }
    int base = 1;
    int max = a[0];
    int length = 0;
    for (int i = 0; i < size; i++)
        if (max < a[i])
            max = a[i];

    if (max == 0)
        length = 0;
    else
        while (max > 0)
        {
            max /= 10;
            length++;
        }
    for (int i = 0; i < length; i++)
    {
        tail = head;
        for (int i = 0; i < 10; i++)
            HEAD[i] = TAIL[i] = nullptr;
        while (tail != nullptr)
        {
            if (HEAD[tail->mData / base % 10] == nullptr)
            {
                HEAD[tail->mData / base % 10] = tail;
                TAIL[tail->mData / base % 10] = tail;
            }
            else
            {
                TAIL[tail->mData / base % 10]->mNext = tail;
                TAIL[tail->mData / base % 10] = TAIL[tail->mData / base % 10]->mNext;
            }
            tail = tail->mNext;
        }
        for (int i = 0; i < 10; i++)
            if (TAIL[i] != nullptr)
                TAIL[i]->mNext = nullptr;
        head = nullptr;
        for (int i = 0; i < 10; i++)
        {
            if (HEAD[i] == nullptr)
                continue;
            if (head == nullptr)
                head = HEAD[i];
            else
                tail->mNext = HEAD[i];
            tail = TAIL[i];
        }
        base *= 10;
    }

    for (int i = 0; i < size; i++)
    {
        a[i] = head->mData;
        head = head->mNext;
    }
}

template <typename elemType>
void Sort<elemType>::RandixSort(int a[], int size)
{

    int count[10]{0};
    int *result = new int[size]();
    int base = 1;
    int max = a[0];
    int length = 0;
    for (int i = 0; i < size; i++)
        if (max < a[i])
            max = a[i];

    if (max == 0)
        length = 0;
    else
        while (max > 0)
        {
            max /= 10;
            length++;
        }
    for (int i = 0; i < length; ++i)
    {
        for (int i = 0; i < 10; ++i)
            count[i] = 0;
        for (int i = 0; i < size; i++)
            count[a[i] / base % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] = count[i] + count[i - 1]; // count[i] == number of element with the key equal or less than i

        for (int i = size - 1; i >= 0; i--)
            result[(count[a[i] / base % 10]--) - 1] = a[i];

        for (int i = 0; i < size; i++)
            a[i] = result[i];

        base *= 10;
    }
}

#endif